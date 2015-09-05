
//-----------------------------------------------
// 			tb_thread_core_init()
//-----------------------------------------------
void tb_thread_core_init( struct toobit_space* in_u ){
  int r;

  pthread_mutex_init(&(*in_u).startup_mutex, NULL);
  pthread_mutex_lock(&(*in_u).startup_mutex);
  r=TB_THREADING_TOTAL_THREADS;
  while(--r){
    pthread_mutex_init(&(*in_u).thread_mutex_ready[r], NULL);
    pthread_mutex_init(&(*in_u).thread_mutex_go[r], NULL);
    pthread_mutex_init(&(*in_u).thread_mutex_done[r], NULL);
    pthread_mutex_init(&(*in_u).thread_mutex_end[r], NULL);
    pthread_mutex_lock(&(*in_u).thread_mutex_ready[r]);
    pthread_mutex_lock(&(*in_u).thread_mutex_go[r]);
    pthread_mutex_lock(&(*in_u).thread_mutex_done[r]);
    pthread_mutex_lock(&(*in_u).thread_mutex_end[r]);
    }

  r=pthread_create(&(*in_u).thread[TB_THREADING_EDGER_THREAD_ID], NULL, tb_thread_core_edger, (void*)in_u);
  if(r){
    printf("error starting edger thread!\n");
    }

  r=pthread_create(&(*in_u).thread[TB_THREADING_MASTER_THREAD_ID], NULL, tb_thread_core_master, (void*)in_u);
  if(r){
    printf("error starting master thread!\n");
    }


  #if TB_THREADING_EXTRA_THREADS > 0
    uint8_t th=TB_THREADING_EXTRA_THREADS;
    while(th--){
      r=pthread_create(&(*in_u).thread[th], NULL, tb_thread_core_slave, (void*)in_u);
      if(r){
        printf("error starting slave thread![%i]\n",th);
        }
      //pthread_mutex_lock(&(*in_u).startup_mutex);
      }
  #endif

  return;
  }

//-----------------------------------------------
// 			tb_thread_ticker()
//  calls threads to action #ticks times
//-----------------------------------------------
void tb_thread_ticker( struct toobit_space* in_u, unsigned int ticks ){
  uint8_t thread_i, first_run=1;

  #if TB_SERVER_LIVE_INJECTION == 1
    uint16_t 		*buf_avail	=&(*in_u).buffer_avail;
    char 		*buf_ptr, *buf_now, *bend_ptr;
    TB_PARTICLE_TYPE	*space_ptr;
    uint16_t 		ne, ob_sz, ob_x, ob_y, row_c, col_c, row_skip;
  #endif
  while(ticks--){
    #if TB_SERVER_LIVE_INJECTION == 1
      if(*buf_avail){
        buf_ptr=(*in_u).injection_buffer;
        pthread_mutex_lock(&(*in_u).injection_mutex);
	ne=*buf_avail;
	while(ne--){

	  buf_now=buf_ptr;
	  ob_sz=*(uint16_t*)buf_now;buf_now+=2;
	  ob_x =*(uint16_t*)buf_now;buf_now+=2;
	  ob_y =*(uint16_t*)buf_now;buf_now+=2;

	  if(ob_sz<6){
	    if(ob_x>TB_SPACE_SIZE_X-ob_sz)ob_x=TB_SPACE_SIZE_X-ob_sz;
	    if(ob_y>TB_SPACE_SIZE_Y-ob_sz)ob_y=TB_SPACE_SIZE_Y-ob_sz;
	    space_ptr=(*in_u).space+(ob_y*TB_SPACE_ROW_DATA_SIZE)+(ob_x*TB_PARTICLE_DATA_SIZE);
	    row_skip=TB_SPACE_ROW_DATA_SIZE-(ob_sz*TB_PARTICLE_DATA_SIZE);
	    col_c=ob_sz;
	    while(col_c--){
	      row_c=ob_sz;
	      while(row_c--){
	        *space_ptr=*(uint16_t*)buf_now;		//later memset in chunks
	        buf_now+=2;
	        space_ptr++;
	        }
	      space_ptr+=row_skip;
	      }
	    }else{
	    unsigned int r_val, u_count=0;
	    if(ob_x>TB_SPACE_SIZE_X-ob_sz)ob_x=TB_SPACE_SIZE_X-ob_sz;
	    if(ob_y>TB_SPACE_SIZE_Y-ob_sz)ob_y=TB_SPACE_SIZE_Y-ob_sz;
	    space_ptr=(*in_u).space+(ob_y*TB_SPACE_ROW_DATA_SIZE)+(ob_x*TB_PARTICLE_DATA_SIZE);
	    row_skip=TB_SPACE_ROW_DATA_SIZE-(ob_sz*TB_PARTICLE_DATA_SIZE);
	    col_c=ob_sz;
	    r_val=random();
	    while(col_c--){
	      row_c=ob_sz;
	      while(row_c--){
	        if(r_val&1)*space_ptr=32; else *space_ptr=42;
		r_val=r_val>>1;
		if(!r_val)r_val=random();
	        space_ptr++;
	        }
	      space_ptr+=row_skip;
	      }
	    }
	  buf_ptr+=TB_SERVER_INJECTION_BUFFER_ENTRY_SIZE;
	  }
	*buf_avail=0;
        pthread_mutex_unlock(&(*in_u).injection_mutex);
	}
    #endif

    pthread_mutex_unlock(&(*in_u).thread_mutex_ready[TB_THREADING_EDGER_THREAD_ID]);
    pthread_mutex_unlock(&(*in_u).thread_mutex_ready[TB_THREADING_MASTER_THREAD_ID]);
    pthread_mutex_unlock(&(*in_u).thread_mutex_ready[0]);

    pthread_mutex_lock(&(*in_u).thread_mutex_go[TB_THREADING_EDGER_THREAD_ID]);
    pthread_mutex_lock(&(*in_u).thread_mutex_go[TB_THREADING_MASTER_THREAD_ID]);
    pthread_mutex_lock(&(*in_u).thread_mutex_go[0]);

    pthread_mutex_lock(&(*in_u).thread_mutex_ready[TB_THREADING_EDGER_THREAD_ID]);
    pthread_mutex_lock(&(*in_u).thread_mutex_ready[TB_THREADING_MASTER_THREAD_ID]);
    pthread_mutex_lock(&(*in_u).thread_mutex_ready[0]);

    pthread_mutex_unlock(&(*in_u).thread_mutex_done[TB_THREADING_EDGER_THREAD_ID]);
    pthread_mutex_unlock(&(*in_u).thread_mutex_done[TB_THREADING_MASTER_THREAD_ID]);
    pthread_mutex_unlock(&(*in_u).thread_mutex_done[0]);

    //shhh...they are working... wait for them to finish
    pthread_mutex_lock(&(*in_u).thread_mutex_end[TB_THREADING_EDGER_THREAD_ID]);
    pthread_mutex_lock(&(*in_u).thread_mutex_end[TB_THREADING_MASTER_THREAD_ID]);
    pthread_mutex_lock(&(*in_u).thread_mutex_end[0]);

    pthread_mutex_lock(&(*in_u).thread_mutex_done[TB_THREADING_EDGER_THREAD_ID]);
    pthread_mutex_lock(&(*in_u).thread_mutex_done[TB_THREADING_MASTER_THREAD_ID]);
    pthread_mutex_lock(&(*in_u).thread_mutex_done[0]);
    //all done

    memcpy((*in_u).space,(*in_u).space_next,TB_SPACE_DATA_SIZE_BYTES);
    }

  return;
  }


//-----------------------------------------------
// 			tb_thread_core_master()
//-----------------------------------------------
void *tb_thread_core_master( void *in_p ){
  usleep(10000);

  struct toobit_space *in_u=( struct toobit_space*)in_p;
  void (*funk_ptr)(struct toobit_space*, TB_PARTICLE_TYPE *, TB_PARTICLE_TYPE *, TB_PARTICLE_TYPE *, unsigned int)=(*in_u).funk_ptr_3ptr;
  uint16_t xnow,ynow;
  unsigned int self;
  TB_PARTICLE_TYPE *space_ptr=(*in_u).space, *space_now_ptr;

while(1){
  pthread_mutex_lock(&(*in_u).thread_mutex_ready[TB_THREADING_MASTER_THREAD_ID]);
  pthread_mutex_unlock(&(*in_u).thread_mutex_ready[TB_THREADING_MASTER_THREAD_ID]);
  pthread_mutex_unlock(&(*in_u).thread_mutex_go[TB_THREADING_MASTER_THREAD_ID]);
    //-------------start 'real work' of thread
    //			it runs through all, or a portion of the main body of space (everthing except perimiter)
    ynow=TB_THREADING_MASTER_RANGE_START;
    space_now_ptr=space_ptr+TB_SPACE_ROW_DATA_SIZE;
    self=TB_SPACE_SIZE_X;

    while(--ynow){
      self++;
      space_now_ptr+=TB_PARTICLE_DATA_SIZE;
      xnow=TB_SPACE_SIZE_X_MINUS_ONE;
      while(--xnow){
          funk_ptr(in_u,
		space_now_ptr-TB_SPACE_ROW_DATA_SIZE_PLUS_ONE,	
		space_now_ptr-TB_PARTICLE_DATA_SIZE,		
		space_now_ptr+TB_SPACE_ROW_DATA_SIZE_MINUS_ONE,
		self++);
        space_now_ptr+=TB_PARTICLE_DATA_SIZE;  
	}
      self++;
      space_now_ptr+=TB_PARTICLE_DATA_SIZE;  
      }
    //-------------end 'real work' of thread
  pthread_mutex_lock(&(*in_u).thread_mutex_done[TB_THREADING_MASTER_THREAD_ID]);
  pthread_mutex_unlock(&(*in_u).thread_mutex_done[TB_THREADING_MASTER_THREAD_ID]);
  pthread_mutex_unlock(&(*in_u).thread_mutex_end[TB_THREADING_MASTER_THREAD_ID]);
  }

  return;
  }

//-----------------------------------------------
// 			tb_thread_core_edger()
// the real beast code-wise
// reatlivly low load though, it just does the
// edges of the map. even at low 100x100 res
// thats only 4% of the total area but its is 
// more complex because buffers have to be made
//-----------------------------------------------
void *tb_thread_core_edger( void *in_p ){
  usleep(20000);
  struct toobit_space *in_u=( struct toobit_space*)in_p;
  //thead vars
 // uint16_t *active_ptr=(uint16_t*)&(*in_u).core_active_flags;
 //uint16_t *start_ptr=(uint16_t*)&(*in_u).core_start_flags;
  //uint16_t *end_ptr=(uint16_t*)&(*in_u).core_end_flags;
  //uint16_t *status_ptr=(uint16_t*)&(*in_u).core_status_flags;

  //edger vars
  void (*funk_ptr)(struct toobit_space*, TB_PARTICLE_TYPE *, TB_PARTICLE_TYPE *, TB_PARTICLE_TYPE *, unsigned int)=(*in_u).funk_ptr_3ptr;
  unsigned int x,y,yoff,xoff;
  TB_PARTICLE_TYPE empty_row[3]={0,0,0};
  TB_PARTICLE_TYPE partial_row1[3], partial_row2[3], partial_row3[3];
  #if TB_PARTICLE_DATA_SIZE == 1
 	 uint_fast16_t 	*p_row1_0=(uint_fast16_t *)partial_row1,
			*p_row1_1=(uint_fast16_t *)(partial_row1+1),
  	 		*p_row2_0=(uint_fast16_t *)partial_row2,
			*p_row2_1=(uint_fast16_t *)(partial_row2+1), 
  	 		*p_row3_0=(uint_fast16_t *)partial_row3,
			*p_row3_1=(uint_fast16_t *)(partial_row3+1); 
  #endif
while(1){
  pthread_mutex_lock(&(*in_u).thread_mutex_ready[TB_THREADING_EDGER_THREAD_ID]);
  pthread_mutex_unlock(&(*in_u).thread_mutex_ready[TB_THREADING_EDGER_THREAD_ID]);
  pthread_mutex_unlock(&(*in_u).thread_mutex_go[TB_THREADING_EDGER_THREAD_ID]);
    //-------------start 'real work' of thread

  /////////////////////////////////////////////////////////////////////////
  //----do the first row
  	//----do the top left corner 
	#if TB_PARTICLE_DATA_SIZE == 1
		partial_row1[0]=0;
		*p_row1_1=*(uint_fast16_t *)((*in_u).space);
		partial_row2[0]=0;
		*p_row2_1=*(uint_fast16_t *)((*in_u).space+TB_SPACE_ROW_DATA_SIZE);
	#else
		partial_row1[0]=0;
		partial_row1[1]=(*in_u).space[0];
		partial_row1[2]=(*in_u).space[1];
		partial_row2[0]=0;
		partial_row2[1]=(*in_u).space[TB_SPACE_ROW_DATA_SIZE];
		partial_row2[2]=(*in_u).space[TB_SPACE_ROW_DATA_SIZE_PLUS_ONE];
	#endif
	funk_ptr(in_u,empty_row,partial_row1,partial_row2,0);
	//----end top left corner
	//*****************************************************************
	//----do up to second last colum in first row
	x=TB_SPACE_X_LAST;
	while(--x){
	  funk_ptr(in_u,empty_row,(*in_u).space+x-TB_PARTICLE_DATA_SIZE,(*in_u).space+x+TB_SPACE_ROW_DATA_SIZE_MINUS_ONE,x);
	  }	
	//----end at second last colum of first row
	//*****************************************************************
	//----do first row last colum
	#if TB_PARTICLE_DATA_SIZE == 1
		*p_row1_0=*(uint_fast16_t *)((*in_u).space+TB_SPACE_ROW_DATA_SIZE_MINUS_TWO);
		partial_row1[2]=0;
		*p_row2_0=*(uint_fast16_t *)((*in_u).space+TB_SPACE_ROW_DATA_SIZE_MINUS_DOUBLE);
		partial_row2[2]=0;
	#else
		partial_row1[0]=(*in_u).space[TB_SPACE_ROW_DATA_SIZE_MINUS_ONE-TB_PARTICLE_DATA_SIZE];
		partial_row1[1]=(*in_u).space[TB_SPACE_ROW_DATA_SIZE_MINUS_ONE];
		partial_row1[2]=0;
		partial_row2[0]=(*in_u).space[TB_SPACE_ROW_DATA_SIZE_MINUS_ONE-TB_SPACE_ROW_DATA_SIZE_MINUS_ONE];
		partial_row2[1]=(*in_u).space[TB_SPACE_ROW_DATA_SIZE_MINUS_ONE];
		partial_row2[2]=0;
	#endif
	funk_ptr(in_u,empty_row,partial_row1,partial_row2,TB_SPACE_X_LAST);
	//----end first row last colum
  //----end first row
  /////////////////////////////////////////////////////////////////////////
  //----Loop though second row to second last row
	y=TB_SPACE_Y_LAST;
	yoff=TB_SPACE_DATA_SIZE_BYTES-TB_SPACE_ROW_DATA_SIZE;
	while(--y){
	  yoff-=TB_SPACE_ROW_DATA_SIZE;
	  ///////////////////////////////////////////////////////////////////
	  //----do first colum of row
	  #if TB_PARTICLE_DATA_SIZE == 1
		partial_row1[0]=0;
		*p_row1_1=*(uint_fast16_t *)((*in_u).space+yoff-TB_SPACE_ROW_DATA_SIZE);
		partial_row2[0]=0;
		*p_row2_1=*(uint_fast16_t *)((*in_u).space+yoff);
		partial_row3[0]=0;
		*p_row3_1=*(uint_fast16_t *)((*in_u).space+yoff+TB_SPACE_ROW_DATA_SIZE);
	  #else
	  	partial_row1[0]=0;
	  	partial_row1[1]=(*in_u).space[yoff-TB_SPACE_ROW_DATA_SIZE];
	  	partial_row1[2]=(*in_u).space[yoff+TB_PARTICLE_DATA_SIZE-TB_SPACE_ROW_DATA_SIZE];
	  	partial_row2[0]=0;
	  	partial_row2[1]=(*in_u).space[yoff];
	  	partial_row2[2]=(*in_u).space[yoff+TB_PARTICLE_DATA_SIZE];
	  	partial_row3[0]=0;
	  	partial_row3[1]=(*in_u).space[yoff+TB_SPACE_ROW_DATA_SIZE];
	  	partial_row3[2]=(*in_u).space[yoff+TB_PARTICLE_DATA_SIZE+TB_SPACE_ROW_DATA_SIZE];
	  #endif
	  funk_ptr(in_u,partial_row1,partial_row2,partial_row3,yoff);
	  //----end last colum of row
	  //*****************************************************************
	  //----do second colum to second last colum
	  // nothing here, that is done by master and slave threads
	  //----end second last colum to second last colum
	  //*****************************************************************
	  //----do last colum of row
	  xoff=yoff+TB_SPACE_ROW_DATA_SIZE_MINUS_ONE;
	  #if TB_PARTICLE_DATA_SIZE == 99
		partial_row1[0]=0;
		*p_row1_1=*(uint_fast16_t *)((*in_u).space+xoff-TB_SPACE_ROW_DATA_SIZE_MINUS_ONE);
		partial_row2[0]=0;
		*p_row2_1=*(uint_fast16_t *)((*in_u).space+xoff-TB_PARTICLE_DATA_SIZE);
		partial_row3[0]=0;
		*p_row3_1=*(uint_fast16_t *)((*in_u).space+xoff+TB_SPACE_ROW_DATA_SIZE_MINUS_ONE);
	  #else
	  	partial_row1[0]=(*in_u).space[xoff-TB_SPACE_ROW_DATA_SIZE_MINUS_ONE];
	  	partial_row1[1]=(*in_u).space[xoff-TB_SPACE_ROW_DATA_SIZE];
	  	partial_row1[2]=0;
	  	partial_row2[0]=(*in_u).space[xoff-TB_PARTICLE_DATA_SIZE];
	  	partial_row2[1]=(*in_u).space[xoff];
	  	partial_row2[2]=0;
	  	partial_row3[0]=(*in_u).space[xoff+TB_SPACE_ROW_DATA_SIZE_MINUS_ONE];
	  	partial_row3[1]=(*in_u).space[xoff+TB_SPACE_ROW_DATA_SIZE];
	  	partial_row3[2]=0;
	  #endif
	  funk_ptr(in_u,partial_row1,partial_row2,partial_row3,xoff);
	  //----end last colum of row
	  ///////////////////////////////////////////////////////////////////
	  }
  //----end second row through second last row
  //----do last row
  	//----do the bottom left corner (needs 2 byte optimization, uint16_t)
	partial_row1[0]=0;
	partial_row1[1]=(*in_u).space[TB_SPACE_UNIVERSE_SECOND_LAST_ROW];
	partial_row1[2]=(*in_u).space[TB_SPACE_UNIVERSE_SECOND_LAST_ROW+TB_PARTICLE_DATA_SIZE];
	partial_row2[0]=0;
	partial_row2[1]=(*in_u).space[TB_SPACE_UNIVERSE_LAST_ROW];
	partial_row2[2]=(*in_u).space[TB_SPACE_UNIVERSE_LAST_ROW+TB_PARTICLE_DATA_SIZE];
	funk_ptr(in_u,partial_row1,partial_row2,empty_row,TB_SPACE_UNIVERSE_LAST_ROW);
	//----end top left corner
	//*****************************************************************
	//----do up to second last colum in last row
	x=TB_SPACE_X_LAST;
	while(--x){
	  //xoff=TB_SPACE_UNIVERSE_LAST_ROW;
	  funk_ptr(in_u,
		((*in_u).space+TB_SPACE_UNIVERSE_LAST_ROW+x)-TB_SPACE_ROW_DATA_SIZE_PLUS_ONE,   ///warning..needs fix to increase data size
		((*in_u).space+TB_SPACE_UNIVERSE_LAST_ROW+x)-TB_PARTICLE_DATA_SIZE,
		empty_row,
		x+TB_SPACE_UNIVERSE_LAST_ROW);
	  }	
	//----end at second last colum of last row
	//*****************************************************************
	//----do last row last colum
	partial_row1[0]=(*in_u).space[TB_SPACE_UNIVERSE_LAST_ROW_MINUS_TWO];
	partial_row1[1]=(*in_u).space[TB_SPACE_UNIVERSE_LAST_ROW_MINUS_ONE];
	partial_row1[2]=0;
	partial_row2[0]=(*in_u).space[TB_SPACE_UNIVERSE_DATA_LAST_MINUS_ONE];
	partial_row2[1]=(*in_u).space[TB_SPACE_UNIVERSE_DATA_LAST];
	partial_row2[2]=0;
	funk_ptr(in_u,partial_row1,partial_row2,empty_row,TB_SPACE_UNIVERSE_DATA_LAST);
	//----end last row last colum
  //----end last row
  /////////////////////////////////////////////////////////////////////////

    //-------------end 'real work' of thread
  pthread_mutex_lock(&(*in_u).thread_mutex_done[TB_THREADING_EDGER_THREAD_ID]);
  pthread_mutex_unlock(&(*in_u).thread_mutex_done[TB_THREADING_EDGER_THREAD_ID]);
  pthread_mutex_unlock(&(*in_u).thread_mutex_end[TB_THREADING_EDGER_THREAD_ID]);
    }
  return;
  }

//-----------------------------------------------
// 			tb_thread_core_slave()
//-----------------------------------------------
void *tb_thread_core_slave( void *in_p ){
  usleep(30000);

  struct toobit_space *in_u=( struct toobit_space*)in_p;
  void (*funk_ptr)(struct toobit_space*, TB_PARTICLE_TYPE *, TB_PARTICLE_TYPE *, TB_PARTICLE_TYPE *, unsigned int)=(*in_u).funk_ptr_3ptr;
  uint16_t xnow,ynow;
  unsigned int self;
  TB_PARTICLE_TYPE *space_ptr=(*in_u).space, *space_now_ptr;

while(1){
  pthread_mutex_lock(&(*in_u).thread_mutex_ready[0]);
  pthread_mutex_unlock(&(*in_u).thread_mutex_ready[0]);
  pthread_mutex_unlock(&(*in_u).thread_mutex_go[0]);
    //-------------start 'real work' of thread
    //			it runs through all, or a portion of the main body of space (everthing except perimiter)
    ynow=TB_THREADING_MASTER_RANGE_START;
    space_now_ptr=space_ptr+(TB_THREADING_SEGMENT_SIZE*TB_SPACE_ROW_DATA_SIZE)+TB_SPACE_ROW_DATA_SIZE;
    self=TB_SPACE_SIZE_X+(TB_THREADING_SEGMENT_SIZE*TB_SPACE_SIZE_X);

    while(--ynow){
      self++;
      space_now_ptr+=TB_PARTICLE_DATA_SIZE;
      xnow=TB_SPACE_SIZE_X_MINUS_ONE;
      while(--xnow){
          funk_ptr(in_u,
		space_now_ptr-TB_SPACE_ROW_DATA_SIZE_PLUS_ONE,	
		space_now_ptr-TB_PARTICLE_DATA_SIZE,		
		space_now_ptr+TB_SPACE_ROW_DATA_SIZE_MINUS_ONE,
		self++);
        space_now_ptr+=TB_PARTICLE_DATA_SIZE;  
	}
      self++;
      space_now_ptr+=TB_PARTICLE_DATA_SIZE;  
      }
    //-------------end 'real work' of thread
  pthread_mutex_lock(&(*in_u).thread_mutex_done[0]);
  pthread_mutex_unlock(&(*in_u).thread_mutex_done[0]);
  pthread_mutex_unlock(&(*in_u).thread_mutex_end[0]);
  }

  return;
  }

