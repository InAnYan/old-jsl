//
// Created by rusla on 12/18/2023.
//

#ifndef BINARYEXPR_HPP
#define BINARYEXPR_HPP
#include <memory>
#include <JSLLib/Syntax/AST/Exprs/BinaryOperation.hpp>

#include "JSLLib/Syntax/AST/AstNode.hpp"

namespace JSL
{
    class Expr;

    class BinaryExpr final : public ASTNode
    {
    public:
        BinaryExpr(const SourcePosition& pos, std::unique_ptr<Expr> left, const BinaryOperation op,
                   std::unique_ptr<Expr> right)
            : ASTNode(pos), left(std::move(left)), op(op), right(std::move(right))
        {
        }

        std::unique_ptr<Expr> left;
        BinaryOperation       op;
        std::unique_ptr<Expr> right;
    };
} // JSL

#endif //BINARYEXPR_HPP
