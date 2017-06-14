#include "led.h"

extern int blue_state;

enum led_mode{zero_mode,one_mode,two_mode,three_mode} led_no=zero_mode; /*0 1 2 3*/
char dir[15]="bash ./Led.sh";
char dir_sh[16];

//change led state
void led_state()
{ 
  //led_no = two_mode;
  while(1)
    {
      sprintf(dir_sh,"%s %d",dir,led_no);
      printf("%s",dir_sh);
      // printf("led:%d",blue_state);
      // sleep(1);
      system(dir_sh);
    }
}
