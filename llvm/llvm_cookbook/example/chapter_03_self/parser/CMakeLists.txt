aux_source_directory(. src)
add_library(Parser ${src})
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
#file(COPY parser.h DESTINATION ${PROJECT_BINARY_DIR}/include)

target_include_directories(Parser PUBLIC
        ${PROJECT_SOURCE_DIR}/include)