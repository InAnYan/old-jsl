//
// Created by rusla on 12/18/2023.
//

#ifndef SIMPLEINSTRUCTION_HPP
#define SIMPLEINSTRUCTION_HPP

#include <vector>
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

        void Write(std::vector<uint8_t>& array) const
        {
            array.push_back(GetOpcode());
        }

        [[nodiscard]] static std::size_t Size()
        {
            return 1;
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
        class name##Inst : public SimpleInstructionTemplate<Opcode##name> {}
} // JSL

#endif //SIMPLEINSTRUCTION_HPP
