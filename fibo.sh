#!/bin/sh
echo "enter number for fibonacci "
read n
a=0
b=1
echo "seriees "
echo $a
echo $b
count=2
while [ $count -lt $n ]
do
fib=$(($a+$b))
a=$b
b=$fib
echo $fib
count=$(($count+1))
done