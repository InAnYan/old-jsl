cmake_minimum_required(VERSION 3.22)
project(JSLLib)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-gdwarf-4)

add_library(JSLLib
        include/JSLLib/Header.hpp
        src/Header.cpp
        include/JSLLib/Bytecode/Chunk.hpp
        include/JSLLib/Bytecode/LinesTable.hpp
        include/JSLLib/Runtime/Value.hpp
        include/JSLLib/Runtime/ManagedObject.hpp
        include/JSLLib/Runtime/Objects/Function.hpp
        include/JSLLib/Runtime/Objects/Module.hpp
        include/JSLLib/Runtime/Objects/JsObject.hpp
        include/JSLLib/Runtime/Objects/String.hpp
        include/JSLLib/VirtualMachine/VirtualMachine.hpp
        include/JSLLib/VirtualMachine/VirtualMachineConfiguration.hpp
        include/JSLLib/VirtualMachine/Stack.hpp
        include/JSLLib/VirtualMachine/CallFrame.hpp
        include/JSLLib/VirtualMachine/Exceptions/RuntimeError.hpp
        include/JSLLib/Runtime/ValueType.hpp
        include/JSLLib/Runtime/ManagedObjectType.hpp
        include/JSLLib/Bytecode/InstructionTypes/InstructionBase.hpp
        include/JSLLib/Bytecode/InstructionTypes/SimpleInstruction.hpp
        include/JSLLib/Bytecode/InstructionTypes/ConstantInstruction.hpp
        include/JSLLib/Syntax/AST/Exprs/BinaryOperation.hpp
        include/JSLLib/Syntax/AST/Stmt.hpp
        include/JSLLib/Syntax/AST/Expr.hpp
        include/JSLLib/Syntax/AST/ModuleAST.hpp
        include/JSLLib/Syntax/AST/Exprs/IntegerLiteralExpr.hpp
        include/JSLLib/Syntax/AST/Exprs/BinaryExpr.hpp
        include/JSLLib/Syntax/AST/Stmts/ExprStmt.hpp
        include/JSLLib/Syntax/AST/Stmts/PrintStmt.hpp
        include/JSLLib/Syntax/AST/AstNode.hpp
        include/JSLLib/Syntax/Token/SourcePosition.hpp
        include/JSLLib/Syntax/Scanner.hpp
        include/JSLLib/Syntax/Token/Token.hpp
        include/JSLLib/Syntax/Token/TokenType.hpp
        include/JSLLib/Syntax/ErrorListener.hpp
        include/JSLLib/Syntax/Parser.hpp
        include/JSLLib/Runtime/GcPtr.hpp
        include/JSLLib/Runtime/MemoryManager.hpp
        include/JSLLib/Runtime/RootsSource.hpp
        include/JSLLib/Util/Assert.hpp
        src/Syntax/Scanner.cpp
        src/Syntax/Parser.cpp
        include/JSLLib/Syntax/AST/Exprs/UnaryOperation.hpp
        include/JSLLib/Syntax/AST/Exprs/UnaryExpr.hpp
        include/JSLLib/Syntax/Compilers/ModuleCompiler.hpp
        src/Compilers/ModuleCompiler.cpp
        include/JSLLib/Bytecode/Instruction.hpp
        include/JSLLib/Bytecode/InstructionList.hpp
        include/JSLLib/Bytecode/Opcode.hpp
        include/JSLLib/Bytecode/UnknownInst.hpp
        include/JSLLib/Bytecode/Instructions.hpp
)
target_include_directories(JSLLib PRIVATE include)
set_target_properties(JSLLib PROPERTIES LINKER_LANGUAGE CXX)

