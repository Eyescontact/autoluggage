/*Blod  2017.6.13  serial for bluetooth */
#include  "blue_serial.h"

struct  termios Opt;
char  *send_buffer = "ATssssssss";
char  recv_buffer[3];
int   sByte; 
int   rByte = 0;

volatile int  blue_command = 0;

extern volatile  double  lug_location_msg_lon ;
extern volatile  double  lug_location_msg_lat ;

int blue_fd;

void blue_serial(void)
{
  struct timeval tv;
  fd_set rfds;
  //recv_buffer = (char *)malloc(sizeof(char));
  tv.tv_sec=30;
  tv.tv_usec=0;
  serial_blueinit();

  printf("blue waiting...\n");
  while(1)
    {
     
      FD_ZERO(&rfds);
      FD_SET(blue_fd, &rfds);
      //sleep(1);
#if send
      //bzero(recv_buffer,0);
      if(write(Serial_fd,send_buffer,strlen(send_buffer)) > 0)
      	{
      	  printf("write suc!\n");
	 
      	}
#endif
      //sleep(1);
      if (select(1+blue_fd, &rfds, NULL, NULL, &tv)>0)
	{
	  if (FD_ISSET(blue_fd, &rfds))
	    {
	      rByte = read(blue_fd,recv_buffer,sizeof(recv_buffer));
	   
	      if(rByte < 0)
		{
		  perror("read");
		  exit(1);
		}
	      else if(rByte > 0)
		{ 
    	          printf("LEN:%d\n",rByte);
		  recv_buffer[rByte] = '\0';
		  printf("buff:%s\n",recv_buffer); 
		  if(strcmp(recv_buffer,command_ahead) == 0)
	     	  {
			blue_command = 1;
			printf("ahead !\n");
		  }
		  if(strcmp(recv_buffer,command_back) == 0)
                  {  	
			blue_command = 2;
		        printf("back !\n");
		  }
		  if(strcmp(recv_buffer,command_left) == 0)
                  { 
			blue_command = 3;
		        printf("left !\n");
		  }
		  if(strcmp(recv_buffer,command_right) == 0)
                  {
			blue_command = 4;
		        printf("right !\n");
		  } 
		  if(strcmp(recv_buffer,command_stop) == 0)
                  {  
			blue_command = 0;
		        printf("stop !\n");
		  }
		  if(strcmp(recv_buffer,command_location) == 0)
		  {  
			blue_command = 5;
		        printf("get location !\n");
			printf("luglocation:%lf,%lf",lug_location_msg_lat,lug_location_msg_lon);
		  }
#if switch
		switch(blue_command)
		{
		  case  1:
			printf("go ahead!\n");
			break;
		}     	     
#endif
		}  
	    }
	}  
    }
  
}

void serial_blueinit(void)
{
  
  /*以读写方式打开串口*/
  //system("echo '258708' | sudo chmod 777 /dev/ttyUSB0");
   system("chmod 777 /dev/ttyUSB0");
   blue_fd = open("/dev/ttyUSB0", O_RDWR|O_NOCTTY); //|O_NDELAY
  if (blue_fd < 0)
    {/* 不能打开串口一*/
      perror("blue Serial open");
      exit(1);
    }
   bzero(&Opt, sizeof(struct termios)); /* clear struct for new port settings */
   tcgetattr(blue_fd, &Opt);
  Opt.c_cflag |= (CLOCAL | CREAD);
  Opt.c_cflag &= ~CSIZE;
  Opt.c_cflag &= ~CRTSCTS;
  Opt.c_cflag |= CS8;
  Opt.c_cflag &= ~CSTOPB; 
  Opt.c_iflag |= IGNPAR;
  Opt.c_iflag &= ~(BRKINT | INPCK | ISTRIP | ICRNL | IXON);		    

  Opt.c_cc[VMIN]  = 2;       //每次接受最小位数 
  Opt.c_cc[VTIME] = 0;
  Opt.c_oflag = 0;
  Opt.c_lflag = 0;
  cfsetispeed(&Opt, 9600);
  cfsetospeed(&Opt, 9600);          
  tcsetattr(blue_fd,TCSANOW,&Opt);

  printf("blue Serial open suc!\n");
}
