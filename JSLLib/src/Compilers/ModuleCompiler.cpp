#include <JSLLib/Bytecode/Instructions.hpp>
#include <JSLLib/Syntax/Compilers/ModuleCompiler.hpp>

namespace JSL
{
    ModuleCompiler::ModuleCompiler(VirtualMachine& vm, ModuleAST& ast, ErrorListener& errorListener)
        : vm(vm), ast(ast), errorListener(errorListener),
          module(vm.AllocateObject<Module>(vm, ast.filePath))
    {
    }

    GcPtr<Module> ModuleCompiler::Compile()
    {
        for (auto&& stmt: ast.stmts)
        {
            CompileStmt(stmt);
        }

        if (!hadError)
        {
            return module;
        }
        else
        {
            return nullptr;
        }
    }

    void ModuleCompiler::ErrorAt(const SourcePosition& pos, std::string_view msg)
    {
        errorListener.Error(pos, msg);
        hadError = true;
    }

    void ModuleCompiler::CompileStmt(const Stmt& stmt)
    {
        std::visit([this](const auto& arg)
        {
            Compile(arg);
        }, stmt);
    }

    void ModuleCompiler::Compile(const PrintStmt& stmt)
    {
        CompileExpr(stmt.expr);
        Emit(PrintInst(), stmt.GetPosition());
    }

    void ModuleCompiler::Compile(const ExprStmt& stmt)
    {
        CompileExpr(stmt.expr);
        Emit(PopInst(), stmt.GetPosition());
    }

    void ModuleCompiler::CompileExpr(const Expr& expr)
    {
        std::visit([this](const auto& arg)
        {
            Compile(arg);
        }, expr);
    }

    void ModuleCompiler::Compile(const BinaryExpr& expr)
    {
        switch (expr.op)
        {
        case BinaryOperation::LogicalAnd:
            CompileLogicalAnd(*expr.left, *expr.right);
            break;

        case BinaryOperation::LogicalOr:
            CompileLogicalOr(*expr.left, *expr.right);
            break;

        default:
            CompileBasicBinOp(expr);
            break;
        }
    }

    void ModuleCompiler::Compile(const UnaryExpr& expr)
    {
        CompileExpr(*expr.expr);

        switch (expr.op)
        {
        case UnaryOperation::Negate:
            Emit(NegateInst(), expr.GetPosition());
            break;
        case UnaryOperation::Not:
            Emit(NotInst(), expr.GetPosition());
            break;
        }
    }

    void ModuleCompiler::Compile(const IntegerLiteralExpr& expr)
    {
        std::size_t index = AddConstant(Value(expr.number), expr.GetPosition());

        if (index < 256)
        {
            Emit(PushConstantInst(index), expr.GetPosition());
        }
    }
}
