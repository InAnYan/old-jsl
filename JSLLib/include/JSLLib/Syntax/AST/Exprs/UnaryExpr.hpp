//
// Created by rusla on 18.12.2023.
//

#ifndef UNARYEXPR_HPP
#define UNARYEXPR_HPP
#include <memory>
#include <JSLLib/Syntax/AST/AstNode.hpp>
#include <JSLLib/Syntax/AST/Exprs/UnaryOperation.hpp>

namespace JSL
{
    class Expr;

    class UnaryExpr final : ASTNode
    {
    public:
        UnaryExpr(const SourcePosition& pos, UnaryOperation op, std::unique_ptr<Expr> expr)
            : ASTNode(pos), op(op), expr(std::move(expr))
        {
        }

    private:
        UnaryOperation        op;
        std::unique_ptr<Expr> expr;
    };
} // JSL

#endif //UNARYEXPR_HPP
