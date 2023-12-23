//
// Created by rusla on 18.12.2023.
//

#ifndef MODULECOMPILER_HPP
#define MODULECOMPILER_HPP
#include <JSLLib/Bytecode/Instruction.hpp>
#include <JSLLib/Runtime/Objects/Module.hpp>
#include <JSLLib/Syntax/ErrorListener.hpp>
#include <JSLLib/Syntax/AST/ModuleAST.hpp>
#include <JSLLib/VirtualMachine/VirtualMachine.hpp>

namespace JSL
{
    class ModuleCompiler final
    {
    public:
        ModuleCompiler(VirtualMachine& vm, ModuleAST& ast, ErrorListener& errorListener);

        GcPtr<Module> Compile();

    private:
        VirtualMachine& vm;
        ModuleAST& ast;
        ErrorListener& errorListener;

        GcPtr<Module> module;

        bool hadError = false;

        void ErrorAt(const SourcePosition& pos, std::string_view msg);

        void CompileStmt(const Stmt& stmt);
        void Compile(const PrintStmt& stmt);
        void Compile(const ExprStmt& stmt);

        void CompileExpr(const Expr& expr);
        void Compile(const BinaryExpr& expr);
        void Compile(const UnaryExpr& expr);
        void Compile(const IntegerLiteralExpr& expr);

        void CompileLogicalAnd(const Expr& left, const Expr& right);
        void CompileLogicalOr(const Expr& left, const Expr& right);
        void CompileBasicBinOp(const BinaryExpr& expr);

        void Emit(Instruction inst, const SourcePosition& pos);
        std::size_t AddConstant(Value value, const SourcePosition& pos);

        Chunk& GetChunk();
    };
} // JSL

#endif //MODULECOMPILER_HPP
