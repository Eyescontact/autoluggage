#include     <stdio.h>      /*标准输入输出定义*/
#include     <stdlib.h>     /*标准函数库定义*/
#include     <unistd.h>     /*Unix 标准函数定义*/
#include     <sys/types.h>  /*数据类型，比如一些XXX_t的那种的结构，没看明白*/
#include     <sys/stat.h>   /*定义了一些返回值*/
#include     <fcntl.h>      /*文件控制定义*/
#include     <termios.h>    /*PPSIX 终端控制定义*/
#include     <errno.h>      /*错误号定义*/
#include     <string.h>

#define  send  0

#define PWM_IOCTL_SET_FREQ 1   //buzzer
#define PWM_IOCTL_STOP 0
#define ESC_KEY 0x1b

#define  command_ahead        "01"
#define  command_back         "02"
#define  command_left         "03"
#define  command_right        "04"
#define  command_stop         "00"
#define  command_location     "05"
#define  command_exit         "ff"

void serial_buzzer_init(void);
void blue_serial(void);

static void close_buzzer(void);
static void open_buzzer(void);
static void set_buzzer_freq(int freq);
static void stop_buzzer(void);

