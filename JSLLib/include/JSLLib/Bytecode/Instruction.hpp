//
// Created by rusla on 19.12.2023.
//

#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <variant>

#include <JSLLib/Bytecode/InstructionList.hpp>
#include <JSLLib/Bytecode/UnknownInst.hpp>

namespace JSL
{
    using Instruction = std::variant<
        #define JSL_INSTRUCTION_VARIANT(name, type) \
            name##Inst,

        JSL_INSTRUCTION_LIST(JSL_INSTRUCTION_VARIANT)
        UnknownInst

        #undef JSL_INSTRUCTION_VARIANT
    >;
}

#endif //INSTRUCTION_HPP
