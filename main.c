/*
xzy  2017.6.9  code for autoluggage pratical trianing
*/
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include "led.h"
#include "get_location_msg.h"
#include "blue_serial.h"
#include "get_weight.h"

#define open  1
#define state 0
#if open
volatile unsigned int  lug_location_msg;
volatile unsigned int  own_location_msg;

extern volatile unsigned int blue_command;

extern enum led_mode{zero_mode,one_mode,two_mode,three_mode} led_no;
pthread_t led_thread,bluethoot_thread,location_thread,weigh_thread;
//状态 也为控制灯的状态
unsigned short int     identity_state        = 0;    
unsigned short int     blue_state            = 0;
unsigned short int     get_location_state    = 0;
unsigned short int     get_weight_state      = 0;

unsigned short int     Last_identity_state        = 0;    
unsigned short int     Last_blue_state            = 0;
unsigned short int     Last_get_location_state    = 0;
unsigned short int     Last_get_weight_state      = 0;

/*创建几个模块的线程*/
void thread_create(void);
void check_StateChange(void);

/* thread try 
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
  
}*/
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
    
    //check_StateChange();
#if state 
    //blue_state += 1;
    //sleep(1);
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

    if(get_location_state == 1) //user ask for location msg
      {
	//gprs mode;  AT + phone number 
      }
    if(identity_state == 1)
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
  int res[4];
  memset(&location_thread  , 0, sizeof(location_thread));
  memset(&led_thread       , 0, sizeof(led_thread));
  memset(&bluethoot_thread , 0, sizeof(bluethoot_thread));
  memset(&weigh_thread     , 0, sizeof(weigh_thread));
  
  res[1] = pthread_create(&location_thread  ,NULL,(void *)get_LocationMsg,NULL);
  res[2] = pthread_create(&led_thread       ,NULL,(void *)led_state,NULL);
  res[3] = pthread_create(&bluethoot_thread ,NULL,(void *)blue_serial,NULL);
  res[4] = pthread_create(&weigh_thread     ,NULL,(void *)get_weight,NULL);  

  if(res[1] >= 0)
    {
      printf("create location_thread suc!\n");
    }
  else
    {
      perror("create location_thread failed!");
      exit(1);
    }
 
  if(res[2] >= 0)
    {
      printf("create led_thread suc!\n");
    }
  else
    {
      perror("create led_thread failed!");
      exit(1);
    }

  if(res[3] >= 0)
    {
      printf("create bluethoot_thread suc!\n");
    }
  else
    {
      perror("create bluethoot_thread failed!");
      exit(1);
    }

  if(res[4] >= 0)
    {
      printf("create weigh_thread suc!\n");
    }
  else
    {
      perror("create weigh_thread failed!");
      exit(1);
    }  
}

void check_StateChange(void)
{
  if(Last_get_weight_state != get_weight_state || Last_get_location_state != get_location_state || Last_identity_state != identity_state || Last_blue_state != blue_state)
    { 
      int res_ok,res_join,res_led;
      void *thread_res;
      res_ok = pthread_cancel(led_thread);
      if(res_ok != 0)
	{
	  perror("cancel led_thread");
	  exit(1);
	}
      printf("Waiting for thread to finish...\n"); 
      
      res_join = pthread_join(led_thread,&thread_res);
      if(0 != res_join){  
        perror("thread join failed!");  
        exit(EXIT_FAILURE);  
      }  
      memset(&led_thread       , 0, sizeof(led_thread));
      
      res_led = pthread_create(&led_thread       ,NULL,(void *)led_state,NULL);
      if(res_led >= 0)
	{
	  printf("create led_thread suc!\n");
	}
      else
	{
	  perror("create led_thread failed!");
	  exit(1);
	}
    }
}
#endif
