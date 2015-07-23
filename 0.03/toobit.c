//-----------------------------
//	TOOBIT v0.2
//	2d bit space simulation system

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <toobit.h>

struct toobit_space the_universe;


//--------------------------------------
//		game_of_life_rules ()
//	x/y = x,y cords
//	t = output target pointer
//	n = # of neighbours
//--------------------------------------
void game_of_life_rules(unsigned int x, unsigned int y, struct toobit_space* in_u ){
  unsigned int offset=(TB_SPACE_SIZE_X*y)+x,yend=TB_SPACE_SIZE_Y-1,xend=TB_SPACE_SIZE_X-1;
  char n=0;
  (*in_u).space_next[offset]=(*in_u).space[offset];

  if(x>0){
    if(y>0)if((*in_u).space[(offset-TB_SPACE_SIZE_X)-1]==42)n++;  	//top-left
    if((*in_u).space[offset-1]==42)n++;					//left
    if(y<yend)if((*in_u).space[offset+TB_SPACE_SIZE_X-1]==42)n++;	//bot-left
    }
  if(y>0){
    if((*in_u).space[(offset-TB_SPACE_SIZE_X)]==42)n++;			//top
    if(x<xend)if((*in_u).space[(offset-TB_SPACE_SIZE_X)+1]==42)n++;	//top-right
    }
  if(y<yend){
    if((*in_u).space[(offset+TB_SPACE_SIZE_X)]==42)n++;			//bot
    if(x<xend)if((*in_u).space[(offset+TB_SPACE_SIZE_X)+1]==42)n++;	//bot right
    }
  if(x<xend){
    if((*in_u).space[offset+1]==42)n++;					//right
    }

  if((*in_u).space[offset]==32){
    if(n==3)(*in_u).space_next[offset]=42;
    }else{
    if(n<2)(*in_u).space_next[offset]=32;
    if(n>3)(*in_u).space_next[offset]=32;
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
  tb_heat_death(&the_universe,32);	//flatten the universe to a signle value
  tb_reset_time(&the_universe);		//Reset time to 1
  tb_big_bang(&the_universe,8,42);	//materialize energy(universe, radius, energy structure )
  

  while(1){				//----main loop
    r_val=random();
    noise_level=(r_val>>2)&7;
    while(noise_level--)the_universe.space[random()%TB_SPACE_DATA_SIZE_BYTES]=42;


    system("clear");				//clear screen

    tb_printf_space_quarter_byte(&the_universe);	//print space to the screen 

    if(next_bang--<1){
      next_bang=r_val&3;
      tb_big_bang(&the_universe,next_bang<<2,42);
      }  
    
    tc=TB_OBSERVATION_TIME_GAP;
    while(tc--){				//progress through 1 observation frame of time ticks
      int x,y=TB_SPACE_SIZE_Y;
      while(y--){
	x=TB_SPACE_SIZE_X;
	while(x--){
	  game_of_life_rules(x,y,&the_universe);
	  }
	}
      //printf("(%i)\n",the_universe.time[0]++);  //show time fly
      memcpy(the_universe.space,the_universe.space_next,TB_SPACE_DATA_SIZE_BYTES);
      }
    
    usleep(60000);    
    }					//----end main loop

  return(0);
}

