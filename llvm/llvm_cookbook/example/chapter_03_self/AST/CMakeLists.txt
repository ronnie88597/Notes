aux_source_directory(. src)
add_library(AST ${src})
target_include_directories(AST PUBLIC
        ${PROJECT_SOURCE_DIR}/include)

set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")