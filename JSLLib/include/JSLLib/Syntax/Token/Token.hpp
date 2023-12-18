//
// Created by rusla on 12/18/2023.
//

#ifndef TOKEN_HPP
#define TOKEN_HPP
#include "SourcePosition.hpp"
#include "TokenType.hpp"

namespace JSL
{
    class Token final
    {
    public:
        Token()
            : type(TokenType::UnspecifiedType), pos(), str()
        {
        }

        Token(TokenType type, const SourcePosition& pos, std::string_view str)
            : type(type), pos(pos), str(str)
        {
        }

        [[nodiscard]] TokenType GetType() const
        {
            return type;
        }

        [[nodiscard]] std::string_view GetString() const
        {
            return str;
        }

        [[nodiscard]] SourcePosition GetPosition() const
        {
            return pos;
        }

    private:
        TokenType        type;
        SourcePosition   pos;
        std::string_view str;
    };
} // JSL

#endif //TOKEN_HPP
