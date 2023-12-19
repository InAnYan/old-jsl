// ReSharper disable CppDFAArrayIndexOutOfBounds
#include <JSLLib/Syntax/Scanner.hpp>
#include <JSLLib/Util/Assert.hpp>

namespace JSL
{
    std::unordered_map<std::string_view, TokenType> keywordsMap =
    {
        #define JSL_KEYWORDS_MAP_FILL(str, name) \
                            { #str, TokenType::name },

        JSL_KEYWORDS_LIST(JSL_KEYWORDS_MAP_FILL)

        #undef JSL_KEYWORDS_MAP_FILL
    };

    TokenType IdentifierOrKeyword(std::string_view str)
    {
        auto it = keywordsMap.find(str);

        if (it != keywordsMap.end())
        {
            return it->second;
        }

        return TokenType::Identifier;
    }

    /// Fully inclusive range.
    bool CharInRange(char ch, char a, char b);

    bool IsDigit(char ch)
    {
        return CharInRange(ch, '0', '9');
    }

    bool IsAlpha(char ch)
    {
        return CharInRange(ch, 'a', 'z')
               || CharInRange(ch, 'A', 'Z');
    }

    bool CharInRange(char ch, char a, char b)
    {
        return ch >= a && ch <= b;
    }

    Scanner::Scanner(std::string::iterator start, std::string::iterator end, GcPtr<String> fileName)
        : start(start), current(start), inputEnd(end), fileName(fileName)
    {
    }

    Token Scanner::NextToken()
    {
        SkipWhitespace();
        BeginNewToken();

        if (IsAtEnd())
        {
            return MakeToken(TokenType::EndOfFile);
        }

        char ch = Advance();
        switch (ch)
        {
            case '+':
                return MakeToken(TokenType::Plus);
            case '-':
                return MakeToken(TokenType::Minus);
            case '*':
                return MakeToken(TokenType::Star);
            case '/':
                return MakeToken(TokenType::Slash);

            case '=':
                return MakeToken(Match('=') ? TokenType::EqualEqual : TokenType::Equal);
            case '!':
                return MakeToken(Match('=') ? TokenType::BangEqual : TokenType::Bang);

            case '>':
                return MakeToken(Match('=') ? TokenType::GreaterEqual : TokenType::Greater);
            case '<':
                return MakeToken(Match('=') ? TokenType::LessEqual : TokenType::Less);

            case '|':
                return MakeToken(Match('|') ? TokenType::BarBar : TokenType::Bar);
            case '&':
                return MakeToken(Match('&') ? TokenType::AmpersandAmpersand : TokenType::Ampersand);

            case '(':
                return MakeToken(TokenType::LeftParen);
            case ')':
                return MakeToken(TokenType::RightParen);
            case '{':
                return MakeToken(TokenType::LeftBracket);
            case '}':
                return MakeToken(TokenType::RightBracket);

            case ';':
                return MakeToken(TokenType::Semicolon);

            default:
                if (IsDigit(ch))
                {
                    return ReadNumber();
                }
                else if (IsAlpha(ch) || ch == '_')
                {
                    return ReadIdentifierOrKeyword();
                }
                else
                {
                    return MakeErrorToken("unknown character");
                }
        }
    }

    void Scanner::SkipWhitespace()
    {
        while (true)
        {
            switch (Peek())
            {
                case '\n':
                    line++;
                case ' ':
                case '\t':
                case '\r':
                    Advance();
                    continue;
                case '/':
                    if (Peek(1) == '/')
                    {
                        AdvanceWhile([](char ch)
                        {
                            return ch != '\n';
                        });
                        continue;
                    }
                    return;
                default:
                    return;
            }
        }
    }

    void Scanner::BeginNewToken()
    {
        start = current;
    }

    Token Scanner::ReadNumber()
    {
        AdvanceWhile(IsDigit);

        return MakeToken(TokenType::Integer);
    }

    Token Scanner::ReadIdentifierOrKeyword()
    {
        AdvanceWhile([](char ch)
        {
            return IsAlpha(ch) || IsDigit(ch) || ch == '_';
        });

        return MakeToken(IdentifierOrKeyword(MakeStr()));
    }

    char Scanner::Advance()
    {
        JSL_ASSERT(!IsAtEnd(), "attempt to advance while being at the end of the input");
        ++current;
        return current[-1];
    }

    void Scanner::AdvanceWhile(const std::function<bool(char)>& predicate)
    {
        while (!IsAtEnd() && predicate(Peek()))
        {
            Advance();
        }
    }

    Token Scanner::MakeToken(TokenType type)
    {
        return {type, MakeSourcePosition(), MakeStr()};
    }

    Token Scanner::MakeErrorToken(std::string_view errorMsg) const
    {
        return {TokenType::Error, MakeSourcePosition(), errorMsg};
    }

    bool Scanner::IsAtEnd() const
    {
        return current == inputEnd;
    }

    char Scanner::Peek(int offset) const
    {
        return current[offset];
    }

    std::string_view Scanner::MakeStr() const
    {
        return std::string_view(start.base(), current - start); // NOLINT(*-return-braced-init-list)
    }

    bool Scanner::Match(char ch)
    {
        if (Peek() != ch)
        {
            return false;
        }

        Advance();
        return true;
    }

    SourcePosition Scanner::MakeSourcePosition() const
    {
        return {fileName, line};
    }

    GcPtr<String> Scanner::GetFileName()
    {
        return fileName;
    }
}
