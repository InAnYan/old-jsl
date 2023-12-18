//
// Created by rusla on 12/18/2023.
//

#ifndef JSOBJECT_HPP
#define JSOBJECT_HPP
#include "String.hpp"
#include "JSLLib/Runtime/ManagedObject.hpp"
#include "JSLLib/Runtime/Value.hpp"

namespace JSL {
    class JSObject final : ManagedObject {
    public:
        JSObject(GcPtr<ManagedObject> next)
            : ManagedObject(next, ManagedObjectType::JSObject), impl() {
        }

        std::optional<Value> GetInSelf(GcPtr<String> name);
        bool SetInSelf(GcPtr<String> name, Value val);

        static ManagedObjectType GetStaticType() {
            return ManagedObjectType::JSObject;
        }

    private:
        std::unordered_map<GcPtr<String>, Value> impl;

        void MarkChildren() override;
};

} // JSL

#endif //JSOBJECT_HPP
