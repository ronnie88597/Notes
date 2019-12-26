# What dose the 'DWARF' mean in llvm?

​	It is the backronym 'Debug With Attributed Record Formats'. DWARF is widely used, standardized debugging data format. It was originally designed along with ELF(Executable and Linkable Format), although it is independent of object file formats.

## History

​	The first version of DWARF proved to use excessive amounts of storage, and an incompatible successor, DWARF-2, superseded it and added various encoding schemes to reduce data size. DWARF did not immediately gain universal acceptance; for instance, when `Sun Microsystems` adopted ELF as part of their move to `Solaris`, they opted to continue using [stabs](https://en.wikipedia.org/wiki/Stabs), in an embedding known as "stabs-in-elf". Linux followed suit, and DWARF-2 did not become the default until the late 1990s.

​	The DWARF Workgroup of the Free Standard Group released DWARF version 3 in January 2006, adding(among other things) support for C++ namespace, Fortran 90 allocatable data and additional compiler optimation techniques.

​	The DWARF committee published version 4 of DWARF, which offers "improved data compression, better description of optimized code, and support for new language features in C++", in 2010.

​	Version 5 of the DWARF format was published in February 2017. It "incorporates improvements in many areas: better data compression, separation of debugging data from executable files, improved description of macros and source files, faster searching for symbols, improved debugging of optimized code, as well as numerous improvements in functionality and performance.

Relative information:

[DWARF 5 Standard](http://dwarfstd.org/Dwarf5Std.php)