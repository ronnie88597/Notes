cmake_minimum_required(VERSION 3.10)
project(main)

add_subdirectory(AST)
add_subdirectory(parser)
add_subdirectory(fd_stream)

aux_source_directory(${PROJECT_SOURCE_DIR} src)
add_executable(main ${src})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

target_include_directories(main PUBLIC
        ${PROJECT_BINARY_DIR}/include
        ../../../../../source_code/llvm-project_install/include/
        )


target_link_directories(main PUBLIC ${PROJECT_BINARY_DIR}/lib)
target_link_libraries(main
        AST
        Parser
        FdStream)