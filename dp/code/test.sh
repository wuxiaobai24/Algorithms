#!/bin/bash

for((j=1;j<5;j++));do
    for ((i=10;i<=10000;i*=10));do
        echo "./a.out $i $i 10 $j"
        ./a.out $i $i 10 $j
    done
done
