#include <charconv>
#include <JSLLib/Runtime/ValueType.hpp>
#include <JSLLib/Syntax/Parser.hpp>
#include <JSLLib/Syntax/AST/Exprs/UnaryExpr.hpp>

namespace JSL
{
    class ParserException : std::exception
    {
    public:
        ParserException(const SourcePosition& pos, std::string_view msg)
            : pos(pos), msg(msg)
        {
        }

        [[nodiscard]] SourcePosition GetPos() const
        {
            return pos;
        }

        [[nodiscard]] std::string_view GetMsg() const
        {
            return msg;
        }

    private:
        SourcePosition   pos;
        std::string_view msg;
    };

    Parser::Parser(std::string::iterator start, std::string::iterator end, GcPtr<const String> fileName,
                   ErrorListener&        errorListener)
        : scanner(start, end, fileName), errorListener(errorListener)
    {
        Advance();
    }

    ModuleAST Parser::ParseModule()
    {
        return ModuleAST(ParseStmts());
    }

    bool Parser::HadError() const
    {
        return hadError;
    }

    std::vector<Stmt> Parser::ParseStmts()
    {
        std::vector<Stmt> stmts;

        while (!IsAtEnd())
        {
            try
            {
                stmts.push_back(ParseStmt());
            }
            catch (const ParserException& e)
            {
                Synchronize();
            }
        }

        return stmts;
    }

    Stmt Parser::ParseStmt()
    {
        if (Match(TokenType::Print))
        {
            return ParsePrintStmt();
        }
        else
        {
            return ParseExprStmt();
        }
    }

    PrintStmt Parser::ParsePrintStmt()
    {
        SourcePosition printPos = previous.GetPosition();
        Expr           expr     = ParseExpr();
        Require(TokenType::Semicolon, "expected ';' at the end of the print statement");
        return {printPos, std::move(expr)};
    }

    ExprStmt Parser::ParseExprStmt()
    {
        SourcePosition firstPos = previous.GetPosition();
        Expr           expr     = ParseExpr();
        Require(TokenType::Semicolon, "expected ';' at the end of the expression statement");
        return {firstPos, std::move(expr)};
    }

    Expr Parser::ParseExpr()
    {
        return ParseAssignment();
    }

    Expr Parser::ParseAssignment()
    {
        Expr expr = ParseEquality();

        if (Match(TokenType::Equal))
        {
            return BinaryExpr(previous.GetPosition(),
                              std::make_unique<Expr>(std::move(expr)),
                              TokenTypeToBinOp(previous.GetType()),
                              std::make_unique<Expr>(ParseAssignment()));
        }
        else
        {
            return expr;
        }
    }

    Expr Parser::ParseEquality()
    {
        return ParseExprBinary<&Parser::ParseLogicalAnd>(TokenType::Equal, TokenType::BangEqual);
    }

    Expr Parser::ParseLogicalAnd()
    {
        return ParseExprBinary<&Parser::ParseLogicalOr>(TokenType::AmpersandAmpersand);
    }

    Expr Parser::ParseLogicalOr()
    {
        return ParseExprBinary<&Parser::ParseComparison>(TokenType::BarBar);
    }

    Expr Parser::ParseComparison()
    {
        return ParseExprBinary<&Parser::ParseTerm>(TokenType::Greater, TokenType::GreaterEqual,
                                                   TokenType::Less, TokenType::LessEqual);
    }

    Expr Parser::ParseTerm()
    {
        return ParseExprBinary<&Parser::ParseFactor>(TokenType::Plus, TokenType::Minus);
    }

    Expr Parser::ParseFactor()
    {
        return ParseExprBinary<&Parser::ParseUnary>(TokenType::Star, TokenType::Slash);
    }

    Expr Parser::ParseUnary()
    {
        if (Match(TokenType::Plus))
        {
            return ParseUnary();
        }
        else if (Match(TokenType::Minus))
        {
            return UnaryExpr(previous.GetPosition(), UnaryOperation::Negate,
                             std::make_unique<Expr>(ParseUnary()));
        }
        else
        {
            return ParsePrimary();
        }
    }

    Expr Parser::ParsePrimary()
    {
        if (Match(TokenType::Integer))
        {
            return IntegerLiteralExpr(previous.GetPosition(), ParseNumber<int>(previous.GetString()));
        }
        else if (Match(TokenType::LeftParen))
        {
            Expr expr = ParseExpr();
            Require(TokenType::RightParen, "expected ')' after the grouping statement");
            return expr;
        }
        else
        {
            ErrorAtNext("expected an expression");
        }
    }

    BinaryOperation Parser::TokenTypeToBinOp(TokenType type)
    {
        switch (type)
        {
            case TokenType::Plus:
                return BinaryOperation::Add;
            case TokenType::Minus:
                return BinaryOperation::Subtract;
            case TokenType::Star:
                return BinaryOperation::Multiply;
            case TokenType::Slash:
                return BinaryOperation::Divide;
            case TokenType::EqualEqual:
                return BinaryOperation::Equal;
            case TokenType::BangEqual:
                return BinaryOperation::NotEqual;
            case TokenType::Greater:
                return BinaryOperation::Greater;
            case TokenType::Less:
                return BinaryOperation::Less;
            case TokenType::LessEqual:
                return BinaryOperation::LessEqual;
            case TokenType::GreaterEqual:
                return BinaryOperation::GreaterEqual;
            case TokenType::AmpersandAmpersand:
                return BinaryOperation::LogicalAnd;
            case TokenType::BarBar:
                return BinaryOperation::LogicalOr;
            default:
                JSL_BUG("unhandled token type to bin op type");
                return BinaryOperation::Add;
        }
    }

    template <typename T>
    T Parser::ParseNumber(std::string_view str)
    {
        T result;
        auto [ptr, ec] = std::from_chars(str.begin(), str.end(), result);

        if (ec == std::errc::invalid_argument)
        {
            JSL_BUG("JSL::Parser or JSL::Scanner does not recognise numbers correctly");
            return T{};
        }
        else if (ec == std::errc::result_out_of_range)
        {
            // TODO: More concise error.
            ErrorAtPrevious("number is out of range");
            return T{};
        }
        else
        {
            return result;
        }
    }

    template<Parser::ParseFn Fn, typename... TokenTypes>
    Expr Parser::ParseExprBinary(TokenTypes... types)
    {
        std::unique_ptr<Expr> left = std::make_unique<Expr>(std::invoke(Fn, *this));

        while (Match(types...))
        {
            Token op    = previous;
            Expr  right = std::invoke(Fn, *this);

            Expr res = BinaryExpr(op.GetPosition(),
                                  std::move(left),
                                  TokenTypeToBinOp(op.GetType()),
                                  std::make_unique<Expr>(std::move(right)));
            left = std::make_unique<Expr>(std::move(res));
        }

        return std::move(*left);
    }

    bool Parser::IsAtEnd() const
    {
        return CheckNext(TokenType::EndOfFile);
    }

    void Parser::Advance()
    {
        previous = next;

        while (true)
        {
            next = scanner.NextToken();

            if (next.GetType() == TokenType::Error)
            {
                // TODO: What is this?
                errorListener.Error(next.GetPosition(), next.GetString());
                hadError = true;
            }
            else
            {
                break;
            }
        }
    }

    bool Parser::CheckPrevious(TokenType type) const
    {
        return previous.GetType() == type;
    }

    bool Parser::CheckNext(TokenType type) const
    {
        return next.GetType() == type;
    }

    template <typename First>
    bool Parser::Match(First type)
    {
        if (next.GetType() != type)
        {
            return false;
        }

        Advance();
        return true;
    }

    template <typename First, typename Second, typename... Rest>
    bool Parser::Match(First type1, Second type2, Rest... restTypes)
    {
        return Match(type1) || Match(type2, restTypes...);
    }

    Token Parser::Require(TokenType type, std::string_view errorMsg)
    {
        if (Match(type))
        {
            return previous;
        }

        ErrorAtPrevious(errorMsg);
        return {}; // To suppress warning.
    }

    void Parser::ErrorAtPrevious(std::string_view msg)
    {
        ErrorAt(previous.GetPosition(), msg);
    }

    void Parser::ErrorAtNext(std::string_view msg)
    {
        ErrorAt(next.GetPosition(), msg);
    }

    void Parser::ErrorAt(SourcePosition pos, std::string_view msg)
    {
        errorListener.Error(pos, msg);
        hadError = true;
        throw ParserException(pos, msg);
    }

    void Parser::Synchronize()
    {
        Advance();

        while (!IsAtEnd())
        {
            if (previous.GetType() == TokenType::Semicolon)
            {
                break;
            }

            switch (next.GetType())
            {
                case TokenType::Print:
                    return;
                default:
                    Advance();
            }
        }
    }
}
