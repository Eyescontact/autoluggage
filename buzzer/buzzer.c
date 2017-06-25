#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

#define PWM_IOCTL_SET_FREQ 1
#define PWM_IOCTL_STOP 0
#define ESC_KEY 0x1b

extern int blue_fd; 

static void getch(void)
{
  struct termios oldt,newt;
  //int ch;
  if (!isatty(STDIN_FILENO)) {
    fprintf(stderr, "this problem should be run at a terminal\n");
    exit(1);
  }
  // save terminal setting
  if(tcgetattr(STDIN_FILENO, &oldt) < 0) {
    perror("save the terminal setting");
    exit(1);
  }
  // set terminal as need
  newt = oldt;
  newt.c_lflag &= ~( ICANON | ECHO );
  if(tcsetattr(STDIN_FILENO,TCSANOW, &newt) < 0) {
    perror("set terminal");
    exit(1);
  }
  //ch = getchar();
  // restore termial setting
  if(tcsetattr(STDIN_FILENO,TCSANOW,&oldt) < 0) {
    perror("restore the termial setting");
    exit(1);
  }
  //return ch;
}

static int fd = -1;
static void close_buzzer(void);

static void open_buzzer(void)
{
  fd = open("/dev/pwm", 0);
  if (fd < 0)
  {
    perror("open pwm_buzzer device");
    exit(1);
  }
  // any function exit call will stop the buzzer
  atexit(close_buzzer);
}

static void close_buzzer(void)
{
  if (fd >= 0) 
  {
    ioctl(fd, PWM_IOCTL_STOP);
    close(fd);
    fd = -1;
  }
}
static void set_buzzer_freq(int freq)
{
  // this IOCTL command is the key to set frequency
  int ret = ioctl(fd, PWM_IOCTL_SET_FREQ, freq);
  if(ret < 0) {
    perror("set the frequency of the buzzer");
    exit(1);
  }
}
static void stop_buzzer(void)
{
  int ret = ioctl(fd, PWM_IOCTL_STOP);
  if(ret < 0) {
    perror("stop the buzzer");
    exit(1);
  }
}

int main(int argc, char **argv)
{
  int freq = 10 ;
  open_buzzer();
  printf( "\nBUZZER ( PWM Control )\n" );
  //printf( "Press +/- to increase/reduce the frequency of the BUZZER\n" ) ;
  //printf( "Press 'ESC' key to Exit this program\n\n" );
  while( 1 )
    {

		  //perror("read");
     		  set_buzzer_freq(freq);
		  // printf( "\tFreq = %d\n", freq );
		  // getch();
		  sleep(5);
		  stop_buzzer();
		  exit(1);

      
    }
}