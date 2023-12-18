//
// Created by rusla on 12/18/2023.
//

#ifndef VALUE_HPP
#define VALUE_HPP
#include "ValueType.hpp"

namespace JSL {

class Value {
public:
    template <typename T>
    explicit Value(T value)
        : type(TypeToValueType<T>()), as(value)
    {

    }

    template <typename T>
    T As() const
    {
        LOX_ASSERT(Is<T>(), "JSL::Value bad cast");
        return as.Get<T>();
    }

    [[nodiscard]] bool Is(ValueType type) const
    {
        return this->type == type;
    }

    template <typename T>
    [[nodiscard]] bool Is() const
    {
        return type == TypeToValueType<T>();
    }

    template <class Visitor>
    void Visit(Visitor&& visitor) const
    {
        switch (type)
        {
            case ValueType::Integer:       visitor(as.integer); break;
            case ValueType::ManagedObjectRef: visitor(as.object);  break;
        }
    }

    [[nodiscard]] ValueType GetType() const
    {
        return type;
    }

    bool operator==(const Value& value) const;

private:
    ValueType type;
    union As
    {
        explicit As(Integer val) : integer(val) {}
        explicit As(ManagedObjectRef val) : object(val) {}

        Integer integer;
        ManagedObjectRef object;

        template <typename T>
        T Get() const
        {
            JSL_ASSERT(false, "wrong Value::As get");
            return T();
        }

        template <>
        Integer Get<Integer>() const
        {
            return integer;
        }

        template <>
        ManagedObjectRef Get<ManagedObjectRef>() const
        {
            return object;
        }
    } as;
};

} // JSL

#endif //VALUE_HPP
