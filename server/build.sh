#bin/bash
rm logs/ -rf
make clean

cmake .

make
