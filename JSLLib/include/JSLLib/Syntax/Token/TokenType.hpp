//
// Created by rusla on 12/18/2023.
//

#ifndef TOKENTYPE_HPP
#define TOKENTYPE_HPP

#define JSL_TOKEN_TYPE_LIST(o)   \
    o(UnspecifiedType)           \
    o(EndOfFile)                 \
    o(Error)                     \
    o(Integer)                   \
    o(Semicolon)                 \
    o(Identifier)                \
    o(Print)                     \
    o(Plus)                      \
    o(Minus)                     \
    o(Star)                      \
    o(Slash)                     \
    o(LeftParen)                 \
    o(RightParen)                \
    o(True)                      \
    o(False)                     \
    o(Null)                      \
    o(Equal)                     \
    o(EqualEqual)                \
    o(Bang)                      \
    o(BangEqual)                 \
    o(Greater)                   \
    o(Less)                      \
    o(GreaterEqual)              \
    o(LessEqual)                 \
    o(Bar)                       \
    o(BarBar)                    \
    o(Ampersand)                 \
    o(AmpersandAmpersand)        \
    o(LeftBracket)               \
    o(RightBracket)              \
    o(If)                        \
    o(Else)                      \
    o(Var)

#define JSL_KEYWORDS_LIST(o)    \
    o(print, Print)             \
    o(true, True)               \
    o(false, False)             \
    o(null, Null)               \
    o(if, If)                   \
    o(else, Else)               \
    o(var, Var)

namespace JSL
{
    enum class TokenType
    {
        #define JSL_TOKEN_TYPE_ENUM(name) \
            name,

        JSL_TOKEN_TYPE_LIST(JSL_TOKEN_TYPE_ENUM)

        #undef JSL_TOKEN_TYPE_ENUM
    };
}

#endif //TOKENTYPE_HPP
