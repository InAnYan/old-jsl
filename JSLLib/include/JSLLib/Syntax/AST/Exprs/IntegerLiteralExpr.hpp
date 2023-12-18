//
// Created by rusla on 12/18/2023.
//

#ifndef INTEGERLITERAL_HPP
#define INTEGERLITERAL_HPP
#include "JSLLib/Syntax/AST/AstNode.hpp"

namespace JSL
{
    class IntegerLiteralExpr final : ASTNode
    {
    public:
        IntegerLiteralExpr(const SourcePosition& pos, const int number)
            : ASTNode(pos),
              number(number)
        {
        }

        int number;
    };
} // JSL

#endif //INTEGERLITERAL_HPP
