cmake_minimum_required(VERSION 3.15)
project(main)

set(LLVM_INSTALL_DIR /home/cmp/work_dir/source_code/llvm-project_install)


add_subdirectory(lexer)
add_subdirectory(AST)
add_subdirectory(parser)

add_subdirectory(unittest)

aux_source_directory(${PROJECT_SOURCE_DIR} src)
add_executable(main ${src})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

target_include_directories(main PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${LLVM_INSTALL_DIR}/include
        )

MESSAGE("lib>>>>${PROJECT_BINARY_DIR}/lib")
target_link_directories(main PUBLIC
        ${PROJECT_BINARY_DIR}/lib
        ${LLVM_INSTALL_DIR}/lib
        )

target_link_libraries(main
        -lLLVMXRay -lLLVMWindowsManifest -lLLVMTextAPI -lLLVMTableGen -lLLVMSymbolize -lLLVMDebugInfoPDB -lLLVMPerfJITEvents -lLLVMOrcJIT -lLLVMJITLink -lLLVMOProfileJIT -lLLVMObjectYAML -lLLVMMIRParser -lLLVMMCA -lLLVMLTO -lLLVMPasses -lLLVMObjCARCOpts -lLLVMLineEditor -lLLVMLibDriver -lLLVMInterpreter -lLLVMIntelJITEvents -lLLVMFuzzMutate -lLLVMMCJIT -lLLVMExecutionEngine -lLLVMRuntimeDyld -lLLVMDlltoolDriver -lLLVMOption -lLLVMDebugInfoGSYM -lLLVMCoverage -lLLVMCoroutines -lLLVMipo -lLLVMInstrumentation -lLLVMVectorize -lLLVMLinker -lLLVMIRReader -lLLVMAsmParser -lLLVMX86Disassembler -lLLVMX86AsmParser -lLLVMX86CodeGen -lLLVMGlobalISel -lLLVMSelectionDAG -lLLVMAsmPrinter -lLLVMDebugInfoDWARF -lLLVMCodeGen -lLLVMTarget -lLLVMScalarOpts -lLLVMInstCombine -lLLVMAggressiveInstCombine -lLLVMTransformUtils -lLLVMBitWriter -lLLVMAnalysis -lLLVMProfileData -lLLVMX86Desc -lLLVMObject -lLLVMMCParser -lLLVMBitReader -lLLVMCore -lLLVMRemarks -lLLVMBitstreamReader -lLLVMMCDisassembler -lLLVMMC -lLLVMDebugInfoCodeView -lLLVMDebugInfoMSF -lLLVMBinaryFormat -lLLVMX86Utils -lLLVMX86Info -lLLVMSupport -lLLVMDemangle
        -lpthread
        -lParser
        -lAST
        -lLexer
        -lfl
        )