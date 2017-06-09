#!bin/bash
led_alloff()
{
i=0
while (($i<4))
do
   `led $i 0` #0 off 
   let i+=1   #i++
done
}

j=$1
led_mode()
{
#echo $j
while (($j<4))
do
   `led $j 0`
   usleep 300000
   `led $j 1`
   usleep 300000
#let i+=1
done
}

`killall led-player`
led_alloff
led_mode
