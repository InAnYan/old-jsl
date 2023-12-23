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

        return hadError ? nullptr : module;
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

        Instruction inst = UnknownInst(static_cast<Opcode>(255));

        switch (expr.op)
        {
        case UnaryOperation::Negate:
            inst = NegateInst();
            break;
        case UnaryOperation::Not:
            inst = NotInst();
            break;
        }

        Emit(inst, expr.GetPosition());
    }

    void ModuleCompiler::Compile(const IntegerLiteralExpr& expr)
    {
        std::size_t index = AddConstant(Value(expr.number), expr.GetPosition());

        if (index < 256)
        {
            Emit(PushConstantInst(index), expr.GetPosition());
        }
    }

    void ModuleCompiler::CompileLogicalAnd(const Expr& left, const Expr& right)
    {
        throw std::logic_error("unimplemented logical and");
    }

    void ModuleCompiler::CompileLogicalOr(const Expr& left, const Expr& right)
    {
        throw std::logic_error("unimplemented logical and");
    }

    void ModuleCompiler::CompileBasicBinOp(const BinaryExpr& expr)
    {
        Instruction inst = UnknownInst(static_cast<Opcode>(255));

        switch (expr.op)
        {
        case BinaryOperation::Add:
            inst = AddInst();
            break;
        case BinaryOperation::Subtract:
            inst = SubtractInst();
            break;
        case BinaryOperation::Multiply:
            inst = MultiplyInst();
            break;
        case BinaryOperation::Divide:
            inst = DivideInst();
            break;
        case BinaryOperation::Equal:
        case BinaryOperation::NotEqual:
            inst = EqualInst();
            break;
        case BinaryOperation::Less:
        case BinaryOperation::GreaterEqual:
            inst = LessInst();
            break;
        case BinaryOperation::Greater:
        case BinaryOperation::LessEqual:
            inst = GreaterInst();
            break;
        default:
            JSL_BUG("wrong operation passed to ModuleCompiler::CompileBasicBinOp");
            break;
        }

        Emit(inst, expr.GetPosition());

        switch (expr.op)
        {
        case BinaryOperation::NotEqual:
            Emit(NotInst(), expr.GetPosition());
            break;
        default:
            break;
        }
    }

    void ModuleCompiler::Emit(Instruction inst, const SourcePosition& pos)
    {
        GetChunk().PushInstruction(inst, pos);
    }

    std::size_t ModuleCompiler::AddConstant(Value value, const SourcePosition& pos)
    {
        std::size_t index = GetChunk().PushConstant(value, pos);

        if (index > 255)
        {
            ErrorAt(pos, "too many constants");
        }

        return index;
    }

    Chunk& ModuleCompiler::GetChunk()
    {
        return module->GetScript()->GetChunk();
    }
}
