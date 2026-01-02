#!/bin/bash
cd ../build/ && make -j && cd ../tests

g++ -o test test.cc ../build/libleveldb.a -I../include -pthread
./test
rm ./test