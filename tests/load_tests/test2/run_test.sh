#!/bin/bash

echo "Entering load test 2"
ulimit -s 200000
./compile_files/test2
echo "Leaving load test 2"

