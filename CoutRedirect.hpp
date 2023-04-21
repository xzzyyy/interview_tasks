#ifndef COUTREDIRECT_HPP
#define COUTREDIRECT_HPP

#include <iostream>

struct CoutRedirect
{
    CoutRedirect(std::streambuf* new_buf)
        : old_buf(std::cout.rdbuf(new_buf))
    {
        // 
    }

    ~CoutRedirect()
    {
        std::cout.rdbuf(old_buf);
    }

private:
    std::streambuf* old_buf;
};

#endif
