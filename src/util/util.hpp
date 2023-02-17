#ifndef APP_UTIL_H
#define APP_UTIL_H

#include <iostream>

namespace util {
    bool log(std::string_view msg);
    bool warning(std::string_view msg);
    bool readfile(std::string_view path, std::string &output);
}

#endif