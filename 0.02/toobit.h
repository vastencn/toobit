//--------------------------------------
//--------------Config------------------
//--------------------------------------

#define TB_KEEP_TIME	1	// 1=time, 0=no time (0 will completly trim the fat)
#define TB_TIME_DEPTH	1	// # depth levels, each level is a uint that overflows into the next

#define TB_PARTICLE_DATA_SIZE 		1	//bytes of information per point in space

#define TB_SPACE_SIZE_X 		50	//X resolution of space
#define TB_SPACE_SIZE_Y 		15	//Y resolution of space

#define TB_OBSERVATION_TIME_GAP		10	//How many time ticks to skip before redrawing screen



//--------------------------------------
//------------Derivatives---------------
//--------------------------------------

#define TB_SPACE_SIZE_XY 		TB_SPACE_SIZE_X * TB_SPACE_SIZE_Y
#define TB_SPACE_DATA_SIZE_BYTES 	TB_SPACE_SIZE_XY * TB_PARTICLE_DATA_SIZE




//--------------------------------------
//--------------Formats-----------------
//--------------------------------------

struct toobit_space {
  char space[TB_SPACE_DATA_SIZE_BYTES];
  #if TB_KEEP_TIME == 1
    unsigned int time[TB_TIME_DEPTH];
  #endif
  };



//--------------------------------------
//---------------Funks------------------
//--------------------------------------

void tb_heat_death( struct toobit_space* in_u, char c );
void tb_big_bang( struct toobit_space* in_u , unsigned int r, char s);

#if TB_KEEP_TIME == 1
  void tb_reset_time( struct toobit_space* in_u );
#endif



