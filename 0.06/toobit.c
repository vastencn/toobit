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
void game_of_life_rules_3row( struct toobit_space* in_u, TB_PARTICLE_TYPE *r0, TB_PARTICLE_TYPE *r1, TB_PARTICLE_TYPE *r2, unsigned int self){
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
void game_of_life_rules2_3row( struct toobit_space* in_u, TB_PARTICLE_TYPE *r0, TB_PARTICLE_TYPE *r1, TB_PARTICLE_TYPE *r2, unsigned int self){//invrulmaant
  int n,n_top=0, n_bot=0, n_left=0, n_right=0;
  if(r0[0]==GOL_FILLED_CHAR){n_top++;n_left++;}
  if(r0[1]==GOL_FILLED_CHAR)n_top+=2;
  if(r0[2]==GOL_FILLED_CHAR){n_top++;n_right++;}

  if(r1[0]==GOL_FILLED_CHAR)n_left+=2;
  if(r1[2]==GOL_FILLED_CHAR)n_right+=2;

  if(r2[0]==GOL_FILLED_CHAR){n_bot++;n_left++;};
  if(r2[1]==GOL_FILLED_CHAR)n_bot+=2;
  if(r2[2]==GOL_FILLED_CHAR){n_bot++;n_right++;}

  n=n_bot+n_top+n_left+n_right;

  //if(n_top>2&&!n_bot&&!n_left&&!n_right)(*in_u).space_next[self]=GOL_FILLED_CHAR;
  //if(n_bot>2&&!n_top&&!n_left&&!n_right)(*in_u).space_next[self]=GOL_FILLED_CHAR;
  //if(n_left>2&&!n_right&&!n_top&&!n_bot)(*in_u).space_next[self]=GOL_FILLED_CHAR;
  //if(n_right>2&&!n_left&&!n_top&&!n_bot)(*in_u).space_next[self]=GOL_FILLED_CHAR;
  //if(n_top==n_bot||n_left==n_right)(*in_u).space_next[self]=GOL_EMPTY_CHAR;
  //if(n_top==2&&n_bot==2&&n_left==2&&n_right==2)(*in_u).space_next[self]=GOL_EMPTY_CHAR;

  if((*in_u).space[self]==GOL_EMPTY_CHAR){
    if(n==6)(*in_u).space_next[self]=GOL_FILLED_CHAR;
    }else{
    if(n<4)(*in_u).space_next[self]=GOL_EMPTY_CHAR;
    if(n>6)(*in_u).space_next[self]=GOL_EMPTY_CHAR;
    }
  n=16-n;
  if((*in_u).space_next[self]==GOL_FILLED_CHAR){
    if(n==6)(*in_u).space_next[self]=GOL_EMPTY_CHAR;
    }else{
    if(n<3)(*in_u).space_next[self]=GOL_FILLED_CHAR;
    if(n>6&&n<8)(*in_u).space_next[self]=GOL_FILLED_CHAR;
    }
 // if(n_top>1&&n_bot>1&&!n_left&&!n_right)(*in_u).space_next[self]=GOL_FILLED_CHAR;
  //if(n_left>1&&n_right>1&&!n_top&&!n_bot)(*in_u).space_next[self]=GOL_FILLED_CHAR;
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
void game_of_life_rules2( struct toobit_space* in_u, unsigned int x, unsigned int y ){
  unsigned int offset=(TB_SPACE_SIZE_X*y)+x,yend=TB_SPACE_SIZE_Y-1,xend=TB_SPACE_SIZE_X-1;
  int n,n_top=0, n_bot=0, n_left=0, n_right=0;

  (*in_u).space_next[offset]=(*in_u).space[offset];
  if(x>0){
    if(y>0)if((*in_u).space[(offset-TB_SPACE_SIZE_X)-1]==GOL_FILLED_CHAR){n_top++;n_left++;} 	//top-left
    if((*in_u).space[offset-1]==GOL_FILLED_CHAR)n_left+=2;					//left
    if(y<yend)if((*in_u).space[offset+TB_SPACE_SIZE_X-1]==GOL_FILLED_CHAR){n_bot++;n_left++;}	//bot-left
    }
  if(y>0){
    if((*in_u).space[(offset-TB_SPACE_SIZE_X)]==GOL_FILLED_CHAR)n_top+=2;			//top
    if(x<xend)if((*in_u).space[(offset-TB_SPACE_SIZE_X)+1]==GOL_FILLED_CHAR){n_top++;n_right++;}//top-right
    }
  if(y<yend){
    if((*in_u).space[(offset+TB_SPACE_SIZE_X)]==GOL_FILLED_CHAR)n_bot+=2;			//bot
    if(x<xend)if((*in_u).space[(offset+TB_SPACE_SIZE_X)+1]==GOL_FILLED_CHAR){n_bot++;n_right++;}//bot right
    }
  if(x<xend){
    if((*in_u).space[offset+1]==GOL_FILLED_CHAR)n_right+=2;					//right
    }

  n=n_bot+n_top+n_left+n_right;
  if((*in_u).space[offset]==GOL_EMPTY_CHAR){
    if(n==6)(*in_u).space_next[offset]=GOL_FILLED_CHAR;
    }else{
    (*in_u).space_next[offset]=GOL_FILLED_CHAR;
    if(n<4)(*in_u).space_next[offset]=GOL_EMPTY_CHAR;
    if(n>6)(*in_u).space_next[offset]=GOL_EMPTY_CHAR;
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




  tb_init_space(&the_universe);			//initialize struct
  tb_heat_death(&the_universe,GOL_EMPTY_CHAR);	//flatten the universe to a signle value
  tb_reset_time(&the_universe);			//Reset time to 1

  tb_big_bang(&the_universe,25,GOL_FILLED_CHAR);	

  tb_speed_test_xy(0, &the_universe, 100, 100, &game_of_life_rules);
  tb_speed_test_3ptr(0, &the_universe, 100, 100, &game_of_life_rules_3row);

return;

int ix=100;
  while(1){				//----main loop
    r_val=random();			// prep a random number for general purpose

    tb_print_space_quarter_byte_match(&the_universe,GOL_FILLED_CHAR);	//print space to the screen 

    if(next_bang--<1&&ix){
      ix--;						//"big-bomber"
      next_bang=r_val&7;				//   repetitive big bangs
      tb_big_bang(&the_universe,(r_val&15)+5,GOL_FILLED_CHAR);
      }  

    //progress time (universe, # time ticks, pointer to physics function run at every point in space every tick)
    tb_time_ticker_3row( &the_universe, 1 , &game_of_life_rules_3row);
    usleep(60000);    
    }					//----end main loop

  return(0);
}

