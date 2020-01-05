# Life of an instruction in LLVM

​	LLVM is a complex piece of software. There are several paths one may take on the quest of understanding how it works, none of which is simple. I recently had to dig in some areas of LLVM I was not previously familiar with, and this article is one of the outcomes of this quest.

​	What I aim to do here is follow the various incarnations an "instruction" takes when it goes through LLVM's multiple compilation stages, starting from a syntactic construct in the source language and until being encoded as binary machine code in an ouput object file.

​	This article in itself will not teach one how LLVM works. It assumes some existing familiarity with LLVM's design and code base, and leaves a lot of "obvious" detail out. Note that unless otherwise stated, the information here is relevant to LLVM9.0. LLVM and Clang are fast-moving projects, and future changes may render parts of this article incorrect. If you notice any discrepancies, please let me know and I'll do my best to fix them.

## Input code

​	I want to start this exploration process at the beginning - C  source. Here's the simple function we're going to work with:

```C
int foo(int aa, int bb, int cc){
	int sum = aa + bb;
	return sum / cc;
}
```

​	The focus of this article is going to be on the division operation.

## Clang

​	Clang serves as the frontend for LLVM, responsible for converting C, C++ and ObjC source in LLVM IR. Clang's main complexity comes from the ability to correctly parse and semantically analyze C++; The flow from a simple C-level operation is actually quite straightforward.

​	Clang's parser builds an Abstract Syntax Tree (AST) out of the input. The AST is the main "currency" in which various parts of Clang deal. For our division operation, a `BinaryOperator` node is created in the AST, carrying the `BO_div` "operator kind".

​	Use Clang to print AST:

```shell
$ ./clang -cc1 /tmp/1.c -ast-dump
```

Result:

```
TranslationUnitDecl 0x5619c4e968d8 <<invalid sloc>> <invalid sloc>
|-TypedefDecl 0x5619c4e97170 <<invalid sloc>> <invalid sloc> implicit __int128_t '__int128'
| `-BuiltinType 0x5619c4e96e70 '__int128'
|-TypedefDecl 0x5619c4e971e0 <<invalid sloc>> <invalid sloc> implicit __uint128_t 'unsigned __int128'
| `-BuiltinType 0x5619c4e96e90 'unsigned __int128'
|-TypedefDecl 0x5619c4e974c8 <<invalid sloc>> <invalid sloc> implicit __NSConstantString 'struct __NSConstantString_tag'
| `-RecordType 0x5619c4e972c0 'struct __NSConstantString_tag'
|   `-Record 0x5619c4e97238 '__NSConstantString_tag'
|-TypedefDecl 0x5619c4e97560 <<invalid sloc>> <invalid sloc> implicit __builtin_ms_va_list 'char *'
| `-PointerType 0x5619c4e97520 'char *'
|   `-BuiltinType 0x5619c4e96970 'char'
|-TypedefDecl 0x5619c4e97838 <<invalid sloc>> <invalid sloc> implicit __builtin_va_list 'struct __va_list_tag [1]'
| `-ConstantArrayType 0x5619c4e977e0 'struct __va_list_tag [1]' 1 
|   `-RecordType 0x5619c4e97640 'struct __va_list_tag'
|     `-Record 0x5619c4e975b8 '__va_list_tag'
`-FunctionDecl 0x5619c4ef4cd0 </tmp/1.c:1:1, line:4:1> line:1:5 foo 'int (int, int, int)'
  |-ParmVarDecl 0x5619c4ef4ae0 <col:9, col:13> col:13 used aa 'int'
  |-ParmVarDecl 0x5619c4ef4b60 <col:17, col:21> col:21 used bb 'int'
  |-ParmVarDecl 0x5619c4ef4be0 <col:25, col:29> col:29 used cc 'int'
  `-CompoundStmt 0x5619c4ef4f98 <col:33, line:4:1>
    |-DeclStmt 0x5619c4ef4ee0 <line:2:3, col:20>
    | `-VarDecl 0x5619c4ef4de8 <col:3, col:18> col:7 used sum 'int' cinit
    |   `-BinaryOperator 0x5619c4ef4ec0 <col:13, col:18> 'int' '+'
    |     |-ImplicitCastExpr 0x5619c4ef4e90 <col:13> 'int' <LValueToRValue>
    |     | `-DeclRefExpr 0x5619c4ef4e50 <col:13> 'int' lvalue ParmVar 0x5619c4ef4ae0 'aa' 'int'
    |     `-ImplicitCastExpr 0x5619c4ef4ea8 <col:18> 'int' <LValueToRValue>
    |       `-DeclRefExpr 0x5619c4ef4e70 <col:18> 'int' lvalue ParmVar 0x5619c4ef4b60 'bb' 'int'
    `-ReturnStmt 0x5619c4ef4f88 <line:3:3, col:16>
      `-BinaryOperator 0x5619c4ef4f68 <col:10, col:16> 'int' '/'
        |-ImplicitCastExpr 0x5619c4ef4f38 <col:10> 'int' <LValueToRValue>
        | `-DeclRefExpr 0x5619c4ef4ef8 <col:10> 'int' lvalue Var 0x5619c4ef4de8 'sum' 'int'
        `-ImplicitCastExpr 0x5619c4ef4f50 <col:16> 'int' <LValueToRValue>
          `-DeclRefExpr 0x5619c4ef4f18 <col:16> 'int' lvalue ParmVar 0x5619c4ef4be0 'cc' 'int'
```

​	Clang's code generator then goes on to emit a `sdiv` LLVM IR instruction from the node, since this is a division of signed integeral types.

## LLVM IR

​	To get the LLVM IR:

```shell
$ ./clang -S -emit-llvm /tmp/1.c -o -
```

​	Here is the LLVM IR created for the function:

```
; ModuleID = '/tmp/1.c'
source_filename = "/tmp/1.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @foo(i32 %aa, i32 %bb, i32 %cc) #0 {
entry:
  %aa.addr = alloca i32, align 4
  %bb.addr = alloca i32, align 4
  %cc.addr = alloca i32, align 4
  %sum = alloca i32, align 4
  store i32 %aa, i32* %aa.addr, align 4
  store i32 %bb, i32* %bb.addr, align 4
  store i32 %cc, i32* %cc.addr, align 4
  %0 = load i32, i32* %aa.addr, align 4
  %1 = load i32, i32* %bb.addr, align 4
  %add = add nsw i32 %0, %1
  store i32 %add, i32* %sum, align 4
  %2 = load i32, i32* %sum, align 4
  %3 = load i32, i32* %cc.addr, align 4
  %div = sdiv i32 %2, %3
  ret i32 %div
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 9.0.0 (https://github.com/llvm/llvm-project.git 0399d5a9682b3cef71c653373e38890c63c4c365)"}
```

​	In LLVM IR, `sdiv` is a `BinaryOperator`, which is a subclass of [Instruction](https://llvm.org/doxygen/classllvm_1_1Instruction.html) with the opcode `SDiv`(defined in llvm/IR/Instruction.def). Like any other instruction, it can be processed by the LLVM analysis and transformation passes. For a specific example targeted at `SDiv`, take a look at `SimplifySDivInst`(in file llvm/lib/Analysis/InstructionSimplify.cpp). Since all through the LLVM "middle-end" layer the instruction remains in its IR form, I won't spend much time talking about it. To witness its next incarnation, we'll have to look at the LLVM code generator.

​	The code generator is one of the most complex parts of LLVM. Its task is to "lower" the relatively high-level, target-independent LLVM IR into low-level, target-dependent "machine instructions"(MachineInstr). On its way to a `MachineInstr`, an LLVM IR instruction passes through a "selection DAG node" incarnation, which is what I'm going to discuss next.

## Selection DAG node

​	Selection DAG nodes are created by the `SelectionDAGBuilder`(defined in file llvm/lib/CodeGen/SelectionDAG/ls SelectionDAGBuilder.h) class acting "at the service of" `SelectionDAGISel`(defined in file llvm/include/llvm/CodeGen/SelectionDAGISel.h ), which is the main base class for instruction selection. `SelectionDAGISel` goes over all the IR instructions and calls the `SelectionDAGBuilder::visit` dispatcher on them. The method handling a `SDiv` instruction is `SelectionDAGBuilder::visitSDiv`. It requests a new `SDNode` from the DAG with the opcode `ISD::SDIV`, which becomes a node in the DAG.

![selection instruction flow chart diagram](./img/Selection instruction flow chart diagram.png)

​	The initial DAG constructed this way is still only partially target dependent. In LLVM nomenclature it's called "illegal" - the types it contains may not be directly supported by the target; the same is true for the operations it contains.

​	There are a couple of ways to visualize the DAG. One is to pass the `-debug` flag to llc, which will cause it to create a textual dump of the DAG during all the selection phases. Another is to pass one of the `-view` options which causes it to dump and display an actual image of the graph(more detail in the [code generator docs](http://llvm.org/docs/CodeGenerator.html)). Here's the relevant porition of the DAG showing our `SDiv` node, right after DAG creation(the `sdiv` node is in the bottom):

1.Before creating DAG graph, you must install a few of component:

```shell
sudo apt-get install -y graphviz
sudo apt-get install graphviz-dev graphviz-doc libgraphviz-dev
which dot
if [ $? -eq 0 ];then
	echo "SUCC"
else
	echo "FAILED"
	exit 1
fi
```

2.





## Related information:

https://eli.thegreenplace.net/2012/11/24/life-of-an-instruction-in-llvm/#id1