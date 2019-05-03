#!/bin/bash

echo "Entering load test 5"
ulimit -s 200000
./compile_files/test5
echo "Leaving load test 5"

