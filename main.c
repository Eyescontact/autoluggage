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
#include "autoFollow.h"
#define open  1
#define state 0
#if open
volatile  double  lug_location_msg_lon = 0;
volatile  double  lug_location_msg_lat = 0;
volatile  double  own_location_msg_lon = 0;
volatile  double  own_location_msg_lat = 0;

extern volatile unsigned int blue_command;

extern enum led_mode{zero_mode,one_mode,two_mode,three_mode} led_no;

pthread_t led_thread,bluethoot_thread,location_thread,weigh_thread,follow_thread;
//状态 也为控制灯的状态
unsigned short int     identity_state        = 0;    
unsigned short int     blue_state            = 0;
unsigned short int     get_location_state    = 0;
unsigned short int     get_weight_state      = 0;

unsigned short int     Last_identity_state        = 0;    
unsigned short int     Last_blue_state            = 0;
unsigned short int     Last_get_location_state    = 0;
unsigned short int     Last_get_weight_state      = 0;

unsigned short int     id_yes = 1;
unsigned short int     motor_on = 1;

/*创建几个模块的线程*/
void thread_create(void);
void check_StateChange(void);
void id_identity(void);
/* thread try 
void *pthread1()
{
  while(1)
    {
      printf("pthread1:%d\n",blue_state);
      sleep(1);
    }
}
*/
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
    
    check_StateChange();
#if state 
    //blue_state += 1;
    //sleep(1);
    if(blue_state == 1)   //change led mode,thread flags can change module mode 
      {
	switch()
	  {
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
  int res[5];
  memset(&location_thread  , 0, sizeof(location_thread));
  memset(&led_thread       , 0, sizeof(led_thread));
  memset(&bluethoot_thread , 0, sizeof(bluethoot_thread));
  memset(&weigh_thread     , 0, sizeof(weigh_thread));
  memset(&follow_thread    , 0, sizeof(follow_thread));
  
  res[1] = pthread_create(&location_thread  ,NULL,(void *)get_LocationMsg,NULL);
  res[2] = pthread_create(&led_thread       ,NULL,(void *)led_state,NULL);
  res[3] = pthread_create(&bluethoot_thread ,NULL,(void *)blue_serial,NULL);
  res[4] = pthread_create(&weigh_thread     ,NULL,(void *)get_weight,NULL);  
  res[5] = pthread_create(&follow_thread    ,NULL,(void *)autoFollow,NULL); 

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

   if(res[5] >= 0)
    {
      printf("create follow_thread suc!\n");
    }
  else
    {
      perror("create follow_thread failed!");
      exit(1);
      }  
}

void id_identity(void)
{
  if(id_yes == 0)
    motor_on == 0;
  else
    motor_on == 1;
}

void check_StateChange(void)
{
  // printf("%d %d %d %d\n",get_weight_state,get_location_state,identity_state, blue_state);
  if(Last_get_weight_state != get_weight_state || Last_get_location_state != get_location_state || Last_identity_state != identity_state || Last_blue_state != blue_state)
    { 
      int res_ok,res_join,res_led;
      void *thread_res;
     
      printf("led change!\n");
      Last_get_weight_state = get_weight_state;
      Last_get_location_state = get_location_state; 
      Last_identity_state = identity_state;
      Last_blue_state = blue_state;

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
