aux_source_directory(. src)
add_library(Parser ${src})
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

MESSAGE("LLVM_INSTALL_DIR = ${LLVM_INSTALL_DIR}")
target_include_directories(Parser PUBLIC
        ${PROJECT_BINARY_DIR}/include
        ${LLVM_INSTALL_DIR}/include
        )

target_link_directories(Parser PUBLIC
        ${PROJECT_BINARY_DIR}/lib
        ${LLVM_INSTALL_DIR}/lib
        )

target_link_libraries(Parser
        -lLLVMXRay -lLLVMWindowsManifest -lLLVMTextAPI -lLLVMTableGen -lLLVMSymbolize -lLLVMDebugInfoPDB -lLLVMPerfJITEvents -lLLVMOrcJIT -lLLVMJITLink -lLLVMOProfileJIT -lLLVMObjectYAML -lLLVMMIRParser -lLLVMMCA -lLLVMLTO -lLLVMPasses -lLLVMObjCARCOpts -lLLVMLineEditor -lLLVMLibDriver -lLLVMInterpreter -lLLVMIntelJITEvents -lLLVMFuzzMutate -lLLVMMCJIT -lLLVMExecutionEngine -lLLVMRuntimeDyld -lLLVMDlltoolDriver -lLLVMOption -lLLVMDebugInfoGSYM -lLLVMCoverage -lLLVMCoroutines -lLLVMipo -lLLVMInstrumentation -lLLVMVectorize -lLLVMLinker -lLLVMIRReader -lLLVMAsmParser -lLLVMX86Disassembler -lLLVMX86AsmParser -lLLVMX86CodeGen -lLLVMGlobalISel -lLLVMSelectionDAG -lLLVMAsmPrinter -lLLVMDebugInfoDWARF -lLLVMCodeGen -lLLVMTarget -lLLVMScalarOpts -lLLVMInstCombine -lLLVMAggressiveInstCombine -lLLVMTransformUtils -lLLVMBitWriter -lLLVMAnalysis -lLLVMProfileData -lLLVMX86Desc -lLLVMObject -lLLVMMCParser -lLLVMBitReader -lLLVMCore -lLLVMRemarks -lLLVMBitstreamReader -lLLVMMCDisassembler -lLLVMMC -lLLVMDebugInfoCodeView -lLLVMDebugInfoMSF -lLLVMBinaryFormat -lLLVMX86Utils -lLLVMX86Info -lLLVMSupport -lLLVMDemangle
        -lpthread
        lex
        )