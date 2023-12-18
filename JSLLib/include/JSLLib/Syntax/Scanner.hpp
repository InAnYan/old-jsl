//
// Created by rusla on 12/18/2023.
//

#ifndef SCANNER_HPP
#define SCANNER_HPP
#include <string>

#include "Token/Token.hpp"

namespace JSL {

class Scanner final {
public:
    Scanner(std::string::iterator start, std::string::iterator current);

    Token Next();

private:
    std::string::iterator start;
    std::string::iterator current;
    std::string::iterator end;
};

} // JSL

#endif //SCANNER_HPP
