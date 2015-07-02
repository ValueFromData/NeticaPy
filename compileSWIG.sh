#!/bin/sh

swig -python example.i
gcc -c example.c example_wrap.c -fPIC        -I/usr/include/python2.7
ld -shared example.o example_wrap.o -o _example.so
