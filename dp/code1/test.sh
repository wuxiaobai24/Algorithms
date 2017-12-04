#!/bin/bash
for((j=10;j<=1000;j*=10));do
    for ((i=10;i<=1000;i*=10));do
        echo "./a.out $i $j 5 3"
        ./a.out $i $j 5 3
    done
done


