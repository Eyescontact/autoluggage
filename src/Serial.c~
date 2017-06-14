/*Blod  2017.6.13  serial for bluetooth */
#include  "Serial.h"

struct  termios Opt;
char  *send_buffer = "ATssssssss";
char  recv_buffer[15];
int   sByte; 
int   rByte = 0;

int Serial_fd;
void serial_setinit(void);

int main()
{
  struct timeval tv;
  fd_set rfds;
  //recv_buffer = (char *)malloc(sizeof(char));
  tv.tv_sec=30;
  tv.tv_usec=0;
  serial_setinit();

  printf("waiting...\n");
  while(1)
    {
     
      FD_ZERO(&rfds);
      FD_SET(Serial_fd, &rfds);
      //sleep(1);
#if send
      if(write(Serial_fd,send_buffer,strlen(send_buffer)) > 0)
      	{
      	  printf("write suc!\n");
	 
      	}
#endif
      //sleep(1);
      if (select(1+Serial_fd, &rfds, NULL, NULL, &tv)>0)
	{
	  if (FD_ISSET(Serial_fd, &rfds))
	    {
	      rByte = read(Serial_fd,recv_buffer,sizeof(recv_buffer));
	   
	      if(rByte <= 0)
		{
		  perror("read");
		  
		}
	      else if(rByte > 0)
		{
		  printf("LEN:%d\n",rByte);
		  recv_buffer[rByte] = '\0';
		  printf("buff:%s\n",recv_buffer);      	     
		}  
	    }
	}  
    }
  return 0;
}

void serial_setinit(void)
{
  
  /*以读写方式打开串口*/
  system("echo '258708' | sudo chmod 777 /dev/ttyUSB0");
  Serial_fd = open("/dev/ttyUSB0", O_RDWR|O_NOCTTY|O_NDELAY);
  if (Serial_fd < 0)
    {/* 不能打开串口一*/
      perror("Serial open");
      exit(1);
    }
   bzero(&Opt, sizeof(struct termios)); /* clear struct for new port settings */
   tcgetattr(Serial_fd, &Opt);
  Opt.c_cflag |= (CLOCAL | CREAD);
  Opt.c_cflag &= ~CSIZE;
  Opt.c_cflag &= ~CRTSCTS;
  Opt.c_cflag |= CS8;
  Opt.c_cflag &= ~CSTOPB; 
  Opt.c_iflag |= IGNPAR;
  Opt.c_iflag &= ~(BRKINT | INPCK | ISTRIP | ICRNL | IXON);		    

  Opt.c_cc[VMIN] = 8;        
  Opt.c_oflag = 0;
  Opt.c_lflag = 0;
  cfsetispeed(&Opt, 9600);
  cfsetospeed(&Opt, 9600);          
  tcsetattr(Serial_fd,TCSANOW,&Opt);

  printf("Serial open suc!\n");
}
