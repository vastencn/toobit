//-----------------------------------------------
//-------------Templates n Such------------------
//-----------------------------------------------

char *response_ok="HTTP/1.1 200 OK\nContent-Type: text; charset=utf-8\nContent-Length:2\n\nok";
char *response_simple="HTTP/1.1 200 OK\nContent-Type: text; charset=utf-8\nContent-Length:";
char *tb_html_template_space=NULL;
char *tb_view_template=NULL;
char *path_to_view_template=TB_SERVER_HTML_VIEW_TEMPLATE;


//-----------------------------------------------
// 				tb_server()
// Main loop of universe server
//-----------------------------------------------
void *tb_server( void* in_p ){
  int client_sock , c ,read_size; 
  unsigned int read_tries;
  struct toobit_space *in_u=( struct toobit_space*)in_p;
  struct sockaddr_in client;
  char client_request[2000];

  (*in_u).sock=socket(AF_INET, SOCK_STREAM, 0);
  if((*in_u).sock == -1){
    printf("Could not create socket\n");
    return;
    }

  (*in_u).sockaddr.sin_family      = AF_INET;
  (*in_u).sockaddr.sin_addr.s_addr = INADDR_ANY;
  (*in_u).sockaddr.sin_port        = htons( (*in_u).server_port );
  if(bind((*in_u).sock,(struct sockaddr *)&(*in_u).sockaddr, sizeof((*in_u).sockaddr))<0){
    perror("bind failed\n");
    return;
    }
  listen((*in_u).sock, 5);
  c=sizeof(struct sockaddr_in);

  while(1){//---- Start Server Loop
    client_sock=accept((*in_u).sock, (struct sockaddr *)&client, (socklen_t*)&c);
    if(client_sock<0){
      printf("accept failed\n");
      return;
      }

    read_size=0;
    read_tries=TB_SERVER_READ_RETRIES;
    while(read_tries--){
      read_size+=recv(client_sock, client_request, (TB_SERVER_MAX_REQUEST_LEN-read_size), 0);
      }
    client_request[read_size]=14;	//do as uint16 later
    client_request[read_size+1]=0;

    if(read_size>3){

      switch(client_request[0]){//---------Begin Request Handler
	case TB_SERVER_COMMAND_GET:
	  if(read_size>5){
	    switch(client_request[5]){

	      case TB_SERVER_COMMAND_GET_RAW://-------Request for raw data, probably a view terminal
		tb_server_dump_raw(in_u, client_sock);
		break;

	      case TB_SERVER_COMMAND_GET_VIEW_TERMINAL://----- Request for a view terminal interface
		tb_server_view_terminal(in_u, client_sock);
		break;

	      #if TB_SERVER_INJECTION == 1
	        case TB_SERVER_COMMAND_GET_INJECT://----- Request to inject into space
	  	  tb_server_inject(in_u, client_sock, read_size, client_request+6);
		  break;
	      #endif

	      default: tb_server_print_space_one_byte(in_u, client_sock);//----- Default command return ascii print
	      }
	    }else tb_server_print_space_one_byte(in_u, client_sock);//----- Default request return ascii print
	  break;

	}

      }				//---------End Request Handler
    shutdown(client_sock,SHUT_RDWR);
    close(client_sock);
    }//---- End Server Loop
  return;
  }


//-----------------------------------------------
// 				tb_start_server()
// Start the universe server
//-----------------------------------------------
void tb_server_start( struct toobit_space* in_u, unsigned int in_port){
  int r;
  (*in_u).server_port=in_port;
  r=pthread_create(&(*in_u).server_thread, NULL, tb_server, (void*)in_u);
  if(r){
    printf("error creating server thread!\n");
    }
  return;
  }


//-----------------------------------------------
// 		tb_server_print_space_one_byte()
// writes the same data as print_space_one_byte 
// to a client socket as an HTTP text response
// ******REQUIRES INNER LOOP OPTIMIZATION*********
//-----------------------------------------------
void tb_server_print_space_one_byte( struct toobit_space* in_u , int socket){
  unsigned int y=TB_SPACE_SIZE_Y,x,offset;
  char pstring[TB_SPACE_SIZE_X_PLUS_ONE];
  write(socket,response_simple,strlen(response_simple));
  sprintf(pstring,"%i\n\n",TB_SPACE_SIZE_X_PLUS_ONE*TB_SPACE_SIZE_Y-1);
  write(socket,pstring,strlen(pstring));
  
  while(y--){
    x=TB_SPACE_SIZE_X;
    while(x--){
      pstring[x]=(*in_u).space[(y*TB_SPACE_SIZE_X)+x];   //fix back later
      }
    pstring[TB_SPACE_SIZE_X]='\n';
    write(socket,pstring,TB_SPACE_SIZE_X_PLUS_ONE);
    }
  return;
  }

//-----------------------------------------------
// 			tb_server_load_template()
// Load template into 'ram disk', return pointer  
//-----------------------------------------------
char *tb_server_load_template(char *path){
  char *now=path, *end=path+strlen(path);
  int fdt, offset=0;
  ssize_t res;

  if(!tb_html_template_space){
    tb_html_template_space=malloc(TB_SERVER_HTML_MEMORY_VALUE);
    if(!tb_html_template_space)return NULL;
    }

  fdt=open(path,O_RDONLY);
  if(fdt<0) {
    printf("failed to open template file\n");
    return NULL;
    }  
  while(res=read(fdt,tb_html_template_space+offset,1)>0){  //wtf! returns 1 no matter how many bytes read?..??.fine!, 1 at a time, fix later
    offset+=res;
    }

  tb_html_template_space[offset]=0;
  close(fdt);
  return tb_html_template_space;
  }

//-----------------------------------------------
// 			tb_server_view_terminal()
// Send client a browser view terminal  
//-----------------------------------------------
void tb_server_view_terminal( struct toobit_space *in_u , int socket){
  char pstring[128]; 
  if(!tb_view_template){
    if(!(tb_view_template=tb_server_load_template(&path_to_view_template[0]))){
      return;
      }
    }  
  write(socket,response_simple,strlen(response_simple));
  sprintf(pstring,"%i\n\n",strlen(tb_view_template));
  write(socket,pstring,strlen(pstring));
  write(socket,tb_view_template,strlen(tb_view_template));
  return;
  }

//-----------------------------------------------
// 			tb_server_dump_raw()
// dump universe data with header to client 
//-----------------------------------------------
void tb_server_dump_raw( struct toobit_space *in_u , int socket){
  char *now=(char *)(*in_u).space, *end=now+TB_SPACE_DATA_SIZE_BYTES;
  unsigned int res;
  char pstring[128];
  unsigned short int hdr[3];  

  hdr[0]=TB_SPACE_SIZE_X;
  hdr[1]=TB_SPACE_SIZE_Y;
  hdr[2]=TB_PARTICLE_DATA_SIZE;

  write(socket,response_simple,strlen(response_simple));
  sprintf(pstring,"%i\n\n",TB_SPACE_DATA_SIZE_BYTES+6);  // 6=size of 3 unit16 for (x y datasize) header
  write(socket,pstring,strlen(pstring));
  while(now<end&&res>=0){
    res=write(socket,now,end-now);
    now+=res;
    }
  write(socket,(char *)hdr,6);
  return;
  }


#if TB_SERVER_INJECTION == 1
  //-----------------------------------------------
  // 			tb_server_inject()
  // inject data into space 
  //    format 8bit frame size, 16 bit x, 16bi y
  //-----------------------------------------------
  void tb_server_inject( struct toobit_space *in_u , int socket, int rlen, char *rptr){
    char *target_ptr, nowv, *now_ptr, buf_cmd[TB_SERVER_INJECTION_BUFFER_ENTRY_SIZE];
    uint16_t totv=0, nown=0;

    target_ptr=rptr;
    now_ptr=buf_cmd;
    while(nowv=*target_ptr++){
      nowv&=15;
      if(nowv<10){
	totv=(totv*10)+nowv;
	}else if(nowv==15){
        nown++;
	*(uint16_t *)now_ptr=totv;
	if(nown==2)*(uint16_t *)now_ptr=TB_SPACE_SIZE_X-*(uint16_t *)now_ptr;
	if(nown==3)*(uint16_t *)now_ptr=TB_SPACE_SIZE_Y-*(uint16_t *)now_ptr;
	now_ptr+=2;
	totv=0;
	}else{
	*(uint16_t *)now_ptr=totv;
	now_ptr+=2;
	totv=0;
	break;
	}    
      }
    totv=now_ptr-buf_cmd;

    pthread_mutex_lock(&(*in_u).injection_mutex);

    target_ptr=(*in_u).injection_buffer+((*in_u).buffer_avail*TB_SERVER_INJECTION_BUFFER_ENTRY_SIZE);

    memcpy(target_ptr,buf_cmd,totv);
    memset(target_ptr+totv,0,TB_SERVER_INJECTION_BUFFER_ENTRY_SIZE-totv);

    (*in_u).buffer_avail++;

    pthread_mutex_unlock(&(*in_u).injection_mutex);

    write(socket,response_ok,strlen(response_ok));
    return;
    }
#endif
