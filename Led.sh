#!bin/bash
led_onoff()
{
i=0
while (($i<4))
do
   `led $i 0`
   usleep 300000
#   `led $i 1`
 #  usleep 300000 
   
let i+=1

done
}

`killall led-player`
led_onoff
