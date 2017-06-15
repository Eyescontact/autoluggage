/*Blod  2017.6.13  serial for bluetooth */
#include  "get_location_msg.h"

struct  termios Opt;
//char  *send_buffer = "ATssssssss";
char  recv_buffer[512];
//int   sByte; 
int   Byte = 0;

int Serial_fd;


void  get_LocationMsg(void)
{
  int i,j=0;
  char fd2[1024];
  char a[1024];
  char* buf=a;
  float lat_v;
  float lon_v;
  float lat_v_flag=0;
  float lon_v_flag=0;
  char lat_value[10];
  char lon_value[10];

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
	      Byte = read(Serial_fd,recv_buffer,sizeof(recv_buffer));
	   
	      if(Byte < 0)
		{
		  perror("read");
		  exit(1);
		}
	      else if(Byte > 0)
		{
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
                                
		      if(lat_v!=lat_v_flag&&lon_v!=lon_v_flag)
			{
			  lat_v_flag=lat_v;
			  lon_v_flag=lon_v;
			  printf("E:%f\tN:%f\n",lat_v,lon_v);
			  break;
			  bzero(fd2,sizeof(fd2));
			  bzero(a,sizeof(a)); 
			}
		    }
			
		}  
	    }
	}  
    }
 
}

void serial_init(void)
{
  
  /*以读写方式打开串口*/
  //system("echo '1' | sudo chmod 777 /dev/ttyUSB0");
  system("chmod 777 /dev/ttySCA0");
  Serial_fd = open("/dev/ttySCA0", O_RDWR|O_NOCTTY|O_NDELAY);
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
