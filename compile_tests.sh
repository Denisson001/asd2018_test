#!/bin/bash

cd tests/unit_tests
bash compile_tests.sh
cd ../..

cd tests/load_tests
bash compile_tests.sh
cd ../..

cd tests/stress_tests
bash compile_tests.sh
cd ../..
