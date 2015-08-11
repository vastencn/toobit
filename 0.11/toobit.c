//------------------------------------------//
//	TOOBIT v0.11			    //
//	2d bit space simulation system      //
//------------------------------------------//
#include <toobit.h>

#define GOL_EMPTY_CHAR		32
#define GOL_FILLED_CHAR		42

struct toobit_space the_universe;


//--------------------------------------
//		game_of_life_rules ()
//	x/y = x,y cords
//	t = output target pointer
//	n = # of neighbours
//		traditional rules
//--------------------------------------
void game_of_life_rules( struct toobit_space* in_u, TB_PARTICLE_TYPE *r0, TB_PARTICLE_TYPE *r1, TB_PARTICLE_TYPE *r2, unsigned int self){
  int n=0;
  if(r0[0]==GOL_FILLED_CHAR)n++;
  if(r0[1]==GOL_FILLED_CHAR)n++;
  if(r0[2]==GOL_FILLED_CHAR)n++;

  if(r1[0]==GOL_FILLED_CHAR)n++;
  if(r1[2]==GOL_FILLED_CHAR)n++;

  if(r2[0]==GOL_FILLED_CHAR)n++;
  if(r2[1]==GOL_FILLED_CHAR)n++;
  if(r2[2]==GOL_FILLED_CHAR)n++;


  if((*in_u).space[self]==GOL_EMPTY_CHAR){
    if(n==3)(*in_u).space_next[self]=GOL_FILLED_CHAR;
    }else{
    (*in_u).space_next[self]=GOL_FILLED_CHAR;
    if(n<2)(*in_u).space_next[self]=GOL_EMPTY_CHAR;
    if(n>3)(*in_u).space_next[self]=GOL_EMPTY_CHAR;
    }

  return;
  }
//--------------------------------------
//		game_of_life_rules_mod ()
//	x/y = x,y cords
//	t = output target pointer
//	n = # of neighbours
//		modified rules
//--------------------------------------
void game_of_life_rules_mod( struct toobit_space* in_u, TB_PARTICLE_TYPE *r0, TB_PARTICLE_TYPE *r1, TB_PARTICLE_TYPE *r2, unsigned int self){
  int n=0;
  if(r0[0]==GOL_FILLED_CHAR)n++;
  if(r0[1]==GOL_FILLED_CHAR)n++;
  if(r0[2]==GOL_FILLED_CHAR)n++;

  if(r1[0]==GOL_FILLED_CHAR)n++;
  if(r1[2]==GOL_FILLED_CHAR)n++;

  if(r2[0]==GOL_FILLED_CHAR)n++;
  if(r2[1]==GOL_FILLED_CHAR)n++;
  if(r2[2]==GOL_FILLED_CHAR)n++;

  if((*in_u).space[self]==GOL_EMPTY_CHAR){
    if(n==3)(*in_u).space_next[self]=GOL_FILLED_CHAR;
    }else{
    (*in_u).space_next[self]=GOL_FILLED_CHAR;
    if(n<2)(*in_u).space_next[self]=GOL_EMPTY_CHAR;
    if(n>3)(*in_u).space_next[self]=GOL_EMPTY_CHAR;
    }

  n=8-n;
  if((*in_u).space_next[self]==GOL_FILLED_CHAR){
    if(n==3)(*in_u).space_next[self]=GOL_EMPTY_CHAR;
    }else{
    if(!n)(*in_u).space_next[self]=GOL_FILLED_CHAR;
    if(n>3&&n<4)(*in_u).space_next[self]=GOL_FILLED_CHAR;
    }
  return;
  }




//--------------------------------------
//				main ()
//--------------------------------------
int main() {
  unsigned int tc=0; 
  unsigned int next_bang=1;
  unsigned int r_val,noise_level,r_buf;



  tb_init_space(&the_universe);				//initialize struct
  tb_reset_time(&the_universe);				//Reset time to 1
  tb_heat_death(&the_universe,GOL_FILLED_CHAR);		//flatten the universe to a signle value
  //tb_big_bang(&the_universe,4,GOL_FILLED_CHAR);	//start with a big bang	
  tb_server_start(&the_universe,8871);			//start the universe server

  while(1){				//----main loop
    r_val=random();
    noise_level=(r_val>>2)&7;
    while(noise_level--)the_universe.space[random()%TB_SPACE_DATA_SIZE_BYTES]=42;

    //tb_print_space_quarter_byte_match(&the_universe,GOL_FILLED_CHAR);	//print space to the screen 
    tb_big_bang(&the_universe,next_bang+10,GOL_FILLED_CHAR);	//start with a big bang	
    if(next_bang>20)next_bang=0;

    //progress time (universe, # time ticks, pointer to physics function run at every point in space every tick)
    tb_time_ticker_3ptr( &the_universe, 1 , &game_of_life_rules);
    //usleep(10000);    
    }					//----end main loop

  return(0);
}

