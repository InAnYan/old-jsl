//
// Created by rusla on 19.12.2023.
//

#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <variant>
#include <iostream>
#include <vector>

#include <JSLLib/Bytecode/Instructions.hpp>
#include <JSLLib/Bytecode/UnknownInst.hpp>

namespace JSL
{
    using InstructionVariant = std::variant<
        #define JSL_INSTRUCTION_VARIANT(name, type) \
            name##Inst,

        JSL_INSTRUCTION_LIST(JSL_INSTRUCTION_VARIANT)
        UnknownInst

        #undef JSL_INSTRUCTION_VARIANT
    >;

    class Instruction : public InstructionVariant
    {
    public:
        using InstructionVariant::InstructionVariant;

        void Write(std::vector<uint8_t>& array);
        std::size_t Size();
    };
}

#endif //INSTRUCTION_HPP
