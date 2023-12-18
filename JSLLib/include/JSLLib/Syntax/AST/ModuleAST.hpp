//
// Created by rusla on 12/18/2023.
//

#ifndef MODULE_AST_HPP
#define MODULE_AST_HPP
#include <vector>

#include "Stmt.hpp"

namespace JSL {
    class ModuleAST final {
    public:
        explicit ModuleAST(std::vector<Stmt>&& stmts)
            : stmts(std::move(stmts)) {
        }

        std::vector<Stmt> stmts;
    };
} // JSL

#endif //MODULE_AST_HPP
