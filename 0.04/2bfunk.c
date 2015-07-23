#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <toobit.h>


//-----------------------------------------------
// 				tb_time_ticker()
// This function recives..
//		-A pointer to the universe
//		-Number of time ticks to progress
//		-A pointer to a function--\
//		       /------------------/
//		       |
//	The function recived will be used
//	on every point in space
//		function (Universe pointer, x, y)
//-----------------------------------------------
void tb_time_ticker( struct toobit_space* in_u, unsigned int tc, void (*fun_ptr)(struct toobit_space*, unsigned int, unsigned int )){
  int x,y;
  tc=TB_OBSERVATION_TIME_GAP;
  while(tc--){			// progress through 1 observation frame of time ticks
    y=TB_SPACE_SIZE_Y;		// cycle each point in space
    while(y--){
      x=TB_SPACE_SIZE_X;
      while(x--){
      fun_ptr(in_u,x,y);	//run the function we got on each particle
      }
    }
    // copy .space_next into .space ( now=next )
    memcpy((*in_u).space,(*in_u).space_next,TB_SPACE_DATA_SIZE_BYTES);
    }
  return;
  }

//-----------------------------------------------
// 				tb_heat_death()
// Clear all space to byte value c
//		*yes i know they could be memset
//		 with one command, the struct is
//		 still changing, not safe yet 
//-----------------------------------------------
void tb_heat_death( struct toobit_space* in_u , char c){
  memset((*in_u).space,c,TB_SPACE_DATA_SIZE_BYTES);
  memset((*in_u).space_next,c,TB_SPACE_DATA_SIZE_BYTES);
  return;
  }


//-----------------------------------------------
// 				tb_big_bang()
// spawn structured enegery at spacial center point
// 	r=radius	s=enegry structure
//	d=diameter	ex=empty shell width x
//	ey=empty shell width y
//-----------------------------------------------
void tb_big_bang( struct toobit_space* in_u , unsigned int r, char s){
  unsigned int d=r<<=1,ey=(TB_SPACE_SIZE_Y-d)>>1, ex=(TB_SPACE_SIZE_X-d)>>1;
  char *space_ptr=((*in_u).space)+ey*TB_SPACE_SIZE_X+ex, *end_ptr;
  while(r--){
    end_ptr=space_ptr+d;
    memset(space_ptr,s,d);
    space_ptr+=TB_SPACE_SIZE_X;
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
void tb_printf_space_one_byte( struct toobit_space* in_u ){
  unsigned int y=TB_SPACE_SIZE_Y,x,offset;
  char pstring[(TB_SPACE_SIZE_X+5)];
  while(y--){
    x=TB_SPACE_SIZE_X;
    while(x--){
      pstring[x]=(*in_u).space[(y*TB_SPACE_SIZE_X)+x];
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
void tb_printf_space_quarter_byte( struct toobit_space* in_u ){
  unsigned int y=TB_SPACE_SIZE_Y>>1,x,offset;
  char pstring[(TB_SPACE_SIZE_X+5)];
  char bc;
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
    pstring[TB_SPACE_SIZE_X]=0;
    puts(pstring);
    }
  return;
  }


//-----------------------------------------------
// 				tb_reset_time()
// reset time counter
// *only available if timekeeping is on
//-----------------------------------------------
#if TB_KEEP_TIME == 1
  void tb_reset_time( struct toobit_space* in_u ){
    memset((char *)(*in_u).time,0,sizeof(int)*TB_TIME_DEPTH);
    (*in_u).time[0]=1;
    return;
    }
#endif



