@ECHO OFF
CLS
IF %PROCESSOR_ARCHITECTURE% EQU x86  (copy Netica_API_504_windows\lib\32 bit\*.* Netica_API_504_windows\lib\) ELSE IF %PROCESSOR_ARCHITECTURE% EQU X86  (copy Netica_API_504_windows\lib\32bit\*.* Netica_API_504_windows\lib\) ElSE  (copy Netica_API_504_windows\lib\64bit\*.* Netica_API_504_windows\lib\)
set msvc=%userprofile%\AppData\Local\Programs\Common\Microsoft\Visual C++ for Python\9.0\
call "%msvc%vcvarsall.bat" %PROCESSOR_ARCHITECTURE%

cd Netica_API_504_windows\src
echo "Compiling NeticaEx.o"
"%msvc%VC\bin\%PROCESSOR_ARCHITECTURE%\cl.exe" /c /I. NeticaEx.c /link ..\lib\Netica.lib
COPY *.obj ..\lib\
cd ..\..
copy Netica_API_504_windows\lib\Netica.dll
COPY Netica_API_504_windows\NeticaPy.pyx
echo compiling cython to c
cython -a NeticaPy.pyx
"%msvc%VC\bin\%PROCESSOR_ARCHITECTURE%\cl.exe"  /nologo /LD /W4  /INetica_API_504_windows\src\ /IC:\Python27\include  /IC:\Python27\PC /FeNeticaPy.pyd  /TcNeticaPy.c    /link Netica_API_504_windows\lib\NeticaEx  /link Netica_API_504_windows\lib\Netica.lib /dll  /libpath:C:\Python27\libs 
"%msvc%VC\bin\%PROCESSOR_ARCHITECTURE%\cl.exe" /LD /W4   /D_USRDLL /D_WINDLL  /INetica_API_504_windows\src\ /IC:\Python27\include  /IC:\Python27\PC  /TcNeticaPy.c    /link Netica_API_504_windows\lib\NeticaEx  /link Netica_API_504_windows\lib\Netica.lib   /dll /libpath:C:\Python27\libs /OUT:NeticaPy.dll

del *.c
del *.html
del *.pyx
del *.obj
del *.lib
del *.exe


echo "Done."
