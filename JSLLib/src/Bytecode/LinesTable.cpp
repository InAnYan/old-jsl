#include <JSLLib/Bytecode/LinesTable.hpp>

namespace JSL
{
    void LinesTable::PushLine(std::size_t index, std::size_t line)
    {
        impl[index] = line;
    }

    std::optional<std::size_t> LinesTable::GetLine(std::size_t index) const
    {
        auto it = impl.find(index);

        if( it != impl.end())
        {
            return it->second;
        }
        else
        {
            return std::nullopt;
        }
    }
}
