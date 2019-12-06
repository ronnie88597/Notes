//
// Created by cmp on 2019/12/4.
//

#include "gtest/gtest.h"

extern "C" {
#include "lex.yy.h"
}

bool isSame(Token t1, Token t2) {
    return t1.EToken == t2.EToken &&
           0 == strcmp(t1.text, t2.text);
}

TEST(Scanner, getToken) {
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{INT_TOKEN, "int"})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{FNUM_TOKEN, "3.14"})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{NUM_TOKEN, "123"})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{ID_TOKEN, "a123"})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{NUM_TOKEN, "123"})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{ID_TOKEN, "a"})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{ID_TOKEN, "a123a"})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{ADD_TOKEN, "+"})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{SUB_TOKEN, "-"})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{MUL_TOKEN, "*"})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{DIV_TOKEN, "/"})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{EQ_TOKEN, "="})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{ID_TOKEN, "_123"})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{ID_TOKEN, "_a123"})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{ID_TOKEN, "_a"})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{ID_TOKEN, "def1"})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{DEF_TOKEN, "def"})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{FOR_TOKEN, "for"})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{ID_TOKEN, "for1"})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{IF_TOKEN, "if"})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{ID_TOKEN, "if1"})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{ID_TOKEN, "ifelse"})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{ELSE_TOKEN, "else"})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{ELIF_TOKEN, "elif"})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{SEMICOLON_TOKEN, ";"})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{L_BRACE_TOKEN, "{"})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{R_BRACE_TOKEN, "}"})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{L_PARENTHSIS_TOKEN, "("})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{R_PARENTHSIS_TOKEN, ")"})
    );
    EXPECT_TRUE(
            isSame(getNextToken(),
                   Token{COMMA_TOKEN, ","})
    );
}


int main(int argc, char **argv) {
    initScanner(
            "/home/cmp/work_dir/Notes/llvm/llvm_cookbook/example/chapter_03_self/unittest/lexer_test/case01/data.txt");
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return 0;
}