# How to solve ExecutionEngine OprofileJIT compilation error?

My llvm source is HEAD detached at llvmorg-9.0.0.

After making llvm cmake project, and compiling it, an error occured. As follow:

![OProfileJIT_compilation_error](/home/cmp/work_dir/Notes/llvm/img/OProfileJIT_ERROR.png)

The way to solve this problem is that modifying file 'llvm/lib/ExecutionEngine/OProfileJIT/OProfileJITEventListener.cpp', and recompile.

```c++
104     uint64_t Addr = *AddrOrErr;
105 +++                                                                         
106 +++                                                                         
107 +++ //---------------FIX COMPILE ERROR                                      
108 +++ auto SecOrErr = Sym.getSection();                                       
109 +++ if (!SecOrErr) {                                                        
110 +++     // TODO: Actually report errors helpfully.                          
111 +++     consumeError(SecOrErr.takeError());                                 
112 +++     continue;                                                           
113 +++ }                                                                       
114 +++ object::section_iterator Sec = *SecOrErr;                               
115 +++ if (Sec == Obj.section_end())                                           
116 +++     continue;                                                           
117 +++ uint64_t Index = Sec->getIndex();                                       
118 +++ //---------------FIX COMPILE ERROR                                      
119 +++                                                                         
120 +++                                                                         
121     uint64_t Size = P.second;
122 
123     if (Wrapper->op_write_native_code(Name.data(), Addr, (void *)Addr, Size)
124         -1) {
125       LLVM_DEBUG(dbgs() << "Failed to tell OProfile about native function "
126                         << Name << " at [" << (void *)Addr << "-"
127                         << ((char *)Addr + Size) << "]\n");
128       continue;
129     }
130 
131 +++ DILineInfoTable Lines = Context->getLineInfoForAddressRange({Addr,Index});
115 --- DILineInfoTable Lines = Context->getLineInfoForAddressRange(Addr, Size);
```

