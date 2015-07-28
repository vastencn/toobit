//------------------------------------------//
//	TOOBIT v0.5			    //
//	2d bit space simulation system      //
//------------------------------------------//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <toobit.h>

#define GOL_EMPTY_CHAR		32
#define GOL_FILLED_CHAR		42

struct toobit_space the_universe;


//--------------------------------------
//		game_of_life_rules_3row ()
//	x/y = x,y cords
//	t = output target pointer
//	n = # of neighbours
//--------------------------------------
void game_of_life_rules_3row( struct toobit_space* in_u, char *r0, char *r1, char *r2 , unsigned int self){
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
    if((*in_u).space[offset-1]==GOL_FILLED_CHAR)n++;				//left
    if(y<yend)if((*in_u).space[offset+TB_SPACE_SIZE_X-1]==GOL_FILLED_CHAR)n++;	//bot-left
    }
  if(y>0){
    if((*in_u).space[(offset-TB_SPACE_SIZE_X)]==GOL_FILLED_CHAR)n++;		//top
    if(x<xend)if((*in_u).space[(offset-TB_SPACE_SIZE_X)+1]==GOL_FILLED_CHAR)n++;//top-right
    }
  if(y<yend){
    if((*in_u).space[(offset+TB_SPACE_SIZE_X)]==GOL_FILLED_CHAR)n++;		//bot
    if(x<xend)if((*in_u).space[(offset+TB_SPACE_SIZE_X)+1]==GOL_FILLED_CHAR)n++;//bot right
    }
  if(x<xend){
    if((*in_u).space[offset+1]==GOL_FILLED_CHAR)n++;				//right
    }

  if((*in_u).space[offset]==GOL_EMPTY_CHAR){
    if(n==3)(*in_u).space_next[offset]=GOL_FILLED_CHAR;
    }else{
    (*in_u).space_next[offset]=GOL_FILLED_CHAR;
    if(n<2)(*in_u).space_next[offset]=GOL_EMPTY_CHAR;
    if(n>3)(*in_u).space_next[offset]=GOL_EMPTY_CHAR;
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
  tb_reset_time(&the_universe);			//Reset time to 1

  tb_big_bang(&the_universe,10,GOL_FILLED_CHAR);	
  the_universe.space[0]=GOL_EMPTY_CHAR;
  tb_print_space_one_byte(&the_universe);

printf("----------------------------------------------\n");

  tb_time_ticker_xy( &the_universe, TB_OBSERVATION_TIME_GAP, &game_of_life_rules);
  tb_print_space_one_byte(&the_universe);

printf("----------------------------------------------\n");  
tb_heat_death(&the_universe,GOL_EMPTY_CHAR);
  tb_big_bang(&the_universe,10,GOL_FILLED_CHAR);
  the_universe.space[0]=GOL_EMPTY_CHAR;
  tb_print_space_one_byte(&the_universe);

printf("----------------------------------------------\n");
  tb_time_ticker_3row( &the_universe, TB_OBSERVATION_TIME_GAP, &game_of_life_rules_3row);
  tb_print_space_one_byte(&the_universe);

return;

  while(1){				//----main loop
    r_val=random();			// prep a random number for general purpose

    tb_print_space_one_byte(&the_universe);	//print space to the screen 

    if(next_bang--<1){				//"big-bomber"
      next_bang=10;				//   repetitive big bangs
      tb_big_bang(&the_universe,3,GOL_FILLED_CHAR);
      }  

    //progress time (universe, # time ticks, pointer to physics function run at every point in space every tick)
    tb_time_ticker_xy( &the_universe, TB_OBSERVATION_TIME_GAP, &game_of_life_rules);
    usleep(60000);    
    }					//----end main loop

  return(0);
}

