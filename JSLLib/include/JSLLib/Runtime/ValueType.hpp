//
// Created by rusla on 12/18/2023.
//

#ifndef VALUETYPE_HPP
#define VALUETYPE_HPP

#include "JSLLib/Util/Assert.hpp"

#define JSL_VALUE_TYPE_LIST(o)  \
    o(Integer, int) \
    o(ManagedObjectRef, JSL::GcPtr<JSL::ManagedObject>)

namespace JSL {
    enum class ValueType {
        #define JSL_VALUE_TYPE_ENUM(name, type)  \
        name,

        JSL_VALUE_TYPE_LIST(JSL_VALUE_TYPE_ENUM)

        #undef JSL_VALUE_TYPE_ENUM
    };

    std::ostream& operator<<(std::ostream& out, ValueType type);

    #define JSL_VALUE_TYPE_REPR(name, type)  \
        using name = type;

    JSL_VALUE_TYPE_LIST(JSL_VALUE_TYPE_REPR);

    #undef JSL_VALUE_TYPE_REPR

    template<typename T>
    inline ValueType TypeToValueType() {
        // TODO: Find a way to trigger a compiler error on this function call.
        JSL_BUG("wrong type passed to JSL::TypeToValueType");
        return ValueType::Integer;
    }

#define JSL_VALUE_TYPE_TYPE_TO_TYPE(name, type)  \
    template <>                                   \
    inline ValueType TypeToValueType<type>()      \
    {                                             \
    return ValueType::name;                   \
    }

    JSL_VALUE_TYPE_LIST(JSL_VALUE_TYPE_TYPE_TO_TYPE);

#undef JSL_VALUE_TYPE_TYPE_TO_TYPE
}

#endif //VALUETYPE_HPP
