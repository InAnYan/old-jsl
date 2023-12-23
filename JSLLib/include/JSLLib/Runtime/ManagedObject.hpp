//
// Created by rusla on 12/18/2023.
//

#ifndef MANAGEDOBJECT_HPP
#define MANAGEDOBJECT_HPP

#include <type_traits>

#include <JSLLib/Runtime/ManagedObjectType.hpp>
#include <JSLLib/Runtime/PrintFlags.hpp>
#include <JSLLib/Runtime/GcPtr.hpp>

namespace JSL
{
    class ManagedObject
    {
    public:
        ManagedObject(GcPtr<ManagedObject> next, ManagedObjectType type);

        virtual ~ManagedObject() = default;

        virtual void Print(PrintFlags flags, std::ostream& out) = 0;

        template<typename T>
        static constexpr bool IsValidJslObject()
        {
            static_assert(std::is_base_of_v<ManagedObject, T> && "the type should inherit from Jsbi::Object");
            static_assert(std::is_same_v<decltype(T::GetStaticType()), ManagedObjectType>,
                          "the type should implement a static method Jsbi::ObjectType GetStaticType()");

            return true;
        }

        [[nodiscard]] ManagedObjectType GetType() const
        {
            return type;
        }

        [[nodiscard]] bool Is(ManagedObjectType otherType) const
        {
            return type == otherType;
        }

        template<typename T>
        [[nodiscard]] bool Is() const
        {
            static_assert(IsValidJslObject<T>() && "the type is not an Jsbi::Object");
            return Is(T::GetStaticType());
        }

        // As methods return GcPtr, which I don't really like. But it is simple and working properly.
        // Just, what if someone instantiates an Object not via MemoryManager?

        template<typename T>
        GcPtr<T> As()
        {
            static_assert(IsValidJslObject<T>() && "the type is not an Jsbi::Object");
            JSL_ASSERT(GetType() == T::GetStaticType(), "bad cast for Jsbi::Object");
            return GcPtr<T>(reinterpret_cast<T *>(this));
        }

        template<typename T>
        GcPtr<const T> As() const
        {
            static_assert(IsValidJslObject<T>() && "the type is not an Jsbi::Object");
            JSL_ASSERT(GetType() == T::GetStaticType(), "bad cast for Jsbi::Object");
            return GcPtr<const T>(reinterpret_cast<const T *>(this));
        }

        template<>
        GcPtr<ManagedObject> As<ManagedObject>()
        {
            return static_cast<GcPtr<ManagedObject>>(this);
        }

        template<>
        [[nodiscard]] GcPtr<const ManagedObject> As<ManagedObject>() const
        {
            return static_cast<GcPtr<const ManagedObject>>(this);
        }

        // Methods that are used by GC.

        GcPtr<ManagedObject> GetNext()
        {
            return next;
        }

        void Mark()
        {
            if (!marked)
            {
                marked = true;
                MarkChildren();
            }
        }

        void UnMark()
        {
            marked = false;
        }

    private:
        bool                 marked;
        GcPtr<ManagedObject> next;
        ManagedObjectType    type;

        virtual void MarkChildren() = 0;
    };
} // JSL

#endif //MANAGEDOBJECT_HPP
