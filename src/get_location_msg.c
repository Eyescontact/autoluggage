/*Blod  2017.6.13  serial for bluetooth */
#include  "get_location_msg.h"

struct  termios Opt;
//char  *send_buffer = "ATssssssss";
char  recv_buffer[512];
//int   sByte; 
int   Byte = 0;

int Serial_fd;

extern volatile  double  lug_location_msg_lon ;
extern volatile  double  lug_location_msg_lat ;
extern volatile  double  own_location_msg_lon ;
extern volatile  double  own_location_msg_lat ;

extern unsigned short int     get_location_state;

void  get_LocationMsg(void)
{
  int i,j=0;
  char fd2[1024];
  char a[1024];
  char* buf=a;
  
  double lat_v;
  double lon_v;
  double lat_v_flag=0;
  double lon_v_flag=0;
  
  char lat_value[10];
  char lon_value[10];

  struct timeval tv;
  fd_set rfds;
  //recv_buffer = (char *)malloc(sizeof(char));
  tv.tv_sec=30;
  tv.tv_usec=0;

  serial_init();

  printf("location waiting...\n");
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
	      Byte = read(Serial_fd,recv_buffer,sizeof(recv_buffer));
	   
	      if(Byte < 0)
		{
		  perror("read");
		  get_location_state = 0;
		  exit(1);
		}
	      else if(Byte > 0)
		{
		  get_location_state = 1;
		  strcat(fd2,recv_buffer);
		  //printf("fd2:%s\n",fd2);
		  while((buf=strstr(fd2,"$GPRMC"))!=NULL&&strstr(buf,"\n")!=NULL)
		    {

		      for(i=0;;i++)
			{
			  if(buf[i]=='A')
			    {
			      i+=2;
			      j=0;
			      while(buf[i]!=',')
				{
				  lat_value[j]=buf[i];
				  j++;
				  i++;
				}
			      i+=3;
			      j=0;
			      while(buf[i]!=',')
				{
				  lon_value[j]=buf[i];
				  j++;
				  i++;
				}
			      break;
			    }
			}	
		      lat_v=atof(lat_value);
		      lon_v=atof(lon_value);
                                
		      //if(lat_v!=lat_v_flag&&lon_v!=lon_v_flag)
			
			  sleep(1);
			  lat_v_flag=lat_v;  //纬
			  lon_v_flag=lon_v;  //经
			  printf("E:%lf\tN:%lf\n",lat_v,lon_v);
			  lug_location_msg_lon = (double)lon_v;
			  lug_location_msg_lat = (double)lat_v;
			  bzero(fd2,sizeof(fd2));
			  bzero(a,sizeof(a)); 
			  break;
		    }
			
		}  
	    }
	}  
      if(sizeof(fd2) > 1000)
     	{
	  bzero(fd2,sizeof(fd2));
      	}
    }//while 
  get_location_state = 0;
}

void serial_init(void)
{
  
  /*以读写方式打开串口*/
  //system("echo '1' | sudo chmod 777 /dev/ttyUSB0");
  system("chmod 777 /dev/ttyUSB1");
  Serial_fd = open("/dev/ttyUSB1", O_RDWR|O_NOCTTY); //|O_NDELAY
  if (Serial_fd < 0)
    {/* 不能打开串口一*/ 
      perror("SCA Serial open");
      // exit(1);
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
  Opt.c_cc[VTIME] = 0; 

  Opt.c_oflag = 0;
  Opt.c_lflag = 0;
  cfsetispeed(&Opt, 9600);
  cfsetospeed(&Opt, 9600);          
  tcsetattr(Serial_fd,TCSANOW,&Opt);

  printf("location Serial open suc!\n");
}
