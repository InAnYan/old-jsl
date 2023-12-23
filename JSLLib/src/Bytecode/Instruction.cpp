#include <JSLLib/Bytecode/Instruction.hpp>

namespace JSL
{
    void Instruction::Write(std::vector<uint8_t>& array)
    {
        std::visit([&array](const auto& real)
        {
            real.Write(array);
        }, *this);
    }

    std::size_t Instruction::Size()
    {
        return std::visit([](const auto& real)
        {
            return real.Size();
        }, *this);
    }
}
