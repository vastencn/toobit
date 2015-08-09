//--------------------------------------
//--------------Config------------------
//--------------------------------------

#define TB_TIME_DEPTH			1	// # depth levels, each level is a uint32 that overflows into the next
#define TB_OBSERVATION_TIME_GAP		100	// How many time ticks to skip before redrawing screen

#define TB_PARTICLE_DATA_SIZE 		1	// bytes of information per point in space

#define TB_SPACE_SIZE_X 		100	// X resolution of space
#define TB_SPACE_SIZE_Y 		30	// Y resolution of space

#define TB_PRINT_CLEAR_SCREEN		1	// 1=clear screen before each draw, 0=no clear just draw




//--------------------------------------
//-------------Optionals----------------
//--------------------------------------
#define TB_KEEP_TIME			1	// 1=time, 0=no time
#define TB_EASY_PRINT			1	// 1=build with tb_print_xxx functions, 0=without
#define TB_SPEED_TEST			1	// 1=build with speed test libs and functions, 0=without
#define TB_SERVER			1	// 1=build with universe server libs and funks, 0=without


//--------------------------------------
//-----------Server Config--------------
//--------------------------------------
#define TB_SERVER_MAX_REQUEST_LEN		100	// maximum bytes of request to read per server connection
#define TB_SERVER_READ_RETRIES			5	// determines tolerance for crappy client connections
#define TB_SERVER_COMMAND_GET			'G'	// request[0] character for the GET commands
#define TB_SERVER_COMMAND_GET_RAW		'r'	// request[5] character for the GET RAW commands
#define TB_SERVER_COMMAND_GET_VIEW_TERMINAL	'v'	// request[5] character for the view terminal interfaces
#define TB_SERVER_HTML_MEMORY			100	// how many k of memory to allocate to html template ram file space

//--------------------------------------
//------------Derivatives---------------
//--------------------------------------

#define TB_SPACE_SIZE_XY 				(TB_SPACE_SIZE_X 			* 	TB_SPACE_SIZE_Y			)
#define TB_SPACE_DATA_SIZE_BYTES 			(TB_SPACE_SIZE_XY 			* 	TB_PARTICLE_DATA_SIZE		)
#define TB_SPACE_ROW_DATA_SIZE				(TB_SPACE_SIZE_X			*	TB_PARTICLE_DATA_SIZE 		)
#define TB_SPACE_ROW_DATA_SIZE_MINUS_ONE		(TB_SPACE_ROW_DATA_SIZE			-	TB_PARTICLE_DATA_SIZE		)
#define TB_SPACE_ROW_DATA_SIZE_MINUS_TWO		(TB_SPACE_ROW_DATA_SIZE_MINUS_ONE	-	TB_PARTICLE_DATA_SIZE		)
#define TB_SPACE_ROW_DATA_SIZE_MINUS_DOUBLE		(TB_SPACE_ROW_DATA_SIZE_MINUS_ONE	*	2				)
#define TB_SPACE_ROW_DATA_SIZE_PLUS_ONE			(TB_SPACE_ROW_DATA_SIZE			+	TB_PARTICLE_DATA_SIZE		)
#define TB_SPACE_Y_LAST					(TB_SPACE_SIZE_Y			-	1				)
#define TB_SPACE_X_LAST					(TB_SPACE_SIZE_X			-	1				)
#define TB_SPACE_UNIVERSE_DATA_SIZE			(TB_SPACE_SIZE_XY			*	TB_PARTICLE_DATA_SIZE		)
#define TB_SPACE_UNIVERSE_DATA_LAST			(TB_SPACE_UNIVERSE_DATA_SIZE		-	TB_PARTICLE_DATA_SIZE		)
#define TB_SPACE_UNIVERSE_DATA_LAST_MINUS_ONE		(TB_SPACE_UNIVERSE_DATA_LAST		-	TB_PARTICLE_DATA_SIZE		)
#define TB_SPACE_UNIVERSE_LAST_ROW			(TB_SPACE_UNIVERSE_DATA_SIZE		-	TB_SPACE_ROW_DATA_SIZE		)
#define TB_SPACE_UNIVERSE_LAST_ROW_MINUS_ONE		(TB_SPACE_UNIVERSE_LAST_ROW		-	TB_PARTICLE_DATA_SIZE		)
#define TB_SPACE_UNIVERSE_LAST_ROW_MINUS_TWO		(TB_SPACE_UNIVERSE_LAST_ROW_MINUS_ONE	-	TB_PARTICLE_DATA_SIZE		)
#define TB_SPACE_UNIVERSE_SECOND_LAST_ROW		(TB_SPACE_UNIVERSE_LAST_ROW		-	TB_SPACE_ROW_DATA_SIZE		)
#define TB_SPACE_SIZE_X_MINUS_ONE			(TB_SPACE_SIZE_X			-	1				)
#define TB_SPACE_SIZE_X_PLUS_ONE			(TB_SPACE_SIZE_X			+	1				)
#define TB_SERVER_HTML_MEMORY_VALUE			(TB_SERVER_HTML_MEMORY			*	1000				)




//--------------------------------------
//---------------FLAGS------------------
//--------------------------------------
#define TB_SPEED_TEST_DEFAULT_MODE 	0



//--------------------------------------
//---------------TYPES------------------
//--------------------------------------

#define TB_PARTICLE_TYPE	uint_fast8_t


//--------------------------------------
//-------------INCLUDES-----------------
//--------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#if TB_SERVER == 1
  #include <pthread.h>
  #include <sys/socket.h>
  #include <arpa/inet.h>
  #include <unistd.h>
#endif

#if TB_KEEP_TIME == 1
  #include <sys/time.h>
#endif


//--------------------------------------
//--------------FORMATS-----------------
//--------------------------------------
struct toobit_space {
  TB_PARTICLE_TYPE space[TB_SPACE_SIZE_XY];
  TB_PARTICLE_TYPE space_next[TB_SPACE_SIZE_XY];

  #if TB_EASY_PRINT == 1
    char four_bytes[4];
  #endif

  #if TB_KEEP_TIME == 1
    unsigned int time[TB_TIME_DEPTH];
  #endif

  #if TB_SERVER == 1
    unsigned int server_port;
    pthread_t thread;
    int sock;
    struct sockaddr_in sockaddr;
  #endif
  };



//--------------------------------------
//---------------Funks------------------
//--------------------------------------

void tb_init_space( struct toobit_space* in_u );
void tb_heat_death( struct toobit_space* in_u, TB_PARTICLE_TYPE s );
void tb_big_bang( struct toobit_space* in_u , unsigned int r, TB_PARTICLE_TYPE s);

void tb_time_ticker_xy( struct toobit_space* in_u, unsigned int tc, void (*funk_ptr)(struct toobit_space*, unsigned int, unsigned int ));
void tb_time_ticker_3ptr( struct toobit_space* in_u, unsigned int tc, void (*funk_ptr)(struct toobit_space*, TB_PARTICLE_TYPE *, TB_PARTICLE_TYPE *, TB_PARTICLE_TYPE *, unsigned int ));

#if TB_SERVER == 1
  void *tb_server( void* in_p );
  void tb_server_start( struct toobit_space* in_u, unsigned int in_port);
  void tb_server_print_space_one_byte( struct toobit_space* in_u, int socket );
  void tb_server_print_space_quarter_byte_match( struct toobit_space* in_u , char match_char);
  void tb_server_dump_raw( struct toobit_space* in_u , int socket);
  void tb_server_view_terminal( struct toobit_space* in_u , int socket);
#endif

#if TB_EASY_PRINT == 1
  void tb_print_space_one_byte( struct toobit_space* in_u );
  void tb_print_space_quarter_byte_match( struct toobit_space* in_u , char match_char);
#endif

#if TB_KEEP_TIME == 1
  void tb_reset_time( struct toobit_space* in_u );
#endif

#if TB_SPEED_TEST == 1
  void tb_speed_test_xy(char mode, struct toobit_space* in_u, unsigned int n1, unsigned int n2, void (*funk_ptr)(struct toobit_space*, unsigned int, unsigned int ));
  void tb_speed_test_3ptr(char mode, struct toobit_space* in_u, unsigned int n1, unsigned int n2, void (*funk_ptr)(struct toobit_space*, TB_PARTICLE_TYPE *, TB_PARTICLE_TYPE *, TB_PARTICLE_TYPE *, unsigned int ));
#endif

