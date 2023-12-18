//
// Created by rusla on 12/18/2023.
//

#ifndef PARSER_HPP
#define PARSER_HPP
#include "ErrorListener.hpp"
#include "Scanner.hpp"
#include "AST/ModuleAST.hpp"

namespace JSL {

class Parser final {
public:
    Parser(std::string::iterator start, std::string::iterator current, GcPtr<const String> fileName, ErrorListener& errorListener);

    ModuleAST ParseModule();

private:
    Scanner scanner;
    ErrorListener& errorListener;
};

} // JSL

#endif //PARSER_HPP
