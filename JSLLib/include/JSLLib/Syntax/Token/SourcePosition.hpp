//
// Created by rusla on 12/18/2023.
//

#ifndef SOURCEPOSITION_HPP
#define SOURCEPOSITION_HPP

#include <string_view>

#include <JSLLib/Runtime/Objects/String.hpp>

namespace JSL
{
    class SourcePosition final
    {
    public:
        SourcePosition()
            : fileName(), line()
        {
        }

        SourcePosition(GcPtr<const String> fileName, unsigned line)
            : fileName(fileName),
              line(line)
        {
        }

        [[nodiscard]] GcPtr<const String> GetFileName() const
        {
            return fileName;
        }

        [[nodiscard]] unsigned GetLine() const
        {
            return line;
        }

    private:
        GcPtr<const String> fileName;
        unsigned            line;
    };
} // JSL

#endif //SOURCEPOSITION_HPP
