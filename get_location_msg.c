#include "get_location_msg.h"

int fd;

int uart_device_open()
{
	struct termios options;
	
	system("echo '258708' | sudo chmod 777 /dev/ttyUSB0");
	if((fd=open("/dev/ttyUSB0",O_RDWR|O_NOCTTY|O_NDELAY))<0)
	{
		perror("open failed");
		return -1;
	}
	tcgetattr(fd, &options);
	options.c_cflag |= (CLOCAL | CREAD);
	options.c_cflag &= ~CSIZE;
	options.c_cflag &= ~CRTSCTS;
	options.c_cflag |= CS8;
	options.c_cflag &= ~CSTOPB; 
	options.c_iflag |= IGNPAR;
	options.c_iflag &= ~(BRKINT | INPCK | ISTRIP | ICRNL | IXON);		    

	options.c_cc[VMIN] = 8;        
	options.c_oflag = 0;
	options.c_lflag = 0;
	cfsetispeed(&options, 9600);
	cfsetospeed(&options, 9600);          
	tcsetattr(fd,TCSANOW,&options);
	
    printf("Open Success!\n");
	return 0;
}



int main(int argc, const char *argv[])
{
	long i;
	int j;
	char fd1[128];
	char fd2[1024];
	char a[1024];
	char* buf=a;
	float lat_v;
	float lon_v;
	int flag;
	char lat_value[10];
    char lon_value[10];


	uart_device_open();

	while(1)
	{   
		sleep(1);
		while((flag=read(fd,fd1,sizeof(fd1)-1))<=0)
		{ 
			perror("read");
			exit(1);
		} 
        strcat(fd2,fd1);
    	bzero(fd1,sizeof(fd1));
        while((buf=strstr(fd2,"$GPRMC"))!=NULL&&strstr(buf,"\n")!=NULL)
		{

//			printf("fd2:%s\n",fd2);
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
			lat_v=atof(lat_value) / 100;
			lon_v=atof(lon_value) / 100;
			if(lat_v!=0&&lon_v!=0)
    			printf("E:%f\tN:%f\n",lat_v,lon_v);
		}	
	}		
	close(fd);
	return 0; 
}

