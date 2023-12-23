//
// Created by rusla on 12/18/2023.
//

#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <vector>

#include <JSLLib/Bytecode/Instruction.hpp>
#include <JSLLib/Bytecode/LinesTable.hpp>
#include <JSLLib/Runtime/Value.hpp>
#include <JSLLib/Syntax/Token/SourcePosition.hpp>

namespace JSL
{
    class Chunk
    {
    public:
        using Code = std::vector<uint8_t>;
        using CodeIterator = Code::const_iterator;

        std::size_t PushInstruction(Instruction inst, std::optional<SourcePosition> pos = std::nullopt);
        std::size_t PushConstant(Value val, std::optional<SourcePosition> pos = std::nullopt);

        [[nodiscard]] std::optional<std::size_t> GetCodeLine(std::size_t index) const
        {
            return codeLines.GetLine(index);
        }

        [[nodiscard]] std::optional<std::size_t> GetConstantsLine(std::size_t index) const
        {
            return constantsLines.GetLine(index);
        }

        [[nodiscard]] const Code& GetCode() const
        {
            return code;
        }

        [[nodiscard]] const std::vector<Value>& GetConstants() const
        {
            return constants;
        }

        [[nodiscard]] Code& GetCode()
        {
            return code;
        }

        [[nodiscard]] std::vector<Value>& GetConstants()
        {
            return constants;
        }

    private:
        Code code;
        LinesTable codeLines;

        std::vector<Value> constants;
        LinesTable constantsLines;
    };
} // JSL

#endif //CHUNK_HPP
