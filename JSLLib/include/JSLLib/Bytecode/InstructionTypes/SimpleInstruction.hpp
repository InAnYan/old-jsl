//
// Created by rusla on 12/18/2023.
//

#ifndef SIMPLEINSTRUCTION_HPP
#define SIMPLEINSTRUCTION_HPP

#include <JSLLib/Bytecode/InstructionTypes/InstructionBase.hpp>
#include <JSLLib/Bytecode/Opcode.hpp>

namespace JSL
{
    class SimpleInstruction : public InstructionBase
    {
    public:
        explicit SimpleInstruction(Opcode opcode)
            : InstructionBase(opcode)
        {
        }
    };

    template <Opcode theOpcode>
    class SimpleInstructionTemplate : public SimpleInstruction
    {
    public:
        SimpleInstructionTemplate()
            : SimpleInstruction(theOpcode)
        {

        }
    };

    #define JSL_DEFINE_INSTRUCTION_Simple(name) \
        class name##Inst : public SimpleInstructionTemplate<name##Opcode> {}
} // JSL

#endif //SIMPLEINSTRUCTION_HPP
