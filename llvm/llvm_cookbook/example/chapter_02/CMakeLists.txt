cmake_minimum_required(VERSION 3.14)
project(chapter_02)
add_executable(chapter_02 toy.cpp)
set(EXECUTABLE_OUTPUT_PATH bin)
target_include_directories(chapter_02 PUBLIC
        ../../../../../source_code/llvm-project_install/include)
target_link_directories(chapter_02 PUBLIC
        ../../../../../source_code/llvm-project_install/lib)
target_link_libraries(chapter_02
        -lLLVMXRay -lLLVMWindowsManifest -lLLVMTextAPI -lLLVMTableGen -lLLVMSymbolize -lLLVMDebugInfoPDB -lLLVMPerfJITEvents -lLLVMOrcJIT -lLLVMJITLink -lLLVMOProfileJIT -lLLVMObjectYAML -lLLVMMIRParser -lLLVMMCA -lLLVMLTO -lLLVMPasses -lLLVMObjCARCOpts -lLLVMLineEditor -lLLVMLibDriver -lLLVMInterpreter -lLLVMIntelJITEvents -lLLVMFuzzMutate -lLLVMMCJIT -lLLVMExecutionEngine -lLLVMRuntimeDyld -lLLVMDlltoolDriver -lLLVMOption -lLLVMDebugInfoGSYM -lLLVMCoverage -lLLVMCoroutines -lLLVMipo -lLLVMInstrumentation -lLLVMVectorize -lLLVMLinker -lLLVMIRReader -lLLVMAsmParser -lLLVMX86Disassembler -lLLVMX86AsmParser -lLLVMX86CodeGen -lLLVMGlobalISel -lLLVMSelectionDAG -lLLVMAsmPrinter -lLLVMDebugInfoDWARF -lLLVMCodeGen -lLLVMTarget -lLLVMScalarOpts -lLLVMInstCombine -lLLVMAggressiveInstCombine -lLLVMTransformUtils -lLLVMBitWriter -lLLVMAnalysis -lLLVMProfileData -lLLVMX86Desc -lLLVMObject -lLLVMMCParser -lLLVMBitReader -lLLVMCore -lLLVMRemarks -lLLVMBitstreamReader -lLLVMMCDisassembler -lLLVMMC -lLLVMDebugInfoCodeView -lLLVMDebugInfoMSF -lLLVMBinaryFormat -lLLVMX86Utils -lLLVMX86Info -lLLVMSupport -lLLVMDemangle
        pthread)