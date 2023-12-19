//
// Created by rusla on 12/18/2023.
//

#ifndef ASTNODE_HPP
#define ASTNODE_HPP
#include "JSLLib/Syntax/Token/SourcePosition.hpp"

namespace JSL
{
    class ASTNode
    {
    public:
        explicit ASTNode(const SourcePosition& pos)
            : pos(pos)
        {
        }

        virtual ~ASTNode() = default;

        [[nodiscard]] SourcePosition GetPosition() const
        {
            return pos;
        }

    private:
        SourcePosition pos;
    };
} // JSL

#endif //ASTNODE_HPP
