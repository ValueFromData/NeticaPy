rem echo off
CLS

echo "Compiling NeticaEx.o"

CL.EXE /c /I. NeticaEx.c /link ..\lib\Netica.lib
COPY *.obj ..\lib
echo "Done."
