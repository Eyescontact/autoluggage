#include <stdio.h>
#include <sys/time.h>

void main()

{
  int i = 0;
  struct timeval tpstart,tpend;
  float timeuse;
 
  while(1)
    { gettimeofday(&tpstart,NULL);
      //   i = i + 1;
      //    if(i == 500000000)
      //     {
      //	 printf("hello\n");
      sleep(2);
	 gettimeofday(&tpend,NULL);
	 timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;      
	 timeuse/=1000000;      
	 printf("used time:%f sec\n",timeuse);
	 //	 i = 0;
	 // }
      
    }

}
