﻿#include  "nice.h"

struct  termios Opt;

char  *send_buffer = "ATssssssss";

char  recv_buffer[2];

int   sByte; 

int   rByte = 0;

  struct timeval tv;

  fd_set rfds;

int select_fd;
int Serial_fd;

void serial_setinit(void);
void Send_Pack_Head(void);
void Get_Image(void);
void Img_To_Buffer1(void);
void Img_To_Buffer2(void);
void Reg_Model(void);
void Delete_All_Model(void);
void Get_Templete_Num(void);
void Search_Finger(void);
void Search_Finger_Admin(void);
void Receive_Data(void);

int i;
unsigned char buffer[12];

unsigned char FPMXX_Pack_Head[6] = {0xEF,0x01,0xFF,0xFF,0xFF,0xFF};  //协议包头  

volatile unsigned char FPMXX_RECEICE_BUFFER[24];//FINGERPRINT通信协议定义

unsigned char FPMXX_Get_Img[6] =  {0x01,0x00,0x03,0x01,0x0,0x05};   //获得指纹图像

unsigned char FPMXX_Get_Templete_Count[6]={0x01,0x00,0x03,0x1D,0x00,0x21 }; //获得模版总数

unsigned char FP_Search[11]={0x01,0x0,0x08,0x04,0x01,0x0,0x0,0x03,0xA1,0x0,0xB2}; //搜索指纹搜索范围0 - 929

unsigned char FP_Search_0_9[11]={0x01,0x0,0x08,0x04,0x01,0x0,0x0,0x0,0x13,0x0,0x21}; //搜索0-9号指纹

unsigned char FP_Img_To_Buffer1[7]={0x01,0x0,0x04,0x02,0x01,0x0,0x08};//将图像放入到BUFFER1

unsigned char FP_Img_To_Buffer2[7]={0x01,0x0,0x04,0x02,0x02,0x0,0x09}; //将图像放入到BUFFER2

unsigned char FP_Reg_Model[6]={0x01,0x0,0x03,0x05,0x0,0x09};

unsigned char FP_Delet_All_Model[6]={0x01,0x0,0x03,0x0d,0x00,0x11};//删除指纹模块里所有的模版

//volatile unsigned char  FP_Save_Finger[9]={0x01,0x00,0x06,0x06,0x01,0x00,0x0B,0x00,0x19};//将BUFFER1中的特征码存放到指定的位置

//volatile unsigned char FP_Delete_Model[10]={0x01,0x00,0x07,0x0C,0x0,0x0,0x0,0x1,0x0,0x0}; //删除指定的模版

int main()

{

  //recv_buffer = (char *)malloc(sizeof(char));

  tv.tv_sec=30;

  tv.tv_usec=0;

  serial_setinit();

  printf("waiting...\n");

  while(1)

    {
      FD_ZERO(&rfds);
      FD_SET(Serial_fd, &rfds);
      Get_Image();
      Receive_Data();
    }

  return 0;

}



void serial_setinit(void)

{  

  /*以读写方式打开串口*/

  system("echo '666666' | sudo chmod 777 /dev/ttyUSB0");

  Serial_fd = open("/dev/ttyUSB0", O_RDWR|O_NOCTTY); //|O_NDELAY

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



  Opt.c_cc[VMIN] = 1;        
  Opt.c_cc[VTIME] = 0;
  Opt.c_oflag = 0;

  Opt.c_lflag = 0;

  cfsetispeed(&Opt, 38400);

  cfsetospeed(&Opt, 38400);          

  tcsetattr(Serial_fd,TCSANOW,&Opt);



  printf("zhiwen open suc!\n");

}


void Send_Pack_Head(void)
{
		int i;
	
		for(i=0;i<6;i++)
    {
    rByte = write(Serial_fd,&FPMXX_Pack_Head[i],sizeof(FPMXX_Pack_Head[i])); 
    }
}


    void Get_Image(void)
    {
        int i;
    for(i=0;i<6;i++)
        rByte = write(Serial_fd,&FPMXX_Pack_Head[i],sizeof(FPMXX_Pack_Head[i]));
    if(rByte <= 0)
    {
        perror("write");  
    }
    else if(rByte > 0)
        {	 
        for(i=0;i<6;i++)
            rByte = write(Serial_fd,&FPMXX_Get_Img[i],sizeof(FPMXX_Get_Img[i]));
        //printf("fir suc!\n");
        if(rByte <=0)
            {
            perror("second write");  
            }
        else if(rByte > 0)
            {
            //printf("suc!\n");			 		
            }
        }  
    }

    void Img_To_Buffer1(void)
    {
        unsigned char i;
    for(i=0;i<6;i++)
        rByte = write(Serial_fd,&FPMXX_Pack_Head[i],sizeof(FPMXX_Pack_Head[i]));
    if(rByte <=0)
    {
        perror("write");   
    }
    else if(rByte>0)
    {
        for(i=0;i<7;i++)
            rByte = write(Serial_fd,&FP_Img_To_Buffer1[i],sizeof(FP_Img_To_Buffer1[i]));
        //printf("fir suc!\n");
        if(rByte <=0)
            {
            perror("second write");  
            }
        else if(rByte > 0)
            {
            //printf("suc!\n");			 		
            }
    }
    }
    
    
    void Img_To_Buffer2(void)
    {
        unsigned char i;
    for(i=0;i<6;i++)
    {
        rByte = write(Serial_fd,&FPMXX_Pack_Head[i],sizeof(FPMXX_Pack_Head[i]));
    }
    if(rByte <=0)
    {
        perror("write");   
    }
    else if(rByte>0)
    {
        for(i=0;i<7;i++)
        {
            rByte = write(Serial_fd,&FP_Img_To_Buffer1[i],sizeof(FP_Img_To_Buffer2[i]));
        }
        //printf("fir suc!\n");
        if(rByte <=0)
            {
            perror("second write");  
            }
        else if(rByte > 0)
            {
            //printf("suc!\n");			 		
            }
    }
    }
    
  
void Reg_Model(void)
{
    unsigned char i;    
    for(i=0;i<6;i++) 
    {
      rByte = write(Serial_fd,&FPMXX_Pack_Head[i],sizeof(FPMXX_Pack_Head[i]));
    }
    if(rByte <=0)
    {
        perror("write");   
    }
   else if(rByte > 0)
        {	 
        for(i=0;i<6;i++)
            rByte = write(Serial_fd,&FP_Reg_Model[i],sizeof(FP_Reg_Model[i]));
        //printf("fir suc!\n");
        if(rByte <=0)
            {
            perror("second write");  
            }
        else if(rByte > 0)
            {
            //printf("suc!\n");			 		
            }
        }  
}

void Delete_All_Model(void)
{
     unsigned char i;    
for(i=0;i<6;i++) 
    {
      rByte = write(Serial_fd,&FPMXX_Pack_Head[i],sizeof(FPMXX_Pack_Head[i]));
    }
    if(rByte <=0)
    {
        perror("write");   
    }
   else if(rByte > 0)
        {	 
        for(i=0;i<6;i++)
            rByte = write(Serial_fd,&FP_Delet_All_Model[i],sizeof(FP_Delet_All_Model[i]));
        //printf("fir suc!\n");
        if(rByte <=0)
            {
            perror("second write");  
            }
        else if(rByte > 0)
            {
            //printf("suc!\n");			 		
            }
        }    
}

void Get_Templete_Num(void)
{  unsigned int i;
   unsigned char temp[14];

      rByte = write(Serial_fd,&FPMXX_Pack_Head[i],sizeof(FPMXX_Pack_Head[i]));
    
    if(rByte <=0)
    {
        perror("write");   
    }
 else if(rByte > 0)
        {	 
        for(i=0;i<6;i++)
            rByte = write(Serial_fd,&FPMXX_Get_Templete_Count[i],sizeof(FPMXX_Get_Templete_Count[i]));
        //printf("fir suc!\n");
        if(rByte <=0)
            {
            perror("second write");  
            }
        else if(rByte > 0)
            {
            //printf("suc!\n");			 		
            }
        }    
}

void Search_Finger(void)
{
     unsigned char i;    
for(i=0;i<6;i++) 
    {
      rByte = write(Serial_fd,&FPMXX_Pack_Head[i],sizeof(FPMXX_Pack_Head[i]));
    }
    if(rByte <=0)
    {
        perror("write");   
    }
   else if(rByte > 0)
        {	 
        for(i=0;i<11;i++)
            rByte = write(Serial_fd,&FP_Search[i],sizeof(FP_Search[i]));
        //printf("fir suc!\n");
        if(rByte <=0)
            {
            perror("second write");  
            }
        else if(rByte > 0)
            {
            //printf("suc!\n");			 		
            }
        }    
}

void Search_Finger_Admin(void)
{
     unsigned char i;    
for(i=0;i<6;i++) 
    {
      rByte = write(Serial_fd,&FPMXX_Pack_Head[i],sizeof(FPMXX_Pack_Head[i]));
    }
    if(rByte <=0)
    {
        perror("write");   
    }
   else if(rByte > 0)
        {	 
        for(i=0;i<11;i++)
            rByte = write(Serial_fd,&FP_Search_0_9[i],sizeof(FP_Search_0_9[i]));
        //printf("fir suc!\n");
        if(rByte <=0)
            {
            perror("second write");  
            }
        else if(rByte > 0)
            {
            //printf("suc!\n");			 		
            }
        }    
}


void Receive_Data(void)
{
  unsigned char i;

  for(i=0;i<12;i++)
  {
  FPMXX_RECEICE_BUFFER[i] = read(Serial_fd,&buffer[i],sizeof(buffer[i]));
	//printf("buf12:%s\n",buffer);
}	
}




void Send_Serial(void)
{
#if send

  if (select(1+Serial_fd, &rfds, NULL, NULL, &tv)>0)
    {
      if (FD_ISSET(Serial_fd, &rfds))
	{
	  rByte = read(Serial_fd,recv_buffer,sizeof(recv_buffer));
	   
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

	    }  
	}
    } 
#endif
}
