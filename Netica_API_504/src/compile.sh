#!/bin/sh
echo "compiling"

gcc NeticaEx.c -c -I. -L../bin 
cp -f NeticaEx.o ../lib
