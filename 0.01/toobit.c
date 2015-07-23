//-----------------------------
//	TOOBIT v0.1
//	2d bit space simulation system

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <toobit.h>

struct toobit_space the_universe;

int main() {
  unsigned int tc=0; 

  tb_heat_death(&the_universe,48);	//flatten the universe to a signle value
  tb_reset_time(&the_universe);		//Reset time to 1
  tb_big_bang(&the_universe,5,49);	//materialize energy(universe, radius, energy structure )

  while(1){				//----main loop
    system("clear");				//clear screen
    tb_printf_space_one_byte(&the_universe);	//print space to the screen    
    
    tc=0;
    while(tc++<TB_OBSERVATION_TIME_GAP){	//progress through 1 observation frame of time
      printf("(%i)\n",the_universe.time[0]++);  //show time fly
      }
    
    usleep(100000);    
    }					//----end main loop

  return(0);
}

