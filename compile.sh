#!/bin/sh
echo "compiling"

gcc Netica_API_504/src/NeticaExV.c -c -fPIC -I. -LNetica_API_504/bin 
cp -f NeticaExV.o Netica_API_504/lib/NeticaEx.o

#compiling cython to c
cython -a NeticaPy.pyx
#compiling C to .so file
gcc -shared -pthread -fPIC -fwrapv -O2 -Wall -fno-strict-aliasing       -I/usr/include/python2.7 Netica_API_504/lib/NeticaEx.o   NeticaPy.c    -o NeticaPy.so  -INetica_API_504/src -LNetica_API_504/lib -lrt -lnetica -lpthread -lstdc++ -lm
