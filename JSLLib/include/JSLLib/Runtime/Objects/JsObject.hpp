//
// Created by rusla on 12/18/2023.
//

#ifndef JSOBJECT_HPP
#define JSOBJECT_HPP

#include <optional>
#include <unordered_map>

#include "String.hpp"
#include "JSLLib/Runtime/ManagedObject.hpp"
#include "JSLLib/Runtime/Value.hpp"

namespace JSL
{
    class JSObject final : ManagedObject
    {
    public:
        explicit JSObject(GcPtr<ManagedObject> next)
            : ManagedObject(next, ManagedObjectType::JSObject)
        {
        }

        void Print(PrintFlags flags, std::ostream& out) override;

        std::optional<Value> GetInSelf(GcPtr<String> name);
        bool                 SetInSelf(GcPtr<String> name, Value val);

        static ManagedObjectType GetStaticType()
        {
            return ManagedObjectType::JSObject;
        }

    private:
        std::unordered_map<GcPtr<String>, Value> impl;

        void MarkChildren() override;
    };
} // JSL

#endif //JSOBJECT_HPP
