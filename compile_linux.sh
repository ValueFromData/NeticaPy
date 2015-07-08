#!/bin/sh

if $(uname -m | grep '64'); then
cp -f Netica_API_504_Linux/lib/64bit/libnetica.a Netica_API_504_Linux/lib/libnetica.a
else
cp -f Netica_API_504_Linux/lib/32bit/libnetica.a Netica_API_504_Linux/lib/libnetica.a
fi

echo "compiling"
cp Netica_API_504_Linux/NeticaPy.pyx
gcc Netica_API_504_Linux/src/NeticaEx.c -c -fPIC -I. -LNetica_API_504_Linux/bin 
cp -f NeticaEx.o Netica_API_504_Linux/lib/NeticaEx.o

#compiling cython to c
cython -a NeticaPy.pyx
#compiling C to .so file
gcc -shared -pthread -fPIC -fwrapv -O2 -Wall -fno-strict-aliasing       -I/usr/include/python2.7 Netica_API_504_Linux/lib/NeticaEx.o   NeticaPy.c    -o NeticaPy.so  -INetica_API_504_Linux/src -LNetica_API_504_Linux/lib -lrt -lnetica -lpthread -lstdc++ -lm
