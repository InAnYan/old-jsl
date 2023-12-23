#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "String.hpp"
#include "JSLLib/Bytecode/Chunk.hpp"
#include "JSLLib/Runtime/ManagedObject.hpp"

namespace JSL
{
    class Module;

    class Function : public ManagedObject
    {
    public:
        Function(GcPtr<ManagedObject> next, GcPtr<Module> module, GcPtr<String> name, GcPtr<String> source,
                 unsigned             arity)
            : ManagedObject(next, ManagedObjectType::Function),
              module(module), name(name), source(source), arity(arity)
        {
        }

        void Print(PrintFlags flags, std::ostream& out) override;

        [[nodiscard]] const Chunk& GetChunk() const
        {
            return chunk;
        }

        [[nodiscard]] Chunk& GetChunk()
        {
            return chunk;
        }

        [[nodiscard]] GcPtr<Module> GetModule()
        {
            return module;
        }

        [[nodiscard]] GcPtr<String> GetName()
        {
            return name;
        }

        [[nodiscard]] unsigned GetArity() const
        {
            return arity;
        }

        static ManagedObjectType GetStaticType()
        {
            return ManagedObjectType::Function;
        }

    private:
        Chunk         chunk;
        GcPtr<Module> module;
        GcPtr<String> name;
        GcPtr<String> source;
        unsigned      arity;

        void MarkChildren() override;
    };
} // JSL

#endif //FUNCTION_HPP
