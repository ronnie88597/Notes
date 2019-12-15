# Where are diagnostic severity levels defined?

Diagnostics are created by adding an entry to one of the `clang/Basic/Diagnostic*Kinds.td` files, depending on what library will be using it. From this file, `tblgen` generates the unique ID of the diagnostic.

​	These severity level are mapped into a smaller set ( the Diagnostic::level enum, {Ignored, Note, Remark, Warning, Error, Fatal}) of output levels by the diagnostics subsystem based on various configuration options.