//----------------------------------------------\\
//	TOOBIT v0.13			    	\\
//	2d bit space simulation system      	\\
//					    	\\
//	More info watch Youtube videos	    	\\----------------------------------------------\\
//		https://www.youtube.com/playlist?list=PLmSUTHzWYMaNGqxUQunqIu3TbsDL2QnI-  	||
//												//
//		More Mad science and								//
//		  technology art								//
//			http://www.dscript.org 							//
//----------------------------------------------------------------------------------------------//
#include <toobit.h>

#define GOL_EMPTY_CHAR		32
#define GOL_FILLED_CHAR		42

struct toobit_space the_universe;


//--------------------------------------
//		simple_rules ()
//	x/y = x,y cords
//	t = output target pointer
//	n = # of neighbours
//		traditional rules
//--------------------------------------
void simple_rules( struct toobit_space* in_u, TB_PARTICLE_TYPE *r0, TB_PARTICLE_TYPE *r1, TB_PARTICLE_TYPE *r2, unsigned int self){
  int n=0;
  char top_c=0, bot_c=0, right_c=0, left_c=0;
  if(r0[0]==GOL_FILLED_CHAR){n++;top_c++;left_c++;}
  if(r0[1]==GOL_FILLED_CHAR){n++;top_c++;}
  if(r0[2]==GOL_FILLED_CHAR){n++;top_c++;right_c++;}

  if(r1[0]==GOL_FILLED_CHAR){n++;left_c++;}
  if(r1[2]==GOL_FILLED_CHAR){n++;right_c++;}

  if(r2[0]==GOL_FILLED_CHAR){n++;bot_c++;left_c++;}
  if(r2[1]==GOL_FILLED_CHAR){n++;bot_c++;}
  if(r2[2]==GOL_FILLED_CHAR){n++;bot_c++;right_c++;}

  //if(bot_c==0){(*in_u).space_next[self]=GOL_EMPTY_CHAR;return;}
  //if(top_c>1){(*in_u).space_next[self]=GOL_FILLED_CHAR;return;}
  if(top_c&&bot_c&&left_c&&right_c&&n<6){(*in_u).space_next[self]=GOL_FILLED_CHAR;return;}
  //if(n>4){(*in_u).space_next[self]=GOL_EMPTY_CHAR;return;}

  //if(right_c>2&&left_c<2){(*in_u).space_next[self]=GOL_FILLED_CHAR;return;}
  //if(right_c<2&&left_c>2){(*in_u).space_next[self]=GOL_FILLED_CHAR;return;}
  //if(top_c<2&&bot_c>2){(*in_u).space_next[self]=GOL_FILLED_CHAR;return;}
  //if(top_c>2&&bot_c<2){(*in_u).space_next[self]=GOL_FILLED_CHAR;return;}
//(*in_u).space_next[self]=GOL_EMPTY_CHAR;return;
  if((*in_u).space[self]!=GOL_FILLED_CHAR){
    if(n==4)(*in_u).space_next[self]=GOL_FILLED_CHAR;
    }else{
    (*in_u).space_next[self]=GOL_FILLED_CHAR;
    if(n<2)(*in_u).space_next[self]=GOL_EMPTY_CHAR;
    if(n>3)(*in_u).space_next[self]=GOL_EMPTY_CHAR;
    }
  return;
  }

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



  if((*in_u).space[self]!=GOL_FILLED_CHAR){
    if(n==3)(*in_u).space_next[self]=GOL_FILLED_CHAR;
    }else{
    (*in_u).space_next[self]=GOL_FILLED_CHAR;
    if(n<2)(*in_u).space_next[self]=GOL_EMPTY_CHAR;
    if(n>3)(*in_u).space_next[self]=GOL_EMPTY_CHAR;
    }
  return;
  }






//--------------------------------------
//				main ()
//--------------------------------------
int main() {
  unsigned int tc=0; 
  unsigned int next_bang=1;  unsigned int r_val,noise_level,r_buf;



  tb_init_space(&the_universe);					//initialize struct
  tb_set_physics_3ptr(&the_universe,&simple_rules);		//set physics
  tb_heat_death(&the_universe,GOL_FILLED_CHAR);			//flatten the universe to a signle value
  //tb_big_bang(&the_universe,4,GOL_FILLED_CHAR);		//start with a big bang	
  tb_server_start(&the_universe,3337);				//start the universe server


  while(1){				//----main loop
    //r_val=random();
    //noise_level=r_val&1023;
    //while(noise_level--)the_universe.space[random()%TB_SPACE_DATA_SIZE_BYTES]=42;

    //the_universe.space[4]=GOL_FILLED_CHAR;
    //tb_print_space_one_byte(&the_universe);	//print space to the screen 
    //tb_big_bang(&the_universe,next_bang+10,GOL_FILLED_CHAR);	//start with a big bang	
    //if(next_bang>20)next_bang=0;

    //progress time (universe, # time ticks)
    //tb_time_ticker_3ptr(&the_universe,1);
    tb_thread_ticker(&the_universe,1);
    usleep(100000);    
    }					//----end main loop

  return(0);
}

