#ifndef DISASSEMBLER_HPP
#define DISASSEMBLER_HPP

#include <JSLLib/Bytecode/Chunk.hpp>

namespace JSL
{
    class Disassembler
    {
    public:
        Disassembler(const Chunk& chunk, std::string_view name, std::string_view path, std::ostream& out)
            : chunk(chunk),
              name(std::move(name)),
              path(std::move(path)),
              out(out)
        {
        }

        void FullDump();

        Chunk::CodeIterator DissasembleInstruction(Chunk::CodeIterator it);

    private:
        const Chunk&     chunk;
        std::string_view name;
        std::string_view path;
        std::ostream&    out;

        void PrintInstruction(const SimpleInstruction& inst) const;
        void PrintInstruction(const ConstantInstruction& inst) const;
    };
}

#endif //DISASSEMBLER_HPP
