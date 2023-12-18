//
// Created by rusla on 12/18/2023.
//

#ifndef TOKENTYPE_HPP
#define TOKENTYPE_HPP


namespace JSL {
    enum class TokenType {
        Unset = 0,
        EndOfFile,
        Error,

        Integer,
        LeftParent,
        RightParent,
        Semicolon,
        Print,
    };
}

#endif //TOKENTYPE_HPP
