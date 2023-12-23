//
// Created by rusla on 12/18/2023.
//

#ifndef MEMORYMANAGER_HPP
#define MEMORYMANAGER_HPP
#include <string_view>

#include "GcPtr.hpp"
#include "ManagedObject.hpp"
#include "RootsSource.hpp"
#include "Value.hpp"

namespace JSL
{
    class MemoryManager final
    {
    public:
        MemoryManager() = default;
        explicit MemoryManager(RootsSource&& fn);

        ~MemoryManager();

        MemoryManager(const MemoryManager& other) = delete;
        MemoryManager(MemoryManager&& other)      = delete;

        MemoryManager& operator=(const MemoryManager& other) = delete;
        MemoryManager& operator=(MemoryManager&& other)      = delete;

        void OnGC();
        void OffGC();

        [[nodiscard]] bool IsGCOn() const;

        template<typename T, typename... Args>
        GcPtr<T> AllocateObject(Args&&... args)
        {
            GcPtr<T> obj(new T(objects, std::forward<Args &&>(args)...));

            LogObject("AllocateObject", obj);

            objects = obj;

            return obj;
        }

        void CollectGarbageIfNeeded();


        static void MarkObject(GcPtr<ManagedObject> obj);

        static void MarkValue(Value val);

    private:
        bool gcAllow = false;

        RootsSource roots = []()
        {
        };

        GcPtr<ManagedObject> objects = nullptr;

        void DeleteAllObjects();

        static void LogObject(std::string_view str, GcPtr<ManagedObject> obj);

        static void LogStages(std::string_view str);

        void DeleteObject(GcPtr<ManagedObject> obj);

        static std::ostream& Log(std::string_view str);
    };
}

#endif //MEMORYMANAGER_HPP
