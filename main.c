/*
xzy  2017.6.9  code for autoluggage pratical trianing
*/
#include <stdio.h>
#include <pthread.h>
#include "led.h"

#define open 0

#if open
volatile unsigned int  lug_location_msg;
volatile unsigned int  own_location_msg;
volatile unsigned char blue_command;

/*创建几个模块的线程*/
void thread_create(void)
{
  int res[2];
  memset(&thread1, 0, sizeof(thread));
  memset(&thread2, 0, sizeof(thread));
  res[1] = pthread_create(&thread1,NULL,pthread1,NULL);
  res[2] = pthread_create(&thread2,NULL,pthread2,NULL);

  if(res[1] >= 0)
    {
      printf("create pthread suc!");
    }
  else
    {
      perror("create pthread failed!");
      exit(1);
    }
 
  if(res[2] >= 0)
    {
      printf("create pthread suc!");
    }
  else
    {
      perror("create pthread failed!");
      exit(1);
    }
}

void *pthread1()
{
  while(1)
    {
      
    }
}

void *pthread2()
{
  
}
#endif


int main ()
{
  /*
    create module pthread. example:
    get_location();
    
   */
  thread_create();
  
  while(1)
  {
   // led_state();   
  }
return 0;
}
