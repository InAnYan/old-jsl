#ifndef MODULE_HPP
#define MODULE_HPP
#include <JSLLib/VirtualMachine/VirtualMachine.hpp>

#include "Function.hpp"
#include "JsObject.hpp"
#include "String.hpp"
#include "JSLLib/Runtime/ManagedObject.hpp"

namespace JSL
{
    class Module final : public ManagedObject
    {
    public:
        Module(GcPtr<ManagedObject> next, VirtualMachine& vm, GcPtr<String> filePath)
            : ManagedObject(next, ManagedObjectType::Module),
              vars(vm.AllocateEmptyObject()),
              exports(vm.AllocateEmptyObject()),
              script(vm.AllocateObject<Function>(GcPtr<Module>(this), filePath, filePath, 0))
        {
        }

        void Print(PrintFlags flags, std::ostream& out) override;

        [[nodiscard]] GcPtr<Function> GetScript()
        {
            return script;
        }

        bool                 SetVariable(GcPtr<String> name, Value value);
        std::optional<Value> GetVariable(GcPtr<String> name);

        void AddExport(GcPtr<String> name, Value value);

        static ManagedObjectType GetStaticType()
        {
            return ManagedObjectType::Module;
        }

    private:
        GcPtr<JSObject> vars;
        GcPtr<JSObject> exports;
        GcPtr<Function> script;

        void MarkChildren() override;
    };
} // JSL

#endif //MODULE_HPP
