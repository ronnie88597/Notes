add_executable(lexer_test main.cpp)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin_test)

target_include_directories(lexer_test PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ../../../../../../../source_code/googletest_build/include)

target_link_directories(lexer_test PUBLIC
        ${PROJECT_BINARY_DIR}/lib
        ../../../../../../../source_code/googletest_build/lib)

target_link_libraries(lexer_test PUBLIC
        -lLexer
        -lfl
        -lgtest
        -lpthread
        )