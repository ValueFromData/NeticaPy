#!/bin/sh
echo "compiling"

gcc Netica_API_504/src/va_sum.c -c -fPIC -I. -LNetica_API_504/bin 
cp -f va_sum.o Netica_API_504/lib/va_sum.o

#compiling cython to c
cython -a Sum_va.pyx 
#compiling C to .so file
gcc -shared -pthread -fPIC -fwrapv -O2 -Wall -fno-strict-aliasing       -I/usr/include/python2.7 Netica_API_504/lib/va_sum.o   Sum_va.c    -o Sum_va.so  -INetica_API_504/src -LNetica_API_504/lib -lrt -lnetica -lpthread -lstdc++ -lm
