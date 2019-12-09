execute_process(COMMAND
        flex ${PROJECT_SOURCE_DIR}/lexer/lexer.l
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/lexer)
add_library(Lexer lex.yy.c)
set(LIBRARY_OUTPUT_PATH  ${PROJECT_BINARY_DIR}/lib)


target_include_directories(Lexer PUBLIC
        ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(Lexer PUBLIC
        -lfl)



