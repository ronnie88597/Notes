## Patch printf.h from glibc:

There is a bug in glibc printf.h: https://sourceware.org/bugzilla/show_bug.cgi?id=18907. Apply the following patch to /usr/include/printf.h to fix the bug.

```c
--- /usr/include/printf.h.orig	2016-12-13 21:34:35.897301441 +0000
+++ /usr/include/printf.h	2016-12-13 21:35:40.374031243 +0000
@@ -111,13 +111,13 @@
    it returns a positive value representing the bit set in the USER
    field in 'struct printf_info'.  */

-extern int register_printf_modifier (const wchar_t *__str) __wur __THROW;
+extern int register_printf_modifier (const wchar_t *__str) __THROW __wur;


 /* Register variable argument handler for user type.  The return value
    is to be used in ARGINFO functions to signal the use of the
    type.  */
-extern int register_printf_type (printf_va_arg_function __fct) __wur __THROW;
+extern int register_printf_type (printf_va_arg_function __fct) __THROW __wur;


 /* Parse FMT, and fill in N elements of ARGTYPES with the
```

## Reference:

https://github.com/securesystemslab/multicompiler
