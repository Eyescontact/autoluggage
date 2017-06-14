/*
xzy  2017.6.9  code for autoluggage pratical trianing
*/
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include "led.h"
#include "get_location_msg.h"
#define open  1
#define state 0
#if open
volatile unsigned int  lug_location_msg;
volatile unsigned int  own_location_msg;
volatile unsigned char blue_command;

extern enum led_mode{zero_mode,one_mode,two_mode,three_mode} led_no;
pthread_t thread1,thread2,thread3;

unsigned int identity_ok = 0;
int blue_state = 0;
/*创建几个模块的线程*/
void thread_create(void);

void *pthread1()
{
  while(1)
    {
      printf("pthread1:%d\n",blue_state);
      sleep(1);
    }
}

void *pthread2()
{
  
}

void *pthread3()
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

#if state 
    blue_state += 1;
    sleep(1);
    if(blue_state == 1)   //change led mode,thread flags can change module mode 
      {
	switch()
	  {
	  case :
	    led_no
	  case :

	  case :

	  }
	
      }

    if(get_location == 1) //user ask for location msg
      {
	//gprs mode;  AT + phone number 
      }
    if(identity_ok == 1)
      {
	printf("verify suc!\n");
	// zhiwen msg
	// maybe push to user  AT phone
      }
#endif 
   // led_state();   
  }
return 0;
}

#if open
void thread_create(void)
{
  int res[2];
  memset(&thread1, 0, sizeof(thread1));
  memset(&thread2, 0, sizeof(thread2));
  res[1] = pthread_create(&thread1,NULL,(void *)get_LocationMsg,NULL);
  res[2] = pthread_create(&thread2,NULL,(void *)led_state,NULL);

  if(res[1] >= 0)
    {
      printf("create pthread1 suc!\n");
    }
  else
    {
      perror("create pthread failed!");
      exit(1);
    }
 
  if(res[2] >= 0)
    {
      printf("create pthread1 suc!\n");
    }
  else
    {
      perror("create pthread failed!");
      exit(1);
    }
}
#endif
