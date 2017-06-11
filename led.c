#include "led.h"

enum led_mode{zero_mode,one_mode,two_mode,three_mode} led_no=zero_mode; /*0 1 2 3*/
char dir[15]="bash ./Led.sh";
char dir_sh[16];

//change led state
void led_state()
{ 
  //led_no = two_mode;
  sprintf(dir_sh,"%s %d",dir,led_no);
  printf("%s",dir_sh); 
  system(dir_sh);
}
