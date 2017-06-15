#include "led.h"

extern unsigned short int     identity_state        ;    
extern unsigned short int     blue_state            ;
extern unsigned short int     get_location_state    ;
extern unsigned short int     get_weight_state      ;

enum led_mode{zero_mode,one_mode,two_mode,three_mode} led_no=zero_mode; /*0 1 2 3 */
char dir[15]="bash ./Led.sh";
char dir_sh[24];

//change led state
void led_state()
{ 
  //led_no = two_mode;
  while(1)
    {
      sprintf(dir_sh,"%s %d %d %d %d",dir,blue_state,identity_state,get_weight_state,get_location_state);
      printf("%s",dir_sh);
      // printf("led:%d",blue_state);
      // sleep(1);
      system(dir_sh);
    }
}
