echo off
CLS
set msvc=C:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\
call "%msvc%vcvarsall.bat" x86_amd64
copy ..\lib\Netica.dll

rem echo "----------------------- COMPILE STEP  Demo.c"
rem "%msvc%bin\x86_amd64\cl.exe" /c  /I..\src Demo.c  
rem echo "-----------------------   LINK  STEP  Demo.c"
rem LINK  /LIBPATH:..\lib  Netica.lib  NeticaEx.obj  Demo.obj /OUT:Demo.exe

echo "-----------------------------------   COMPILE & LINK"
echo "-----------------------------------   Demo.c
"%msvc%bin\x86_amd64\cl.exe"  /I..\src  Demo.c  ..\src\NeticaEx.c   /link ..\lib\Netica.lib  /OUT:Demo.exe
echo "-----------------------------------   BuildNet.c
"%msvc%bin\x86_amd64\cl.exe"  /I..\src  BuildNet.c      /link ..\lib\Netica.lib   ..\lib\NeticaEx.obj   /OUT:BuildNet.exe
echo "-----------------------------------   DoInference.c
"%msvc%bin\x86_amd64\cl.exe"  /I..\src  DoInference.c   /link ..\lib\Netica.lib   ..\lib\NeticaEx.obj   /OUT:DoInference.exe
echo "-----------------------------------   SimulateCases.c
"%msvc%bin\x86_amd64\cl.exe"  /I..\src  SimulateCases.c /link ..\lib\Netica.lib    /OUT:SimulateCases.exe
echo "-----------------------------------   LearnCPTs.c
"%msvc%bin\x86_amd64\cl.exe"  /I..\src  LearnCPTs.c     /link ..\lib\Netica.lib    /OUT:LearnCPTs.exe
echo "-----------------------------------   LearnLatent.c
"%msvc%bin\x86_amd64\cl.exe"  /I..\src  LearnLatent.c   /link ..\lib\Netica.lib    /OUT:LearnLatent.exe
echo "-----------------------------------   NetTester.c
"%msvc%bin\x86_amd64\cl.exe"  /I..\src  NetTester.c     /link ..\lib\Netica.lib   ..\lib\NeticaEx.obj   /OUT:NetTester.exe
echo "-----------------------------------   MakeDecision.c
"%msvc%bin\x86_amd64\cl.exe"  /I..\src  MakeDecision.c  /link ..\lib\Netica.lib   ..\lib\NeticaEx.obj   /OUT:MakeDecision.exe
echo "-----------------------------------   ClassifyData.c
"%msvc%bin\x86_amd64\cl.exe"  /I..\src  ClassifyData.c  /link ..\lib\Netica.lib   ..\lib\NeticaEx.obj   /OUT:ClassifyData.exe

echo "Done."
