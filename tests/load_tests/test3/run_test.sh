#!/bin/bash

echo "Entering load test 3"
ulimit -s 200000
./compile_files/test3
echo "Leaving load test 3"

