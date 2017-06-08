#!bin/bash
led_onoff()
{
i=0
while (($i<5))
do
   `led 1 0`
   sleep 1 
   `led 1 1`
   sleep 1 
done
}

`killall led-player`
led_onoff
