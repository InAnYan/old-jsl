//
// Created by rusla on 12/18/2023.
//

#ifndef INTEGERLITERAL_HPP
#define INTEGERLITERAL_HPP
#include "JSLLib/Syntax/AST/AstNode.hpp"

namespace JSL
{
    class IntegerLiteralExpr final : public ASTNode
    {
    public:
        IntegerLiteralExpr(const SourcePosition& pos, const Integer number)
            : ASTNode(pos), number(number)
        {
        }

        Integer number;
    };
} // JSL

#endif //INTEGERLITERAL_HPP
