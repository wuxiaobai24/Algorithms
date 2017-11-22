#!/bin/bash

for (( i = 10;i <= 10000;i=i*10))
do
    for ((j = 10;j <= 10000;j=j*10))
    do
        echo "==================================="
        echo "i = $i and j = $j"
        ./a.out $i $j 1 1 4
        echo "===================================="
    done
done
