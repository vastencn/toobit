//--------------------------------------
//--------------Config------------------
//--------------------------------------

#define TB_TIME_DEPTH			1	// # depth levels, each level is a uint32 that overflows into the next
#define TB_OBSERVATION_TIME_GAP		1	// How many time ticks to skip before redrawing screen

#define TB_PARTICLE_DATA_SIZE 		1	// bytes of information per point in space

#define TB_SPACE_SIZE_X 		20	// X resolution of space
#define TB_SPACE_SIZE_Y 		20	// Y resolution of space

#define TB_PRINT_CLEAR_SCREEN		0	// 1=clear screen before each draw, 0=no clear just draw



//--------------------------------------
//-------------Optionals----------------
//--------------------------------------
#define TB_KEEP_TIME			1	// 1=time, 0=no time
#define TB_EASY_PRINT			1	// 1=build with tb_print_xxx functions, 0=without
#define TB_SPEED_TEST			1	// 1=build with speed test libs and functions, 0=without



//--------------------------------------
//------------Derivatives---------------
//--------------------------------------

#define TB_SPACE_SIZE_XY 				TB_SPACE_SIZE_X 			* 	TB_SPACE_SIZE_Y
#define TB_SPACE_DATA_SIZE_BYTES 			TB_SPACE_SIZE_XY 			* 	TB_PARTICLE_DATA_SIZE
#define TB_SPACE_ROW_DATA_SIZE				TB_SPACE_SIZE_X				*	TB_PARTICLE_DATA_SIZE
#define TB_SPACE_ROW_DATA_SIZE_MINUS_ONE		TB_SPACE_ROW_DATA_SIZE			-	TB_PARTICLE_DATA_SIZE
#define TB_SPACE_ROW_DATA_SIZE_PLUS_ONE			TB_SPACE_ROW_DATA_SIZE			+	TB_PARTICLE_DATA_SIZE
#define TB_SPACE_Y_LAST					TB_SPACE_SIZE_Y				-	1
#define TB_SPACE_X_LAST					TB_SPACE_SIZE_X				-	1
#define TB_SPACE_UNIVERSE_DATA_SIZE			TB_SPACE_SIZE_XY			*	TB_PARTICLE_DATA_SIZE
#define TB_SPACE_UNIVERSE_DATA_LAST			TB_SPACE_UNIVERSE_DATA_SIZE		-	TB_PARTICLE_DATA_SIZE
#define TB_SPACE_UNIVERSE_DATA_LAST_MINUS_ONE		TB_SPACE_UNIVERSE_DATA_LAST		-	TB_PARTICLE_DATA_SIZE
#define TB_SPACE_UNIVERSE_LAST_ROW			TB_SPACE_UNIVERSE_DATA_SIZE		-	TB_SPACE_ROW_DATA_SIZE
#define TB_SPACE_UNIVERSE_LAST_ROW_MINUS_ONE		TB_SPACE_UNIVERSE_LAST_ROW		-	TB_PARTICLE_DATA_SIZE
#define TB_SPACE_UNIVERSE_LAST_ROW_MINUS_TWO		TB_SPACE_UNIVERSE_LAST_ROW_MINUS_ONE	-	TB_PARTICLE_DATA_SIZE
#define TB_SPACE_UNIVERSE_SECOND_LAST_ROW		TB_SPACE_UNIVERSE_LAST_ROW		-	TB_SPACE_ROW_DATA_SIZE

#define TB_SPACE_SIZE_X_MINUS_ONE			TB_SPACE_SIZE_X				-	1

#define TB_PARTICLE_TYPE	uint_fast8_t


//--------------------------------------
//---------------FLAGS------------------
//--------------------------------------
#define TB_SPEED_TEST_DEFAULT_MODE 	0



//--------------------------------------
//--------------Formats-----------------
//--------------------------------------

struct toobit_space {
  TB_PARTICLE_TYPE space[TB_SPACE_DATA_SIZE_BYTES];
  TB_PARTICLE_TYPE space_next[TB_SPACE_DATA_SIZE_BYTES];
  #if TB_KEEP_TIME == 1
    unsigned int time[TB_TIME_DEPTH];
  #endif
  };



//--------------------------------------
//---------------Funks------------------
//--------------------------------------

void tb_heat_death( struct toobit_space* in_u, TB_PARTICLE_TYPE s );
void tb_big_bang( struct toobit_space* in_u , unsigned int r, TB_PARTICLE_TYPE s);

void tb_time_ticker_xy( struct toobit_space* in_u, unsigned int tc, void (*funk_ptr)(struct toobit_space*, unsigned int, unsigned int ));
void tb_time_ticker_3row( struct toobit_space* in_u, unsigned int tc, void (*funk_ptr)(struct toobit_space*, TB_PARTICLE_TYPE *, TB_PARTICLE_TYPE *, TB_PARTICLE_TYPE *, unsigned int ));

#if TB_EASY_PRINT == 1
  void tb_print_space_one_byte( struct toobit_space* in_u );
  void tb_print_space_quarter_byte( struct toobit_space* in_u );
#endif

#if TB_KEEP_TIME == 1
  void tb_reset_time( struct toobit_space* in_u );
#endif

#if TB_SPEED_TEST == 1
void tb_speed_test_xy(char mode, struct toobit_space* in_u, unsigned int n1, unsigned int n2, void (*funk_ptr)(struct toobit_space*, unsigned int, unsigned int ));
#endif

