# The exception handling mechanism uses three data structures:

- An unwind table, which allows the dispatcher and unwinder to associate an IP value with a procedure and its unwind and exception handling information. Every procedure that has either a memory stack frame or exception handling requirements, or both, has one entry in this table. (If the compiler has generated more than one non-contiguous region of code for a procedure, there will be one entry in this table for each region.) Each unwind table entry points to an information block that contains the other two data structures.
- A set of unwind descriptors for each procedure.
- An optional language-specific data area for each procedure.

​	The dispatcher and unwinder both use the unwind table to locate an unwind entry for a procedure, given an IP value. The unwinder also uses the unwind descriptor list so that it can properly unwind the stack from any point in the procedure. 

​	The language-specific data area is used to store cleanup actions and a try region table. 

Detailed information:

https://www.intel.com/content/dam/www/public/us/en/documents/guides/itanium-software-runtime-architecture-guide.pdf