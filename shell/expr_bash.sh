#!/bin/bash

echo "=>reg value test ....... "
i=1
((i=$i\<\<3))
echo `printf "first round %d" $i`
i=`expr $i + 1`
echo `printf "second round %d" $i`
i=`expr $i \* 5`
echo `printf "third round %d" $i`
