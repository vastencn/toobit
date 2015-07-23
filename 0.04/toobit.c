//-----------------------------
//	TOOBIT v0.2
//	2d bit space simulation system

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <toobit.h>

#define GOL_EMPTY_CHAR		32
#define GOL_FILLED_CHAR		42

struct toobit_space the_universe;


//--------------------------------------
//		game_of_life_rules ()
//	x/y = x,y cords
//	t = output target pointer
//	n = # of neighbours
//--------------------------------------
void game_of_life_rules( struct toobit_space* in_u, unsigned int x, unsigned int y ){
  unsigned int offset=(TB_SPACE_SIZE_X*y)+x,yend=TB_SPACE_SIZE_Y-1,xend=TB_SPACE_SIZE_X-1;
  char n=0;
  (*in_u).space_next[offset]=(*in_u).space[offset];

  if(x>0){
    if(y>0)if((*in_u).space[(offset-TB_SPACE_SIZE_X)-1]==GOL_FILLED_CHAR)n++;  	//top-left
    if((*in_u).space[offset-1]==GOL_FILLED_CHAR)n+=2;				//left
    if(y<yend)if((*in_u).space[offset+TB_SPACE_SIZE_X-1]==GOL_FILLED_CHAR)n++;	//bot-left
    }
  if(y>0){
    if((*in_u).space[(offset-TB_SPACE_SIZE_X)]==GOL_FILLED_CHAR)n+=2;		//top
    if(x<xend)if((*in_u).space[(offset-TB_SPACE_SIZE_X)+1]==GOL_FILLED_CHAR)n++;	//top-right
    }
  if(y<yend){
    if((*in_u).space[(offset+TB_SPACE_SIZE_X)]==GOL_FILLED_CHAR)n+=2;		//bot
    if(x<xend)if((*in_u).space[(offset+TB_SPACE_SIZE_X)+1]==GOL_FILLED_CHAR)n++;	//bot right
    }
  if(x<xend){
    if((*in_u).space[offset+1]==GOL_FILLED_CHAR)n+=2;				//right
    }

  if((*in_u).space[offset]==GOL_EMPTY_CHAR){
    if(n>3&&n<6)(*in_u).space_next[offset]=GOL_FILLED_CHAR;
    }else{
    if(n<3)(*in_u).space_next[offset]=GOL_EMPTY_CHAR;
    if(n>5)(*in_u).space_next[offset]=GOL_EMPTY_CHAR;
    }

  return;
  }



//--------------------------------------
//				main ()
//--------------------------------------
int main() {
  unsigned int tc=0; 
  unsigned int next_bang=5;
  unsigned int r_val,noise_level,r_buf;


  tb_heat_death(&the_universe,GOL_EMPTY_CHAR);	//flatten the universe to a signle value
  tb_reset_time(&the_universe);		//Reset time to 1
  tb_big_bang(&the_universe,8,GOL_FILLED_CHAR);	//materialize energy(universe, radius, energy structure )
  

  while(1){				//----main loop
    r_val=random();			// prep a random number for general purpose

    system("clear");				//clear screen

    tb_printf_space_one_byte(&the_universe);	//print space to the screen 

    if(next_bang--<1){					//"big-bomber"
      next_bang=10;				//   repetitive big bangs
      tb_big_bang(&the_universe,3,GOL_FILLED_CHAR);
      }  

    tb_time_ticker( &the_universe, TB_OBSERVATION_TIME_GAP, &game_of_life_rules);
    usleep(60000);    
    }					//----end main loop

  return(0);
}

