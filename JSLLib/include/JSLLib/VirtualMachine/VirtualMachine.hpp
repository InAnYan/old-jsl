//
// Created by rusla on 12/18/2023.
//

#ifndef VIRTUALMACHINE_HPP
#define VIRTUALMACHINE_HPP

#include <JSLLib/Runtime/GcPtr.hpp>
#include <JSLLib/Runtime/MemoryManager.hpp>
#include <JSLLib/Runtime/Objects/JsObject.hpp>
#include <JSLLib/VirtualMachine/VirtualMachineConfiguration.hpp>

namespace JSL
{
    class VirtualMachine
    {
    public:
        explicit VirtualMachine(const VirtualMachineConfiguration& conf);

        template <typename T, typename... Args>
        GcPtr<T> AllocateObject(Args&& ... args)
        {
            return memory.AllocateObject<T>(std::forward<Args&&>(args)...);
        }

        GcPtr<JSObject> AllocateEmptyObject();

    private:
        VirtualMachineConfiguration conf;
        MemoryManager memory;
    };
} // JSL

#endif //VIRTUALMACHINE_HPP
