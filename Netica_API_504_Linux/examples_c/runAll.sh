#!/bin/sh
LD_LIBRARY_PATH=../lib
export LD_LIBRARY_PATH

echo "-----------------------------------   running Demo"
./Demo
echo "-----------------------------------   running BuildNet"
./BuildNet
echo "-----------------------------------   running DoInference"
./DoInference
echo "-----------------------------------   running Simulate"
#IF EXIST "ChestClinic.cas". (DEL "ChestClinic.cas".)  
rm -f ChestClinic.cas
./SimulateCases
echo "-----------------------------------   running LearnCPTs"
./LearnCPTs
echo "-----------------------------------   running LearnLatent"
./LearnLatent
echo "-----------------------------------   running NetTester"
#./NetTester (don't run; not ready yet)
echo "-----------------------------------   running MakeDecision"
./MakeDecision
echo "-----------------------------------   running ClassifyData"
#./ClassifyData  (don't run; not ready yet)
