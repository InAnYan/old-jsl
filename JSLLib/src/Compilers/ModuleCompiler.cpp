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
        for (auto&& stmt : ast.stmts)
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
        std::visit(stmt, [this](const auto& arg) { Compile(arg); });
    }

    void ModuleCompiler::Compile(const PrintStmt& stmt)
    {
    }

    void ModuleCompiler::Compile(const ExprStmt& stmt)
    {
    }
}
