//
// Created by rusla on 19.12.2023.
//

#ifndef UNKNOWNINST_HPP
#define UNKNOWNINST_HPP
#include <JSLLib/Bytecode/Opcode.hpp>

namespace JSL
{
    class SimpleInstruction;

    class UnknownInst : public SimpleInstruction
    {
    public:
        explicit UnknownInst(Opcode opcode)
            : SimpleInstruction(opcode)
        {

        }
    };
}
#endif //UNKNOWNINST_HPP
