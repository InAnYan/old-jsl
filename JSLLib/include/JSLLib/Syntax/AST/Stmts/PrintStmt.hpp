//
// Created by rusla on 12/18/2023.
//

#ifndef PRINTSTMT_HPP
#define PRINTSTMT_HPP
#include "JSLLib/Syntax/AST/AstNode.hpp"
#include "JSLLib/Syntax/AST/Expr.hpp"

namespace JSL {

class PrintStmt final : public ASTNode{
public:
    PrintStmt(const SourcePosition& pos, Expr&& expr)
        : ASTNode(pos),
          expr(std::move(expr)) {
    }

    Expr expr;
};

} // JSL

#endif //PRINTSTMT_HPP
