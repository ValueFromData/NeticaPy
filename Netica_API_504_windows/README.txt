

              Netica API Programmer's Library, version 5.04      2012-01-21
              ---------------------------------------------

       Dynamic Link Library (DLL) for Microsoft Windows (95/NT4 to Vista and 7)


FILES INCLUDED
--------------

To install, expand the .zip file downloaded from the website or copied
from the disk sent to you, and put them in the hard disk directory of 
your choice (C:\Netica\API\ is a possibility).

After unzipping, you should have a new folder with the 
following subfolders in it:

doc ----------- Documentation on using Netica-C API
lib ----------- The Netica-C binaries
src ----------- Source code useful for working with Netica-C
examples_c ---- Example files and projects showing how to use Netica-C

Some important files are:

doc/NeticaAPIMan_C.pdf ---- The manual for Netica-C
doc/webdocs/index.html ---- Reference for all the functions of Netica-C
doc/LicAgree.txt ---------- License agreement

lib/Netica.dll ------------ The Netica library (32 bit binary file)
lib/Netica.lib ------------ For the linker to link Netica.dll
lib/64bit/.. -------------- Versions of the above for 64 bit projects

src/Netica.h -------------- Header file for Netica-C API
src/NeticaEx.c ------------ Extra C source code for Netica-C
src/NeticaEx.h ------------ Header file for NeticaEx.c

examples_c/Demo.c --------- Source code to try Netica API
examples_c/Demo.dsw ------- Example project for Demo.c


LICENSE AGREEMENT
-----------------

Before using Netica, make sure you accept the license agreement,
which is included with this package.  If not, return Netica unused 
for a refund.


MANUAL and ONSCREEN HELP
------------------------

All information required to use Netica-C is contained in the manual
doc/NeticaAPIMan_C.pdf, and you can continue installing Netica from
that instead of reading this file if you wish.

Also, be sure to open  doc/webdocs/index.html  with your web browser,
and bookmark that page, since it is a great reference, and is the most 
useful tool for working with Netica-C.


DEMO PROJECT
------------

The best first step is to get the example project working.

If you are working with Visual C++ (6.xx to 2010), 
then open:  examples_c\Demo.dsp
Note that this project is in 6.xx format, so that old development 
environments can work with it, but new ones should automatically upgrade 
it when they open it.

If you have an even earlier version of Visual C++, or a different compiler,
then you should make a project consisting of:  
lib\  Netica.dll  Netica.lib
src\  Netica.h    NeticaEx.c  NeticaEx.h
examples_c\  Demo.c

Choose "Build Demo" from the Build menu, and check that everything
compiles and links without errors, as it constructs your executable
Demo.exe.  

Then try running it by choosing  Debug->Start Debugging.

If it displays the welcome message, and does some simple probabilistic
inference without any errors, then your installation is successful.


LICENSE PASSWORD
----------------

If you have a license password, the next step is to make sure it works.
In Demo.c, change the line that says:

    env = NewNeticaEnviron_ns (NULL, NULL, NULL);

to one that says:

    env = NewNeticaEnviron_ns ("...", NULL, NULL);

where "..." is the license password provided to you by email, on your shipped 
CD-ROM, or on your invoice.  Then recompile, relink and run it again.
If you get the same message as before (except without the "Netica operating 
without a password ..." line), then your password is working properly.


YOUR PROJECTS
-------------

Once you have the example program running, you can duplicate the "Demo"
project, replace Demo.c with your own source files, and you are ready to 
build your own application.

Alternately, you can simply include Netica.dll and Netica.lib in an existing
project.  If you suspect that any of your project's compiler or linker 
options are incompatible with Netica, you can check to see if they are 
different from the options in the Demo project.  Demo is a console 
application, but of course Netica.dll will work in other types of Windows 
applications as well.

Whenever you run an application which requires Netica dll, Windows must be
  able to find it in one of the following directories:
  1. The directory where the executable module is located.
  2. The current directory.
  3. The Windows system directory ('GetSystemDirectory' function retrieves
     the path of this directory). 
  4. The Windows directory (the 'GetWindowsDirectory' function retrieves 
     the path of this directory).
  5. The directories listed in the PATH environment variable. 


PROGRAMMING LANGUAGES
---------------------

Netica API is available for programming in Java, C#, Visual Basic, C and C++.
For more information on Netica API for different languages, see the
Norsys web site.


FUTURE VERSIONS
---------------

If you just purchased Netica, your purchase price includes all version 
4.xx releases of Netica (for your chosen operating system), so your 
license password will work on all of them.  
They may be downloaded from the Norsys web site.


SPECIAL BUILDS
--------------

Versions of the Netica API library built with different options,
or for different compilers or operating systems, may be purchased from 
Norsys.  Contact Norsys with your request.
Notice that 64 bit versions of the library are available in the '64bit'
folder within 'lib'.


PROBLEMS
--------

If you have problems, contact Norsys at:    support@norsys.com


Norsys Software Corp.
www.norsys.com











