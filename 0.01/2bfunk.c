#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <toobit.h>


//-----------------------------------------------
// 				tb_heat_death()
// Clear all space to byte value c
//-----------------------------------------------
void tb_heat_death( struct toobit_space* in_u , char c){
  memset((*in_u).space,c,TB_SPACE_DATA_SIZE_BYTES);
  return;
  }


//-----------------------------------------------
// 				tb_big_bang()
// spawn structured enegery at spacial center point
// 	r=radius	s=enegry structure
//	d=diameter	e=empty shell width
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
//     ******REQUIRES OPTIMIZATION*********
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
// 				tb_reset_time()
// *only available if timekeeping is on
// reset time counter
//-----------------------------------------------
#if TB_KEEP_TIME == 1
  void tb_reset_time( struct toobit_space* in_u ){
    memset((char *)(*in_u).time,0,sizeof(int)*TB_TIME_DEPTH);
    (*in_u).time[0]=1;
    return;
    }
#endif



