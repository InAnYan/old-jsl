#include <JSLLib/Bytecode/Disassembler.hpp>
#include <JSLLib/Bytecode/InstructionReader.hpp>
#include <JSLLib/Runtime/PrintFlags.hpp>

namespace JSL
{
    void Disassembler::FullDump()
    {
        out << "Chunk disassembly: " << name << std::endl;
        out << "Path: " << path << std::endl;

        out << "OFFS LINE NAME        ARGS" << std::endl;
        out << "                          " << std::endl;

        for (auto it = chunk.GetCode().begin();
             it != chunk.GetCode().end();
             it = DissasembleInstruction(it));
    }

    Chunk::CodeIterator Disassembler::DissasembleInstruction(Chunk::CodeIterator it)
    {
        const std::size_t                offset = it - chunk.GetCode().begin();
        const std::optional<std::size_t> line   = chunk.GetCodeLine(offset);

        out << offset << " ";

        if (line)
        {
            out << *line;
        }

        out << " ";

        auto [inst, newIt] = ReadInstructionSafe(chunk, it);

        std::visit([this](const auto& real)
        {
            PrintInstruction(real);
        }, inst);

        out << std::endl;

        return newIt;
    }

    void Disassembler::PrintInstruction(const ConstantInstruction& inst) const
    {
        out << inst.GetOpcode() << " #" << static_cast<int>(inst.GetIndex()) << "  ";
        chunk.GetConstants()[inst.GetIndex()].Print(PrintFlags::Debug, out);
    }

    void Disassembler::PrintInstruction(const SimpleInstruction& inst) const
    {
        out << inst.GetOpcode();
    }
}
