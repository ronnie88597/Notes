//
// Created by cmp on 2019/12/3.
//

#ifndef MAIN_FD_STREAM_H
#define MAIN_FD_STREAM_H

#include <string>
#include <fstream>

typedef int T_TOKEN;

enum {
    ID_TOKEN = 1001,
    NUM_TOKEN = 1002,

    DEF_TOKEN = 2001,
    IF_TOKEN = 2002,
    ELSE_TOKEN = 2003,
    ELIF_TOKEN = 2004,
    FOR_TOKEN = 2005,

    INT_TOKEN = 3001,
    FLOAT_TOKEN = 3002,
    STR_TOKEN = 3003,
};

class FdStream {
    enum {
        INVALIDFD = -1
    };
private:
    std::ifstream _Infd;
    std::string _Path;
public:
    FdStream(const std::string &p);

    T_TOKEN getNextToken();

protected:
    void nextToken();

protected:
};


#endif //MAIN_FD_STREAM_H
