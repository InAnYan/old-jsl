//
// Created by rusla on 12/18/2023.
//

#ifndef CONSTANTINSTRUCTION_HPP
#define CONSTANTINSTRUCTION_HPP

#include <JSLLib/Bytecode/InstructionTypes/InstructionBase.hpp>
#include <JSLLib/Bytecode/Opcode.hpp>

namespace JSL
{
    class ConstantInstruction : public InstructionBase
    {
    public:
        ConstantInstruction(Opcode opcode, uint8_t index)
            : InstructionBase(opcode), index(index)
        {
        }

        [[nodiscard]] uint8_t GetIndex() const
        {
            return index;
        }

    private:
        uint8_t index;
    };
    
    template <Opcode theOpcode>
    class ConstantInstructionTemplate : public ConstantInstruction
    {
    public:
        explicit ConstantInstructionTemplate(uint8_t index)
            : ConstantInstruction(theOpcode, index)
        {

        }
    };

    #define JSL_DEFINE_INSTRUCTION_Constant(name) \
        class name##Inst : public ConstantInstructionTemplate<name##Opcode> \
        { using ConstantInstructionTemplate<name##Opcode>::ConstantInstructionTemplate; }
} // JSL

#endif //CONSTANTINSTRUCTION_HPP
