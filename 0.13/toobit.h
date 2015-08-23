//--------------------------------------
//--------------Config------------------
//--------------------------------------

//time not yet implemented
#define TB_TIME_DEPTH			1	// # depth levels, each level is a uint32 that overflows into the next
#define TB_PARTICLE_DATA_SIZE 		1	// bytes of information per point in space
#define TB_SPACE_SIZE_X 		700	// X resolution of space
#define TB_SPACE_SIZE_Y 		400	// Y resolution of space




//--------------------------------------
//-------------Optionals----------------
//--------------------------------------
#define TB_KEEP_TIME			1	// 1=time, 0=no time
#define TB_EASY_PRINT			1	// 1=build with tb_print_xxx functions, 0=without
#define TB_SPEED_TEST			1	// 1=build with speed test libs and functions, 0=without
#define TB_THREADING			1	// 1=build with threading libs and funks, 0=without
#define TB_SERVER			1	// 1=build with universe server libs and funks, 0=without
#define TB_SERVER_INJECTION		1	// 1=build with universe server injection, 0=without
#define TB_SERVER_LIVE_INJECTION	1	// 1=build auto-injection into time ticker, 0=without
#define TB_BASIC_TICKER			1	// 1=build with non-threaded ticker functions, 0=without
#define TB_PRINT_CLEAR_SCREEN		1	// 1=clear screen before each console draw, 0=no clear just draw
//need to add function for manual injection


//--------------------------------------
//-----------Thread Config--------------
//--------------------------------------
#define TB_THREADING_EXTRA_THREADS		1			// default 2, this is how many extra (max 16 total,max extra is 14)
#define TB_THREADING_MASTER_MASK		0b1000000000000000	// mask for master thread bit
#define TB_THREADING_EDGER_MASK			0b0100000000000000	// mask for edger thread bit
#define TB_THREADING_START_WAIT_MICROS		100000			// how long threads delay between polls when waiting for tasks
#define TB_THREADING_DONE_WAIT_MICROS		100000			// how long threads delay between polls when waiting after tasks
#define TB_THREADING_TICKER_STATUS_WAIT_MICROS	1000			// how long to wait between checks of thread status flags
#define TB_THREADING_TICKER_FINISH_WAIT_MICROS	1000			// how long to wait between checks of task finished flags
#define TB_THREADING_WAIT_FOR_EDGER_MICROS	1000			// how long to wait between checks of edger finished flags

//--------------------------------------
//-----------Server Config--------------
//--------------------------------------
#define TB_SERVER_MAX_REQUEST_LEN		100	// maximum bytes of request to read per server connection
#define TB_SERVER_READ_RETRIES			5	// determines tolerance for crappy client connections
#define TB_SERVER_COMMAND_GET			'G'	// request[0] character for the GET commands
#define TB_SERVER_COMMAND_GET_RAW		'r'	// request[5] character for the GET RAW commands
#define TB_SERVER_COMMAND_GET_VIEW_TERMINAL	'v'	// request[5] character for the view terminal interfaces
#define TB_SERVER_COMMAND_GET_INJECT		'i'	// request[5] character for injections
#define TB_SERVER_HTML_MEMORY			100	// how many k of memory to allocate to html template ram file space
#define TB_SERVER_HTML_VIEW_TEMPLATE		"html/view.tmpl"

#define TB_SERVER_INJECTION_BUFFER_ENTRY_SIZE		255	// length of each entry in buffer	=l
#define TB_SERVER_INJECTION_BUFFER_NUM_ENTRIES		100	// number of entries in buffer		=n  l*n=buffer memory size
#define TB_SERVER_INJECTION_BUFFER_LOCK_DELAY		10	// us to wait before re-checking lock on buffer

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
#define TB_SPACE_SIZE_Y_MINUS_ONE			(TB_SPACE_SIZE_Y			-	1				)
#define TB_SPACE_SIZE_X_PLUS_ONE			(TB_SPACE_SIZE_X			+	1				)
#define TB_SPACE_SIZE_Y_MINUS_EDGE			(TB_SPACE_SIZE_Y			-	2				)

#define TB_SERVER_HTML_MEMORY_VALUE			(TB_SERVER_HTML_MEMORY			*	1000				)
#define TB_SERVER_INJECTION_BUFFER_SIZE			(TB_SERVER_INJECTION_BUFFER_ENTRY_SIZE  * TB_SERVER_INJECTION_BUFFER_NUM_ENTRIES)

#define TB_THREADING_TOTAL_THREADS			(TB_THREADING_EXTRA_THREADS		+	2				)
#define TB_THREADING_GROUP_THREADS			(TB_THREADING_TOTAL_THREADS		-	1				)
#define TB_THREADING_MASTER_THREAD_ID			(TB_THREADING_TOTAL_THREADS		-	1				)
#define TB_THREADING_EDGER_THREAD_ID			(TB_THREADING_TOTAL_THREADS		-	2				)
#define TB_THREADING_MASTER_MASK_INVERSE		(TB_THREADING_MASTER_MASK		^	0xFF				)
#define TB_THREADING_EDGER_MASK_INVERSE			(TB_THREADING_EDGER_MASK		^	0xFF				)
#define TB_THREADING_DUTY_ROSTER 			(TB_THREADING_MASTER_MASK		|	TB_THREADING_EDGER_MASK		)
#define TB_THREADING_SEGMENT_REMAINDER			(TB_SPACE_SIZE_Y_MINUS_EDGE		%	TB_THREADING_GROUP_THREADS	)
#define TB_THREADING_SEGMENTS_NO_REMAINDER 		(TB_SPACE_SIZE_Y_MINUS_EDGE		-	TB_THREADING_SEGMENT_REMAINDER	)
#define TB_THREADING_SEGMENT_SIZE 			(TB_THREADING_SEGMENTS_NO_REMAINDER	/	TB_THREADING_GROUP_THREADS	)
#define TB_THREADING_ONE_SEGMENT_PLUS_REMAINDER		(TB_THREADING_SEGMENT_SIZE		+	TB_THREADING_SEGMENT_REMAINDER	)
#define TB_THREADING_MASTER_RANGE_START			(TB_THREADING_ONE_SEGMENT_PLUS_REMAINDER+	1				)



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
#include <sys/types.h>

#if TB_SERVER == 1 || TB_THREADING == 1
  #include <pthread.h>
#endif

#if TB_SERVER == 1
  #include <sys/socket.h>
  #include <arpa/inet.h>
  #include <unistd.h>
  #include <sys/stat.h>
  #include <fcntl.h>
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
  void (*funk_ptr_3ptr)(struct toobit_space*, TB_PARTICLE_TYPE *, TB_PARTICLE_TYPE *, TB_PARTICLE_TYPE *, unsigned int);//not done

  #if TB_EASY_PRINT == 1
    char four_bytes[4];
  #endif

  #if TB_KEEP_TIME == 1
    unsigned int time[TB_TIME_DEPTH];
  #endif

  #if TB_SERVER == 1
    unsigned int server_port;
    pthread_t server_thread;
    int sock;
    struct sockaddr_in sockaddr;
  #endif

  #if TB_SERVER_INJECTION == 1
    char injection_buffer[TB_SERVER_INJECTION_BUFFER_SIZE];
    uint16_t buffer_avail;
    pthread_mutex_t injection_mutex;
  #endif

  #if TB_THREADING == 1
    pthread_t thread[TB_THREADING_TOTAL_THREADS];
    char thread_status[TB_THREADING_TOTAL_THREADS];
    pthread_mutex_t thread_mutex_ready[TB_THREADING_TOTAL_THREADS];
    pthread_mutex_t thread_mutex_go[TB_THREADING_TOTAL_THREADS];
    pthread_mutex_t thread_mutex_done[TB_THREADING_TOTAL_THREADS];
    pthread_mutex_t thread_mutex_end[TB_THREADING_TOTAL_THREADS];
    pthread_mutex_t startup_mutex;
    pthread_mutex_t edger_mutex;
    uint8_t thread_id_holder;
  #endif
  };



//--------------------------------------
//---------------Funks------------------
//--------------------------------------

void tb_init_space( struct toobit_space* in_u );
void tb_set_physics_3ptr( struct toobit_space* in_u, void (*funk_ptr)(struct toobit_space*, TB_PARTICLE_TYPE *, TB_PARTICLE_TYPE *, TB_PARTICLE_TYPE *, unsigned int));
void tb_heat_death( struct toobit_space* in_u, TB_PARTICLE_TYPE s );
void tb_big_bang( struct toobit_space* in_u , unsigned int r, TB_PARTICLE_TYPE s);

#if TB_BASIC_TICKER == 1
  void tb_time_ticker_xy( struct toobit_space* in_u, unsigned int tc, void (*funk_ptr)(struct toobit_space*, unsigned int, unsigned int ));
  void tb_time_ticker_3ptr( struct toobit_space* in_u, unsigned int tc);
#endif

#if TB_SERVER == 1
  void *tb_server( void* in_p );
  void tb_server_start( struct toobit_space* in_u, unsigned int in_port);
  void tb_server_print_space_one_byte( struct toobit_space* in_u, int socket );
  void tb_server_print_space_quarter_byte_match( struct toobit_space* in_u , char match_char);
  void tb_server_dump_raw( struct toobit_space* in_u , int socket);
  void tb_server_view_terminal( struct toobit_space* in_u , int socket);
  char *tb_server_load_template(char *path);
  void tb_server_inject( struct toobit_space* in_u , int socket, int rlen, char *rptr);
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

#if TB_THREADING == 1
  void tb_thread_core_init( struct toobit_space* in_u );
  void tb_thread_ticker( struct toobit_space* in_u, unsigned int ticks );
  void *tb_thread_core_edger( void *in_p );
  void *tb_thread_core_master( void *in_p );
  void *tb_thread_core_slave( void *in_p );
#endif

