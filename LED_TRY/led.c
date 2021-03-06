#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv)
{
  //system(". ~/github/EasyGitPush.sh");
  int on;
  int led_no;   //1~6
  int fd;

  /* 检查 led 控制的两个参数，如果没有参数输入则退出。 */
  if (argc != 3 || sscanf(argv[1], "%d", &led_no) != 1 || sscanf(argv[2],"%d", &on) != 1 ||
on < 0 || on > 1 || led_no < 0 || led_no > 6) 
  {
  fprintf(stderr, "Usage: leds led_no 0|1\n");
  exit(1);
  }
  
  fd = open("/dev/leds",0);
  if(fd < 0)
  {
    perror("open device leds");
    exit(1);
  }
  
  ioctl(fd,on,led_no);
  close(fd);
  return 0;
}
