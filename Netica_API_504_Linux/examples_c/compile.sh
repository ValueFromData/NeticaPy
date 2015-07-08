#!/bin/sh
echo "compiling"


gcc ../lib/NeticaEx.o   Demo.c            -o Demo              -I../src -L../lib -lm -lrt -lnetica -lpthread -lstdc++

echo "-----------------------------------   BuildNet"
gcc ../lib/NeticaEx.o   BuildNet.c        -o BuildNet          -I../src -L../lib -lm -lrt -lnetica -lpthread -lstdc++

echo "-----------------------------------   DoInference"
gcc ../lib/NeticaEx.o   DoInference.c    -o  DoInference       -I../src -L../lib -lm -lrt -lnetica -lpthread -lstdc++

echo "-----------------------------------   SimulateCases"
gcc ../lib/NeticaEx.o   SimulateCases.c  -o  SimulateCases     -I../src -L../lib -lm -lrt -lnetica -lpthread -lstdc++

echo "-----------------------------------   LearnCPTs"
gcc ../lib/NeticaEx.o   LearnCPTs.c      -o  LearnCPTs         -I../src -L../lib -lm -lrt -lnetica -lpthread -lstdc++

echo "-----------------------------------   LearnLatent"
gcc ../lib/NeticaEx.o   LearnLatent.c    -o  LearnLatent       -I../src -L../lib -lm -lrt -lnetica -lpthread -lstdc++

echo "-----------------------------------   NetTester"
gcc  ../lib/NeticaEx.o  NetTester.c      -o  NetTester         -I../src -L../lib -lm -lrt -lnetica -lpthread -lstdc++

echo "-----------------------------------   MakeDecision"
gcc  ../lib/NeticaEx.o  MakeDecision.c   -o  MakeDecision      -I../src -L../lib -lm -lrt -lnetica -lpthread -lstdc++

echo "-----------------------------------   ClassifyData"
gcc  ../lib/NeticaEx.o  ClassifyData.c   -o  ClassifyData      -I../src -L../lib -lm -lrt -lnetica -lpthread -lstdc++

