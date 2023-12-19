//
// Created by rusla on 19.12.2023.
//

#ifndef OPCODE_HPP
#define OPCODE_HPP

#include <cstdint>

#include "InstructionList.hpp"

namespace JSL
{
    enum Opcode : uint8_t
    {
        #define JSL_INSTRUCTION_OPCODE(name, type) \
            name##Opcode,

        JSL_INSTRUCTION_LIST(JSL_INSTRUCTION_OPCODE)

        #undef JSL_INSTRUCTION_OPCODE
    };
}

#endif //OPCODE_HPP
