//
// Created by rusla on 12/18/2023.
//

#ifndef FUNCTION_HPP
#define FUNCTION_HPP
#include "String.hpp"
#include "JSLLib/Bytecode/Chunk.hpp"
#include "JSLLib/Runtime/ManagedObject.hpp"

namespace JSL {
    class Module;

    class Function : ManagedObject {
    public:
        Function(GcPtr<ManagedObject> next, GcPtr<Module> module, GcPtr<String> name,
                         unsigned arity)
                    : ManagedObject(next, ManagedObjectType::Function),
                      module(module),
                      name(name),
                      arity(arity) {
        }

        [[nodiscard]] const Chunk& GetChunk() const {
            return chunk;
        }

        [[nodiscard]] Chunk& GetChunk() {
            return chunk;
        }

        [[nodiscard]] GcPtr<Module> GetModule() {
            return module;
        }

        [[nodiscard]] GcPtr<String> GetName() {
            return name;
        }

        [[nodiscard]] unsigned GetArity() const {
            return arity;
        }

        static ManagedObjectType GetStaticType() {
            return ManagedObjectType::Function;
        }

    private:
        Chunk chunk;
        GcPtr<Module> module;
        GcPtr<String> name;
        unsigned arity;
    };
} // JSL

#endif //FUNCTION_HPP
