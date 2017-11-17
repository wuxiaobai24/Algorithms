#!/bin/bash

for i in 10,100,1000,10000
do
    for j in 10,100,1000,10000
    do
        echo "i = $i and j = $j"
        ./a.out $i $j 1
        echo "===================================="
    done
done
