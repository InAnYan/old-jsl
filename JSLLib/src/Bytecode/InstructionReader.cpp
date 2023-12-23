#include <JSLLib/Bytecode/InstructionReader.hpp>

#include <JSLLib/Bytecode/Opcode.hpp>

namespace JSL
{
    template<bool check>
    class Reader
    {
    public:
        Reader(const Chunk& chunk, Chunk::CodeIterator it)
            : chunk(chunk), it(it)
        {
        }

        Instruction ReadInstruction()
        {
            Opcode opcode = static_cast<Opcode>(ReadByte());

            switch (opcode)
            {
                #define JSL_READ_INSTRUCTION(name, type) \
                    case Opcode##name: return Read##type##Instruction<name##Inst>();

            JSL_INSTRUCTION_LIST(JSL_READ_INSTRUCTION);

                #undef JSL_READ_INSTRUCTION

            default:
                return UnknownInst(opcode);
            }
        }

        Chunk::CodeIterator GetIterator() const
        {
            return it;
        }

    private:
        const Chunk&        chunk;
        Chunk::CodeIterator it;

        template<typename T>
        Instruction ReadSimpleInstruction()
        {
            return T();
        }

        template<typename T>
        Instruction ReadConstantInstruction()
        {
            return T(ReadByte());
        }

        uint8_t ReadByte()
        {
            if (check)
            {
                if (it == chunk.GetCode().end())
                {
                    throw std::out_of_range("corrupted chunk of code");
                }
            }

            return *it++;
        }
    };

    template<bool check>
    ReadResult ReadInstructionImpl(const Chunk& chunk, Chunk::CodeIterator it)
    {
        Reader<check> reader(chunk, it);
        Instruction   inst = reader.ReadInstruction();
        return {inst, reader.GetIterator()};
    }

    ReadResult ReadInstruction(const Chunk& chunk, Chunk::CodeIterator it)
    {
        return ReadInstructionImpl<true>(chunk, it);
    }

    ReadResult ReadInstructionSafe(const Chunk& chunk, Chunk::CodeIterator it)
    {
        return ReadInstructionImpl<true>(chunk, it);
    }
}
