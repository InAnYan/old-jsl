//
// Created by rusla on 12/18/2023.
//

#ifndef LINESTABLE_HPP
#define LINESTABLE_HPP

#include <map>
#include <optional>

namespace JSL
{
    class LinesTable
    {
    public:
        void PushLine(std::size_t index, std::size_t line);
        [[nodiscard]] std::optional<std::size_t> GetLine(std::size_t index) const;

    private:
        std::map<std::size_t, std::size_t> impl;
    };
}

#endif //LINESTABLE_HPP
