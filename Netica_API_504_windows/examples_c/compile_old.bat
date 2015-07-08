echo off
CLS

copy ..\lib\Netica.dll

rem echo "----------------------- COMPILE STEP  Demo.c"
rem CL.EXE /c  /I..\src Demo.c  
rem echo "-----------------------   LINK  STEP  Demo.c"
rem LINK  /LIBPATH:..\lib  Netica.lib  NeticaEx.obj  Demo.obj /OUT:Demo.exe

echo "-----------------------------------   COMPILE & LINK"
echo "-----------------------------------   Demo.c
CL.EXE  /I..\src  Demo.c  ..\src\NeticaEx.c   /link ..\lib\Netica.lib  /OUT:Demo.exe
echo "-----------------------------------   BuildNet.c
CL.EXE  /I..\src  BuildNet.c      /link ..\lib\Netica.lib   ..\lib\NeticaEx.obj   /OUT:BuildNet.exe
echo "-----------------------------------   DoInference.c
CL.EXE  /I..\src  DoInference.c   /link ..\lib\Netica.lib   ..\lib\NeticaEx.obj   /OUT:DoInference.exe
echo "-----------------------------------   SimulateCases.c
CL.EXE  /I..\src  SimulateCases.c /link ..\lib\Netica.lib    /OUT:SimulateCases.exe
echo "-----------------------------------   LearnCPTs.c
CL.EXE  /I..\src  LearnCPTs.c     /link ..\lib\Netica.lib    /OUT:LearnCPTs.exe
echo "-----------------------------------   LearnLatent.c
CL.EXE  /I..\src  LearnLatent.c   /link ..\lib\Netica.lib    /OUT:LearnLatent.exe
echo "-----------------------------------   NetTester.c
CL.EXE  /I..\src  NetTester.c     /link ..\lib\Netica.lib   ..\lib\NeticaEx.obj   /OUT:NetTester.exe
echo "-----------------------------------   MakeDecision.c
CL.EXE  /I..\src  MakeDecision.c  /link ..\lib\Netica.lib   ..\lib\NeticaEx.obj   /OUT:MakeDecision.exe
echo "-----------------------------------   ClassifyData.c
CL.EXE  /I..\src  ClassifyData.c  /link ..\lib\Netica.lib   ..\lib\NeticaEx.obj   /OUT:ClassifyData.exe

echo "Done."
