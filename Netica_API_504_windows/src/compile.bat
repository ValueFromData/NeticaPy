rem echo off
CLS
set msvc=C:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\
call "%msvc%vcvarsall.bat" x86_amd64

echo "Compiling NeticaEx.o"
"%msvc%bin\x86_amd64\cl.exe" /c /I. NeticaEx.c /link ..\lib\Netica.lib

COPY *.obj ..\lib
echo "Done."
