//
// Created by rusla on 12/18/2023.
//

#ifndef COMPILER_HPP
#define COMPILER_HPP
#include "AST/ModuleAST.hpp"
#include "JSLLib/Runtime/GcPtr.hpp"
#include "JSLLib/Runtime/Objects/Module.hpp"

namespace JSL {
    class Compiler final {
    public:
        GcPtr<Module> CompileModule(ModuleAST& ast);
    };
} // JSL

#endif //COMPILER_HPP
