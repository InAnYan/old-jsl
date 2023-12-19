//
// Created by rusla on 12/18/2023.
//

#ifndef PARSER_HPP
#define PARSER_HPP
#include "ErrorListener.hpp"
#include "Scanner.hpp"
#include "AST/ModuleAST.hpp"

namespace JSL {

class Parser final {
public:
    Parser(std::string::iterator start, std::string::iterator end, GcPtr<String> fileName, ErrorListener& errorListener);

    ModuleAST ParseModule();

    [[nodiscard]] bool HadError() const;

private:
    Scanner scanner;
    ErrorListener& errorListener;

    Token previous;
    Token next;

    bool hadError = false;

    std::vector<Stmt> ParseStmts();
    Stmt ParseStmt();

    PrintStmt ParsePrintStmt();
    ExprStmt ParseExprStmt();

    Expr ParseExpr();
    Expr ParseAssignment();
    Expr ParseEquality();
    Expr ParseLogicalAnd();
    Expr ParseLogicalOr();
    Expr ParseComparison();
    Expr ParseTerm();
    Expr ParseFactor();
    Expr ParseUnary();
    Expr ParsePrimary();

    using ParseFn = Expr (Parser::*)();

    template <ParseFn Fn, typename... TokenTypes>
    Expr ParseExprBinary(TokenTypes... types);

    static BinaryOperation TokenTypeToBinOp(TokenType type);

    template <typename T>
    T ParseNumber(std::string_view str);

    [[nodiscard]] bool IsAtEnd() const;

    void Advance();

    [[nodiscard]] bool CheckPrevious(TokenType type) const;
    [[nodiscard]] bool CheckNext(TokenType type) const;

    template <typename First>
    bool Match(First type);

    template <typename First, typename Second, typename... Rest>
    bool Match(First type1, Second type2, Rest... restTypes);

    Token Require(TokenType type, std::string_view errorMsg);

    void ErrorAtPrevious(std::string_view msg);
    void ErrorAtNext(std::string_view msg);
    void ErrorAt(SourcePosition pos, std::string_view msg);

    void Synchronize();
};

} // JSL

#endif //PARSER_HPP
