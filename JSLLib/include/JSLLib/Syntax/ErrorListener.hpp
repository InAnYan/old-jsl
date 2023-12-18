//
// Created by rusla on 12/18/2023.
//

#ifndef ERRORLISTENER_HPP
#define ERRORLISTENER_HPP
#include "Token/SourcePosition.hpp"

namespace JSL {
    class ErrorListener {
    public:
        virtual ~ErrorListener() = default;

        virtual void Error(const SourcePosition& pos, std::string_view msg) = 0;
        virtual void Warning(const SourcePosition& pos, std::string_view msg) = 0;
    }; // JSL
}

#endif //ERRORLISTENER_HPP
