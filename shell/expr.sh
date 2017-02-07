#!/bin/sh

echo "=>reg value test ....... "
i=10
i=$((i<<2 | 0x1000))
echo `printf "first round 0x%x" $i`
i=`expr $i + 1`
echo `printf "second round %d" $i`
i=`expr $i \* 5`
echo `printf "third round %d" $i`
