//needs tmp 2 byte optimization
//-----------------------------------------------
// 			    tb_time_ticker_3row()
// This function recives..
//		-A pointer to the universe
//		-Number of time ticks to progress
//------------------------------------------------
//   Pointer now embeded in universe structure
//------------------------------------------------
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
void tb_time_ticker_3ptr( struct toobit_space* in_u, unsigned int tc){
  void (*funk_ptr)(struct toobit_space*, TB_PARTICLE_TYPE *, TB_PARTICLE_TYPE *, TB_PARTICLE_TYPE *, unsigned int)=(*in_u).funk_ptr_3ptr;
  unsigned int x,y,yoff,xoff;
  TB_PARTICLE_TYPE empty_row[3]={0,0,0};
  TB_PARTICLE_TYPE partial_row1[3], partial_row2[3], partial_row3[3];

  #if TB_SERVER_LIVE_INJECTION == 1
    uint16_t 		*buf_avail	=&(*in_u).buffer_avail;
    char 		*buf_ptr	=(*in_u).injection_buffer, *buf_now, *end_ptr;
    TB_PARTICLE_TYPE	*space_ptr;
    uint16_t 		ne, ob_sz, ob_x, ob_y, row_c, col_c, row_skip;
  #endif

  #if TB_PARTICLE_DATA_SIZE == 1
 	 uint_fast16_t 	*p_row1_0=(uint_fast16_t *)partial_row1,
			*p_row1_1=(uint_fast16_t *)(partial_row1+1),
  	 		*p_row2_0=(uint_fast16_t *)partial_row2,
			*p_row2_1=(uint_fast16_t *)(partial_row2+1), 
  	 		*p_row3_0=(uint_fast16_t *)partial_row3,
			*p_row3_1=(uint_fast16_t *)(partial_row3+1); 
  #endif
  
  while(tc--){//start loop

    #if TB_SERVER_LIVE_INJECTION == 1
      if(*buf_avail){
        pthread_mutex_lock(&(*in_u).injection_mutex);
	ne=*buf_avail;
	
	while(ne--){
	  buf_now=buf_ptr;
	  ob_sz=*(uint16_t*)buf_now;buf_now+=2;
	  ob_x =*(uint16_t*)buf_now;buf_now+=2;
	  ob_y =*(uint16_t*)buf_now;buf_now+=2;

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

	  buf_ptr+=TB_SERVER_INJECTION_BUFFER_ENTRY_SIZE;
	  }
	*buf_avail=0;
        pthread_mutex_unlock(&(*in_u).injection_mutex);
	}
    #endif
//return;

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
	  x=TB_SPACE_X_LAST;
	  xoff=yoff;
	  while(--x){
	    xoff+=TB_PARTICLE_DATA_SIZE; 
	    funk_ptr(in_u,
		(*in_u).space+(xoff-TB_SPACE_ROW_DATA_SIZE_PLUS_ONE),	//OPTIMIZATION REQUIRED
		(*in_u).space+xoff-TB_PARTICLE_DATA_SIZE,		//THREE SCROLLING POINTERS
		(*in_u).space+xoff+TB_SPACE_ROW_DATA_SIZE_MINUS_ONE,
		xoff);  
	    }
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
	funk_ptr(in_u,empty_row,partial_row1,partial_row2,TB_SPACE_UNIVERSE_DATA_LAST);
	//----end last row last colum
  //----end last row
  /////////////////////////////////////////////////////////////////////////
  memcpy((*in_u).space,(*in_u).space_next,TB_SPACE_DATA_SIZE_BYTES);
  }//end loop
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
//	The function recieved will be used
//	on every point in space
//		function (Universe pointer, x, y)
//-----------------------------------------------
void tb_time_ticker_xy( struct toobit_space* in_u, unsigned int tc, void (*funk_ptr)(struct toobit_space*, unsigned int, unsigned int )){
  int x,y;
 // tc=TB_OBSERVATION_TIME_GAP;
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
