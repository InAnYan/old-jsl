//
// Created by rusla on 19.12.2023.
//

#ifndef OPCODE_HPP
#define OPCODE_HPP

#include <cstdint>
#include <iostream>

#include "InstructionList.hpp"

namespace JSL
{
    enum Opcode : uint8_t
    {
        #define JSL_INSTRUCTION_OPCODE(name, type) \
            Opcode##name,

        JSL_INSTRUCTION_LIST(JSL_INSTRUCTION_OPCODE)

        #undef JSL_INSTRUCTION_OPCODE
    };

    std::ostream& operator<<(std::ostream& out, Opcode opcode);
}

#endif //OPCODE_HPP
