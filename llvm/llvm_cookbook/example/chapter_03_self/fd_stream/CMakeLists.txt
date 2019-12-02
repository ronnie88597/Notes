aux_source_directory(. src)
add_library(FdStream ${src})
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
#file(COPY fd_stream.h DESTINATION ${PROJECT_BINARY_DIR}/include)

target_include_directories(FdStream PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ../../../../../../source_code/llvm-project_install/include/
        )