//
// Created by rusla on 12/18/2023.
//

#ifndef SOURCEPOSITION_HPP
#define SOURCEPOSITION_HPP
#include <string_view>

namespace JSL {

class SourcePosition final {
public:
    SourcePosition()
        : fileName(), line() {
    }

    SourcePosition(const std::string_view& fileName, unsigned line)
        : fileName(fileName),
          line(line) {
    }

    [[nodiscard]] std::string_view GetFileName() const {
        return fileName;
    }

    [[nodiscard]] unsigned GetLine() const {
        return line;
    }

private:
    std::string_view fileName;
    unsigned line;
};

} // JSL

#endif //SOURCEPOSITION_HPP
