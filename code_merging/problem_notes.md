# Problem notes

- About llvm/include/llvm/Config folder, there are so mang difference between multicompiler and llvm9.0,  as below:

  ![diff rlt include/llvm/Config](./img/diff_rlt_include_llvm_config.png)

  so just do not deal with his problem for now.

- In llvm9.0, header file llvm/include/llvm/IR/TypeBuilder.h has been removed. 

- In llvm9.0, header file llvm/include/llvm/Target/TargetLowering.h has been removed.

- About llvm/lib/CodeGen/SelectionDAG/DAGCombiner.cpp, for now, i can not merge multicompiler3.8 to llvm9.0, beacuse they are completely different as llvm9.0 refactored.

  ![diff rlt llvm/lib/CodeGen/SelectionDAG/DAGCombiner.cpp](./img/diff_rlt_lib_CodeGen_DAGCombiner.png)

- About the `CalcNodeSethiUllmanNumber` Function at file of llvm/lib/CodeGen/SelectionDAG/ScheduleDAGRRList.cpp, for now, I can not merge multicompiler3.8 to llvm9.0, beacuse the function has been refactored and there are so many difference.

  ![diff rlt llvm/lib/CodeGen/SelectionDAG/ScheduleDAGRRList.cpp](./img/diff_rlt_lib_CodeGen_ScheduleDAGRRList.png)


- Have `void IntrinsicLowering::AddPrototypes(Module &M)` function in llvm/lib/CodeGen/IntrinsicLowering.cpp file been removed in llvm9.0? I can not merge multicompiler3.8 to llvm9.0, beacuse I do not find the function.

  ![diff rlt llvm/lib/CodeGen/IntrinsicLowering.cpp](./img/diff_rlt_lib_CodeGen_IntrinsicLowering.png)

- Have `void MachineModuleInfo::EndFunction()` function in llvm/lib/CodeGen/MachineModuleInfo.cpp file been removed in llvm9.0? I can not merge multicompiler3.8 to llvm9.0, beacuse I do not find the function.

  ![diff rlt llvm/lib/CodeGen/MachineModuleInfo.cpp](./img/diff_rlt_lib_CodeGen_MachineModuleInfo.png)

- As the Function `void MIPrinter::print(const MachineOperand &Op, const TargetRegisterInfo *TRI,unsigned I, bool ShouldPrintRegisterTies, bool IsDef)` has been refactored in llvm/lib/CodeGen/MIRPrinter.cpp file, there are so many differences between multicompiler3.8 and llvm9.0, for now I can not to merge.

  ![diff rlt llvm/lib/CodeGen/MIRPrinter.cpp](/home/cmp/work_dir/Notes/code_merging/img/diff_rlt_CodeGen_MIRPrinter.png)

- In llvm9.0, header file llvm/lib/CodeGen/Passes.cpp has been removed.

- As the function `void PEI::calculateFrameObjectOffsets` has been refactored in llvm/lib/CodeGen/PrologEpilogInserter.cpp file In llvm9.0, there are so many differences between multicompiler3.8 and llvm9.0, for now I can not to merge.

  ![diff rlt llvm/lib/CodeGen/PrologEpilogInserter.cpp](./img/diff_rlt_lib_CodeGen_PrologEpilogInserter.png)

- As the function `uint64_t AttributeImpl::getAttrMask(Attribute::AttrKind Val)` in llvm/lib/IR/Attributes.cpp file has been removed, for now I can not to merge.

  ![diff rlt llvm/lib/IR/Attributes.cpp](/home/cmp/work_dir/Notes/code_merging/img/diff_rlt_lib_IR_Attributes.png)

- As the function `ConstantInt::ConstantInt` in llvm/lib/IR/Constants.cpp file has been refactored , for now I can not to merge.

  ![diff rlt llvm/lib/IR/Constants.cpp](./img/diff_rlt_lib_IR_Constants.png)

- In llvm9.0, header file llvm/lib/IR/ValueTypes.cpp has been removed.

- As the function `void Verifier::verifyAttributeTypes` has been refactored, for now I can not to merge.

  ![diff rlt llvm/lib/IR/ValueTypes.cpp](./img/diff_rlt_lib_IR_Verifier.png)

- As the function `void IRLinker::materializeInitFor` in llvm/lib/Linker/IRMover.cpp file has been removed, for now I can not to merge.

  ![diff rlt llvm/lib/Linker/IRMover.cpp](./img/diff_rlt_lib_Linker_IRMover.png)

- There are so many differences in llvm/lib/Target/X86/X86InstrInfo.td file, I can not merge.

  ![diff rlt llvm/lib/Target/X86/X86InstrInfo.td](./img/diff_rlt_lib_Target_X86_X86InstrInfo.png)

- As the function `X86TargetLowering::LowerCall` in llvm/lib/Target/X86/X86ISelLowering.cpp file has been refactored, I can not merge.

  ![diff rlt llvm/lib/Target/X86/X86ISelLowering.cpp](./img/diff_rlt_lib_Target_X86_X86ISelLowering.png)

- As the function `X86TargetLowering::LowerGlobalAddress` in llvm/lib/Target/X86/X86ISelLowering.cpp and llvm/lib/Target/X86/X86ISelLowering.h has been refactored, I can not merge.

  ![diff rlt llvm/lib/Target/X86/X86ISelLowering.cpp](./img/diff_rlt_lib_Target_X86_X86ISelLowering2.png)

- For now, I leave llvm/patches, llvm/projects, llvm/test alone without dealing.

  ![llvm/patches, llvm/projects, llvm/test](./img/patches_projects_test.png)

- As `configure & make` was not deprecated, for now, I do not merge llvm/configure and llvm/Makefile.

- As llvm/tools/clang/lib/Basic/Targets.cpp has been refactored, I can not merge.

- As the function `EmitAssemblyHelper::CreateTargetMachine` in llvm/tools/clang/lib/CodeGen/BackendUtil.cpp file has been refactored, I can not merge.

  ![diff rlt llvm/tools/clang/lib/CodeGen/BackendUtil.cpp](./img/diff_rlt_clang_lib_CodeGen_BackendUtil.png)

- As the function `void CodeGenVTables::createVTableInitializer` in llvm/tools/clang/lib/CodeGen/CGVTables.cpp file has been refactored, I can not merge.

  ![diff rlt llvm/tools/clang/lib/CodeGen/CGVTables.cpp](./img/diff_rlt_clang_lib_CodeGen_CGVTables.png)

- As the function `CodeGenFunction::StartFunction` in llvm/tools/clang/lib/CodeGen/CodeGenFunction.cpp file has been refactored, I can not merge.

  ![](./img/diff_rlt_clang_lib_CodeGen_CodeGenFunction.png)

- As the `CodeGenModule::isInSanitizerBlacklist` function in llvm/tools/clang/lib/CodeGen/CodeGenModule.cpp file has been refactored, I can not merge.

  ![diff rlt llvm/tools/clang/lib/CodeGen/CodeGenModule.cpp](/home/cmp/work_dir/Notes/code_merging/img/diff_rlt_clang_lib_CodeGen_CodeGenModule.png)

- As the `hasAnyUsedVirtualInlineFunction` function in llvm/tools/clang/lib/CodeGen/ItaniumCXXABI.cpp file has been refactored, I can not merge.

  ![diff rlt llvm/tools/clang/lib/CodeGen/ItaniumCXXABI.cpp](./img/diff_rlt_clang_lib_CodeGen_ItaniumCXXABI.png)

- As the `ItaniumCXXABI::EmitLoadOfMemberFunctionPointer` Function in llvm/tools/clang/lib/CodeGen/ItaniumCXXABI.cpp file has been refactored, I can not merge.

  ![diff rlt llvm/tools/clang/lib/CodeGen/ItaniumCXXABI.cpp](./img/diff_rlt_clang_lib_CodeGen_ItaniumCXXABI2.png)

- There so many differences in llvm/tools/clang/lib/CodeGen/ItaniumCXXABI.cpp, you would better merge it carefully.

- As the `MicrosoftCXXABI::emitVTableDefinitions` function in llvm/tools/clang/lib/CodeGen/MicrosoftCXXABI.cpp file has been refactored, I can not merge.

  ![diff rlt llvm/tools/clang/lib/CodeGen/MicrosoftCXXABI.cpp](./img/diff_rlt_clang_lib_CodeGen_MicrosoftCXXABI.png)

- As the `SanitizerArgs::clear` function be remove in llvm/tools/clang/lib/Driver/SanitizerArgs.cpp file has been removed, I can not merge.

  ![diff rlt llvm/tools/clang/lib/Driver/SanitizerArgs.cpp](./img/diff_rlt_clang_lib_Drive_SanitizerArgs.png)

- As the `getSupportedSanitizers` function in llvm/tools/clang/lib/Driver/ToolChains.cpp file as been refactored, I can not merge.

  ![diff rlt llvm/tools/clang/lib/Driver/ToolChains.cpp](/home/cmp/work_dir/Notes/code_merging/img/diff_rlt_clang_lib_Driver_ToolChains.png)

- The llvm/tools/clang/lib/Driver/Tools.cpp file has been removed.

- 

- 

- 

- 

- 

- 

- 

- 

  
