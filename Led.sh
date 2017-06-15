#!bin/bash
led_alloff()
{
i=0
while (($i<4))    #off ledall
do
   `led $i 0` #0 off 
   let i+=1   #i++
done
}

n=$1
m=$2
q=$3
p=$4

led_mode()
{
#echo $j
while ((1<4))
do
   `led 0 $n`
   `led 1 $m`
   `led 2 $q`
   `led 3 $p`
   usleep 300000
   `led 0 0`
   `led 1 0`
   `led 2 0`
   `led 3 0`
   usleep 300000
#let i+=1
done
}

`killall led-player`
led_alloff
led_mode
