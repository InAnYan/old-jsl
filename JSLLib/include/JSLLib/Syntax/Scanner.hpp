//
// Created by rusla on 12/18/2023.
//

#ifndef SCANNER_HPP
#define SCANNER_HPP
#include <functional>
#include <string>

#include "JSLLib/Runtime/Objects/String.hpp"
#include "Token/Token.hpp"

namespace JSL
{
    class Scanner final
    {
    public:
        Scanner(std::string::iterator start, std::string::iterator end, GcPtr<String> fileName);

        Token                       NextToken();
        [[nodiscard]] GcPtr<String> GetFileName();

    private:
        std::string::iterator start;
        std::string::iterator current;
        std::string::iterator inputEnd;

        GcPtr<String> fileName;
        unsigned      line = 1;

        void SkipWhitespace();
        void BeginNewToken();

        Token ReadNumber();
        Token ReadIdentifierOrKeyword();

        char Advance();
        void AdvanceWhile(const std::function<bool(char)>& predicate);

        bool Match(char ch);

        Token                        MakeToken(TokenType type);
        [[nodiscard]] Token          MakeErrorToken(std::string_view errorMsg) const;
        [[nodiscard]] SourcePosition MakeSourcePosition() const;

        [[nodiscard]] bool IsAtEnd() const;
        [[nodiscard]] char Peek(int offset = 0) const;

        [[nodiscard]] std::string_view MakeStr() const;
    };
} // JSL

#endif //SCANNER_HPP
