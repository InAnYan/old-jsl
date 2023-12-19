//
// Created by rusla on 19.12.2023.
//

#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP

#include <JSLLib/Bytecode/InstructionTypes/ConstantInstruction.hpp>
#include <JSLLib/Bytecode/InstructionTypes/SimpleInstruction.hpp>

namespace JSL
{
    #define JSL_INSTRUCTION_DEFINE(name, type) \
        JSL_DEFINE_INSTRUCTION_##type(name);

    JSL_INSTRUCTION_LIST(JSL_INSTRUCTION_DEFINE)

    #undef JSL_INSTRUCTION_DEFINE
}

#endif //INSTRUCTIONS_HPP
