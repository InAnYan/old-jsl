#include <JSLLib/Bytecode/Chunk.hpp>

namespace JSL
{
    std::size_t Chunk::PushInstruction(Instruction inst, std::optional<SourcePosition> pos)
    {
        inst.Write(code);

        std::size_t index = code.size() - inst.Size();

        if (pos)
        {
            codeLines.PushLine(index, pos->GetLine());
        }

        return index;
    }

    std::size_t Chunk::PushConstant(Value val, std::optional<SourcePosition> pos)
    {
        constants.push_back(val);

        std::size_t index = constants.size() - 1;

        if (pos)
        {
            constantsLines.PushLine(index, pos->GetLine());
        }

        return index;
    }
}
