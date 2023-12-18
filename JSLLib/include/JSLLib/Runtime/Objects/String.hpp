//
// Created by rusla on 12/18/2023.
//

#ifndef STRING_HPP
#define STRING_HPP
#include "JSLLib/Runtime/ManagedObject.hpp"

namespace JSL {

class String final : ManagedObject {
public:
    String(GcPtr<ManagedObject> next, std::string&& impl)
        : ManagedObject(next, ManagedObjectType::String),
          impl(std::move(impl)), hash(std::hash<std::string>{}(impl)) {
    }

    [[nodiscard]] const std::string& GetCppString() const {
        return impl;
    }

    [[nodiscard]] std::size_t GetHash() const {
        return hash;
    }

    static ManagedObjectType GetStaticType() {
        return ManagedObjectType::String;
    }

private:
    std::string impl;
    std::size_t hash;

    void MarkChildren() override;
};

} // JSL

    template<>
    struct std::hash<JSL::GcPtr<JSL::String>> {
        std::size_t operator()(JSL::GcPtr<JSL::String> ptr) const noexcept {
            return ptr->GetHash();
        }
    };

#endif //STRING_HPP
