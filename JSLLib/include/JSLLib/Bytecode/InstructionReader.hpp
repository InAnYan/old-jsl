#ifndef INSTRUCTIONREADER_HPP
#define INSTRUCTIONREADER_HPP
#include <JSLLib/Bytecode/Chunk.hpp>

namespace JSL
{
    using ReadResult = std::pair<Instruction, Chunk::CodeIterator>;

    ReadResult ReadInstruction(const Chunk& chunk, Chunk::CodeIterator it);
    ReadResult ReadInstructionSafe(const Chunk& chunk, Chunk::CodeIterator it);
}

#endif //INSTRUCTIONREADER_HPP
