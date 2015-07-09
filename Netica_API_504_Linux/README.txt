

              Netica API Programmer's Library, version 5.04      2012-01-21
              ---------------------------------------------

     For Linux, on kernels 2.6.38(64bit) or newer (and maybe some older).
     Tested on Ubuntu 11.0 and Centos 6.2
     Compiled with gcc 4.4.6 (32bit) and 4.5.2 (64bit).

FILES INCLUDED
--------------

To install, expand the .zip file downloaded from the website or copied
from the disk sent to you, and put them in the hard disk directory of 
your choice (/home/userAccount/Netica/API/ is a possibility).

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

lib/libnetica.a ----------- The Netica library (32 bit binary file)
lib/64bit/.. -------------- Version of the above for 64 bit Linux; if on 64bit, use this version for lib/libnetica.a 

src/Netica.h -------------- Header file for Netica-C API
src/NeticaEx.c ------------ Extra C source code for Netica-C
src/NeticaEx.h ------------ Header file for NeticaEx.c
src/compile.sh ------------ script to create NeticaEx.o and place it in lib, if you use NeticaEx funtions

examples_c/Demo.c --------- First Source code file to try, to confirm correct installation of Netica API
examples_c/*.c    --------- Additional source code to demonstrate common uses of Netica API


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

The best first step is to get the Demo program working.

>cd src
>./compile.sh 
>cd ../examples_c
>./compile.sh
>./runDemo.sh

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
Notice that 64 bit version of the library is available in the '64bit'
folder within 'lib'.


PROBLEMS
--------

If you have problems, contact Norsys at:    support@norsys.com


Norsys Software Corp.
www.norsys.com











