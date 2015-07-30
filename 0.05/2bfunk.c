#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <toobit.h>

#if TB_SPEED_TEST == 1
	#include <sys/time.h>
#endif


//needs tmp 2 byte optimization
//-----------------------------------------------
// 			    tb_time_ticker_3row()
// This function recives..
//		-A pointer to the universe
//		-Number of time ticks to progress
//		-A pointer to a function--\
//		       /------------------/
//		       |
//  The function recived will be used
//  on every point in space
//	function (Universe pointer, r0, r1, r2, self)
//		r(0,1,2) = row data strings
//		r1[1] = self value
//		self = space element id of self
//-----------------------------------------------
void tb_time_ticker_3row( struct toobit_space* in_u, unsigned int tc, void (*funk_ptr)(struct toobit_space*, TB_PARTICLE_TYPE *, TB_PARTICLE_TYPE *, TB_PARTICLE_TYPE *, unsigned int)){
  unsigned int x,y,yoff,xoff;
  TB_PARTICLE_TYPE empty_row[3]={0,0,0};
  TB_PARTICLE_TYPE partial_row1[3], partial_row2[3], partial_row3[3];

  #if TB_PARTICLE_DATA_SIZE == 1
 	 uint_fast16_t 	*p_row1_0=(uint_fast16_t *)partial_row1,
			*p_row1_1=(uint_fast16_t *)(partial_row1+1),
  	 		*p_row2_0=(uint_fast16_t *)partial_row2,
			*p_row2_1=(uint_fast16_t *)(partial_row2+1); 
  #endif

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
	  funk_ptr(in_u,empty_row,(*in_u).space+x-TB_PARTICLE_DATA_SIZE,(*in_u).space+x-TB_PARTICLE_DATA_SIZE+TB_SPACE_ROW_DATA_SIZE,x);
	  }	
	//----end at second last colum of first row
	//*****************************************************************
	//----do first row last colum
	#if TB_PARTICLE_DATA_SIZE == 99 //////NEED RETURN TO VALUE 1 WHEN DONE
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
	  partial_row1[0]=0;
	  partial_row1[1]=(*in_u).space[yoff-TB_SPACE_ROW_DATA_SIZE];
	  partial_row1[2]=(*in_u).space[yoff+TB_PARTICLE_DATA_SIZE-TB_SPACE_ROW_DATA_SIZE];
	  partial_row2[0]=0;
	  partial_row2[1]=(*in_u).space[yoff];
	  partial_row2[2]=(*in_u).space[yoff+TB_PARTICLE_DATA_SIZE];
	  partial_row3[0]=0;
	  partial_row3[1]=(*in_u).space[yoff+TB_SPACE_ROW_DATA_SIZE];
	  partial_row3[2]=(*in_u).space[yoff+TB_PARTICLE_DATA_SIZE+TB_SPACE_ROW_DATA_SIZE];
	  funk_ptr(in_u,partial_row1,partial_row2,partial_row3,yoff);
	  //----end last colum of row
	  //*****************************************************************
	  //----do second colum to second last colum
	  x=TB_SPACE_X_LAST;
	  xoff=yoff;
	  while(--x){
	    funk_ptr(in_u,
		(*in_u).space+xoff-TB_SPACE_ROW_DATA_SIZE,
		(*in_u).space+xoff,
		(*in_u).space+xoff+TB_SPACE_ROW_DATA_SIZE,
		xoff+TB_PARTICLE_DATA_SIZE);
	    xoff+=TB_PARTICLE_DATA_SIZE;  	  
	    }
	  //----end second last colum to second last colum
	  //*****************************************************************
	  //----do last colum of row
	  xoff=yoff+TB_SPACE_ROW_DATA_SIZE_MINUS_ONE;
	  partial_row1[0]=(*in_u).space[xoff-TB_SPACE_ROW_DATA_SIZE_MINUS_ONE];
	  partial_row1[1]=(*in_u).space[xoff-TB_SPACE_ROW_DATA_SIZE];
	  partial_row1[2]=0;
	  partial_row2[0]=(*in_u).space[xoff-TB_PARTICLE_DATA_SIZE];
	  partial_row2[1]=(*in_u).space[xoff];
	  partial_row2[2]=0;
	  partial_row3[0]=(*in_u).space[xoff+TB_SPACE_ROW_DATA_SIZE_MINUS_ONE];
	  partial_row3[1]=(*in_u).space[xoff+TB_SPACE_ROW_DATA_SIZE];
	  partial_row3[2]=0;
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
		(*in_u).space+TB_SPACE_UNIVERSE_LAST_ROW+x-TB_PARTICLE_DATA_SIZE-TB_SPACE_ROW_DATA_SIZE,
		(*in_u).space+TB_SPACE_UNIVERSE_LAST_ROW+x-TB_PARTICLE_DATA_SIZE,
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
	funk_ptr(in_u,empty_row,partial_row1,partial_row2,TB_SPACE_UNIVERSE_DATA_LAST);
	//----end last row last colum
  //----end last row
  /////////////////////////////////////////////////////////////////////////
  memcpy((*in_u).space,(*in_u).space_next,TB_SPACE_DATA_SIZE_BYTES);
  return;
  }


//-----------------------------------------------
// 			      tb_time_ticker_xy()
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
void tb_time_ticker_xy( struct toobit_space* in_u, unsigned int tc, void (*funk_ptr)(struct toobit_space*, unsigned int, unsigned int )){
  int x,y;
  tc=TB_OBSERVATION_TIME_GAP;
  while(tc--){			// progress through 1 observation frame of time ticks
    y=TB_SPACE_SIZE_Y;		// cycle each point in space
    while(y--){
      x=TB_SPACE_SIZE_X;
      while(x--){
      funk_ptr(in_u,x,y);	//run the function we got on each point in space
      }
    }
    // copy .space_next into .space ( now=next )
    memcpy((*in_u).space,(*in_u).space_next,TB_SPACE_UNIVERSE_DATA_SIZE);
    }
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
  char *space_ptr=((*in_u).space)+ey*TB_SPACE_SIZE_X+ex;
  while(r--){
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
void tb_print_space_one_byte( struct toobit_space* in_u ){
  unsigned int y=TB_SPACE_SIZE_Y,x,offset;
  char pstring[(TB_SPACE_SIZE_X+5)];
  #if TB_PRINT_CLEAR_SCREEN == 1
  	system("clear");				//clear screen
  #endif
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
////not done
#if TB_KEEP_TIME == 1
  void tb_reset_time( struct toobit_space* in_u ){
    memset((char *)(*in_u).time,0,sizeof(int)*TB_TIME_DEPTH);
    (*in_u).time[0]=1;
    return;
    }
#endif

//-----------------------------------------------
// 				tb_speed_test_xy()
// speed test the xy time ticker using
// given physics rules
//-----------------------------------------------
/////not done
#if TB_SPEED_TEST == 1
  void tb_speed_test_xy(char mode, struct toobit_space* in_u, unsigned int n1, unsigned int n2, void (*funk_ptr)(struct toobit_space*, unsigned int, unsigned int )){
    struct toobit_space tmp_universe;
    struct timeval tv1,tv2;
    time_t now;
 
    memcpy(tmp_universe.space,(*in_u).space,TB_SPACE_UNIVERSE_DATA_SIZE);

    switch(mode){
      case TB_SPEED_TEST_DEFAULT_MODE:
        gettimeofday(&tv1,NULL);
        while(n1--){
          tb_time_ticker_xy(&tmp_universe, n2, funk_ptr);
          }
        gettimeofday(&tv2,NULL); 
	break;
      }

    return;
    }
#endif



