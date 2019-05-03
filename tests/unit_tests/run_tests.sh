#!/bin/bash

ulimit -s 65536
./compile_files/tests --log_level=test_suite
