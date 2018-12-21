#!/bin/bash 
g++ main.cpp -std=c++11 -o main
for i in $(seq 1 1000)
do
echo -n $i ": " ;
time -p ./main i || break;	
done