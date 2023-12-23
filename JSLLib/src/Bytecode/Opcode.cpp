#include <JSLLib/Bytecode/Opcode.hpp>

namespace JSL
{
    std::ostream& operator<<(std::ostream& out, Opcode opcode)
    {
        switch (opcode)
        {
            #define JSL_OPCODE_PRINT(name, type) \
                case Opcode##name: out << #name; break;

            JSL_INSTRUCTION_LIST(JSL_OPCODE_PRINT)

            #undef JSL_OPCODE_PRINT
        }

        return out;
    }
}