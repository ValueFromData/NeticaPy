echo off
CLS
set PATH=.;..\lib;%PATH%


echo "-----------------------------------   running Demo
Demo
echo "-----------------------------------   running BuildNet
BuildNet
echo "-----------------------------------   running DoInference
DoInference
echo "-----------------------------------   running Simulate
IF EXIST "ChestClinic.cas". (DEL "ChestClinic.cas".)
SimulateCases
echo "-----------------------------------   running LearnCPTs
LearnCPTs
echo "-----------------------------------   running LearnLatent
LearnLatent
echo "-----------------------------------   running NetTester
NetTester
echo "-----------------------------------   running MakeDecision
MakeDecision
echo "-----------------------------------   running ClassifyData
ClassifyData

