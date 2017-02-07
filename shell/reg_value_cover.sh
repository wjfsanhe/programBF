#!/bin/sh

echo "=>reg value test ....... "
i=0
j=0
skew_limit=$((1<<1))
delay_limit=$((1<<1))
base=0x1621
target_ip=$1

if ( ""$target_ip"xy" = "xy" );
then
target_ip="192.168.1.1"
fi


network_reset(){
echo "reset network"
netcfg eth0 down
netcfg eth0 up
ip_null="0.0.0.0"
ip=$ip_null
while [ "$ip" = "$ip_null"]
do
ip=$(netcfg | grep eth0 | awk '{print $3}' | awk -F "/" '{print $1}')
done
echo  "reset network ok"


}

for k in `seq 4` ;do
adj_enable=0
adj_setup=0
if [ $k = 4 ];then continue;fi
if [ $k = 1 ];then adj_enable=1;fi
if [ $k = 2 ];then adj_setup=1;fi
if [ $k = 3 ];then adj_enable=1; adj_setup=1 ;fi


echo `printf "[%d]-[%d]" $adj_enable $adj_setup`
continue;
while [ $i -lt $skew_limit ] ;do 
round_1_val=$((base | i << 20 ))
j=0
while [ $j -lt $delay_limit ] ;do 
round_2_val=$((round_1_val | j << 15))
index=$((i*skew_limit+j))
echo `printf "[%d]setting value 0x%x" $index  $round_2_val`

echo `printf "0xc8834540 %x" $round_2_val` > paddr;cat paddr ; ping -c 2 -W 1 192.168.1.1
if [ $? = 0  ] ;then
echo ping router pass !!!!
else
echo ping router fail !!!!
fi
j=$((j+1))
done
i=$((i+1)) 
done 
done
