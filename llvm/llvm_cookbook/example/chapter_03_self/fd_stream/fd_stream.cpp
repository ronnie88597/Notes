//
// Created by cmp on 2019/12/3.
//
#include "fd_stream.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "llvm/Support/raw_ostream.h"


FdStream::FdStream(const std::string &p) :
        _Path(p) {
    this->_Infd.open(this->_Path, std::ifstream::in);
    if (!this->_Infd.good()) {
        llvm::errs() << "Open " << this->_Path << " occured error! " << this->_Infd.rdstate() << "\n";
        llvm::errs().flush();
    }
}

T_TOKEN FdStream::getNextToken() {
    return 0;
}

void FdStream::nextToken() {
    while (true) {
        // whitespace:
        // 9 \t
        // 10 \n
        // 11 \v
        // 12 \f
        // 13 \r
        char c = this->_Infd.peek();
        if (9 <= c && c <= 13) { continue; }
        break;
    }
}
