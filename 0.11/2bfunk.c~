#include <toobit.h>

#include <time_ticker.c>

#if TB_EASY_PRINT == 1
  #include <easy_print.c>
#endif

#if TB_SPEED_TEST == 1
  #include <speed_test.c>
#endif

#if TB_SERVER == 1
  #include <server.c>
#endif


char default_four_bytes[4]={'.','"','*','#'};



//-----------------------------------------------
// 				tb_init_space()
// Some simple init
//-----------------------------------------------
void tb_init_space( struct toobit_space* in_u ){
  memset((*in_u).space,0,TB_SPACE_UNIVERSE_DATA_SIZE);
  memset((*in_u).space_next,0,TB_SPACE_UNIVERSE_DATA_SIZE);
  memcpy((*in_u).four_bytes,default_four_bytes,4);
  return;
  }

//-----------------------------------------------
// 				tb_heat_death()
// Clear all space to byte value c
//-----------------------------------------------
void tb_heat_death( struct toobit_space* in_u , TB_PARTICLE_TYPE s){
  memset((*in_u).space,s,TB_SPACE_UNIVERSE_DATA_SIZE);
  memset((*in_u).space_next,s,TB_SPACE_UNIVERSE_DATA_SIZE);
  return;
  }


//-----------------------------------------------
// 				tb_big_bang()
// spawn structured enegery at spacial center point
// 	r=radius	s=enegry structure
//	d=diameter	ex=empty shell width x
//	ey=empty shell width y
//-----------------------------------------------
void tb_big_bang( struct toobit_space* in_u , unsigned int r, TB_PARTICLE_TYPE s){
  unsigned int d=r<<=1,ey=(TB_SPACE_SIZE_Y-d)>>1, ex=(TB_SPACE_SIZE_X-d)>>1;
  char *space_ptr1=((*in_u).space)+ey*TB_SPACE_SIZE_X+ex,
       *space_ptr2=((*in_u).space_next)+ey*TB_SPACE_SIZE_X+ex;
  while(r--){
    memset(space_ptr1,s,d);
    memset(space_ptr2,s,d);
    space_ptr1+=TB_SPACE_SIZE_X;
    space_ptr2+=TB_SPACE_SIZE_X;
    }
  return;
  }




//-----------------------------------------------
// 				tb_reset_time()
// reset time counter
// *only available if timekeeping is on
//-----------------------------------------------
////not done
#if TB_KEEP_TIME == 1
  void tb_reset_time( struct toobit_space* in_u ){
    memset((char *)(*in_u).time,0,sizeof(int)*TB_TIME_DEPTH);
    (*in_u).time[0]=1;
    return;
    }
#endif





