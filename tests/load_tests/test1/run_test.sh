#!/bin/bash

echo "Entering load test 1"
ulimit -s 200000
./compile_files/test1
echo "Leaving load test 1"

