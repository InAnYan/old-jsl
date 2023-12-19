//
// Created by rusla on 12/18/2023.
//

#ifndef EXPRSTMT_HPP
#define EXPRSTMT_HPP
#include "JSLLib/Syntax/AST/AstNode.hpp"
#include "JSLLib/Syntax/AST/Expr.hpp"

namespace JSL {

class ExprStmt final : public ASTNode {
public:
    ExprStmt(const SourcePosition& pos, Expr&& expr)
        : ASTNode(pos),
          expr(std::move(expr)) {
    }

    Expr expr;
};

} // JSL

#endif //EXPRSTMT_HPP
