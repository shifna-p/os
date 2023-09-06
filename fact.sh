#!/bin/sh
# enter number
echo " Enter a number : "
read n1
factorial=1
while [ $n1 -gt 1 ]
do
  factorial=$((factorial*n1))
  n1=$((n1-1))
done
echo "FActorial of given number $n1 is : $factorial"