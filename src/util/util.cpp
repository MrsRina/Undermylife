#include <fstream>
#include "util.hpp"

bool util::log(std::string_view msg) {
    std::string full_msg {"Log >> "};
    full_msg += msg;
    std::cout << full_msg << std::endl;
    return false;
}

bool util::warning(std::string_view msg) {
    std::string full_msg {"Warning >> "};
    full_msg += msg;
    std::cout << full_msg << std::endl;
    return true;
}

bool util::readfile(std::string_view path, std::string &output) {
    std::ifstream ifs {};
    ifs.open(path.data());
    output.clear();

    if (ifs.is_open()) {
        std::string buffer {};
        while (std::getline(ifs, buffer)) {
            output += buffer;
            output += '\n';
        }

        ifs.close();
    } else {
        std::string msg {"Failed to open file '"};
        msg += path;
        msg += "'!";
        return util::warning(msg);
    }

    return false;
}
