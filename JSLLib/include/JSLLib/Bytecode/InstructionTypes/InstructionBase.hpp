//
// Created by rusla on 12/18/2023.
//

#ifndef INSTRUCTIONBASE_HPP
#define INSTRUCTIONBASE_HPP
#include <JSLLib/Bytecode/Opcode.hpp>

namespace JSL
{
    class InstructionBase
    {
    public:
        InstructionBase(Opcode opcode)
            : opcode(opcode)
        {
        }

        [[nodiscard]] Opcode GetOpcode() const
        {
            return opcode;
        }

    private:
        Opcode opcode;
    };
} // JSL

#endif //INSTRUCTIONBASE_HPP
