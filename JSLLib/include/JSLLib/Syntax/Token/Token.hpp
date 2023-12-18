//
// Created by rusla on 12/18/2023.
//

#ifndef TOKEN_HPP
#define TOKEN_HPP
#include "SourcePosition.hpp"
#include "TokenType.hpp"

namespace JSL {

class Token final {
public:
    Token()
        : type(TokenType::UNSET), str(), pos() {

    }

    Token(TokenType type, std::string_view str, const SourcePosition& pos)
        : type(type),
          str(str),
          pos(pos) {
    }

    [[nodiscard]] TokenType GetType() const {
        return type;
    }

    [[nodiscard]] std::string_view GetString() const {
        return str;
    }

    [[nodiscard]] SourcePosition GetPosition() const {
        return pos;
    }



private:
    TokenType type;
    std::string_view str;
    SourcePosition pos;
};

} // JSL

#endif //TOKEN_HPP
