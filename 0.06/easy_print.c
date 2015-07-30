
//-----------------------------------------------
// 			tb_printf_space_one_byte()
// Prints the space of each point as a character. 
//  It plots a 2d "ascci art" on console screen
//  using the first byte of data as a character.
// ******REQUIRES INNER LOOP OPTIMIZATION*********
//-----------------------------------------------
void tb_print_space_one_byte( struct toobit_space* in_u ){
  unsigned int y=TB_SPACE_SIZE_Y,x,offset;
  char pstring[(TB_SPACE_SIZE_X+5)];
  #if TB_PRINT_CLEAR_SCREEN == 1
  	system("clear");				//clear screen
  #endif
  while(y--){
    x=TB_SPACE_SIZE_X;
    while(x--){
      pstring[x]=(*in_u).space[(y*TB_SPACE_SIZE_X)+x];   //fix back later
      }
    pstring[TB_SPACE_SIZE_X]=0;
    puts(pstring);
    }
  return;
  }


//-----------------------------------------------
// 			tb_printf_space_one_byte()
// Prints the space of each point as a character. 
//  It plots a 2d "ascci art" on console screen
//  using the first byte of data as a character.
// ******REQUIRES INNER LOOP OPTIMIZATION*********
//-----------------------------------------------
void tb_print_space_quarter_byte( struct toobit_space* in_u ){
  unsigned int y=TB_SPACE_SIZE_Y>>1,x,offset;
  char pstring[(TB_SPACE_SIZE_X+5)];
  char bc;
  #if TB_PRINT_CLEAR_SCREEN == 1
    system("clear");			//clear screen
  #endif			
  while(y--){
    x=TB_SPACE_SIZE_X>>1;
    while(x--){
      bc=0;
      offset=((y<<1)*TB_SPACE_SIZE_X)+(x<<1);
      if((*in_u).space[offset]==42)bc++;
      if((*in_u).space[offset+1]==42)bc++;
      offset+=TB_SPACE_SIZE_X;
      if((*in_u).space[offset]==42)bc++;
      if((*in_u).space[offset+1]==42)bc++;
      if(bc==1){
	pstring[x]='.';
	}else if(bc==2){
	pstring[x]='"';
	}else if(bc==3){
	pstring[x]='*';
	}else if(bc==4){
	pstring[x]='#';
	}else{
	pstring[x]=' ';
	}
      }
    pstring[(TB_SPACE_SIZE_X>>1)]=0;
    puts(pstring);
    }
  return;
  }
