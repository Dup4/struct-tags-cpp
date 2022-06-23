#ifndef STRUCT_TAGS_INTERNAL_STRUCT_TAGS_H
#define STRUCT_TAGS_INTERNAL_STRUCT_TAGS_H

#include <cstddef>
#include <tuple>
#include <type_traits>

#include "../types_check/index.h"
#include "./options.h"

namespace struct_tags {

template <typename T>
class StructTags {
public:
    StructTags() = delete;
    StructTags(T* value) : value_(value) {}

    StructTags(const StructTags&) = default;
    StructTags(StructTags&&) = default;
    StructTags& operator=(const StructTags&) = default;
    StructTags& operator=(StructTags&&) = default;

    T& Interface() {
        return *value_;
    }

    size_t NumField() {
        static auto options = ::struct_tags::OptionsBuilder().WithVisitField().Build();
        return entrance(options, []([[maybe_unused]] auto&& field) {});
    }

    template <typename Func>
    void FieldByIndex(size_t ix, Func&& f) {
        static auto options = ::struct_tags::OptionsBuilder().WithVisitField().WithVisitByIndex().WithIndex(ix).Build();
        entrance(options, std::forward<Func>(f));
    }

    template <typename Func>
    void FieldByName(const char* name, Func&& f) {
        static auto options = ::struct_tags::OptionsBuilder().WithVisitField().WithVisitByName().WithName(name).Build();
        entrance(options, std::forward<Func>(f));
    }

    template <typename Func>
    void FieldForEach(Func&& f) {
        static auto options = ::struct_tags::OptionsBuilder().WithVisitField().WithVisitForEach().Build();
        entrance(options, std::forward<Func>(f));
    }

private:
    template <typename Func>
    size_t entrance(const Options& options, Func&& func) {
        if constexpr (has_struct_tags_entrance_v<T>) {
            return T::__StructTags_Entrance(value_, options, std::forward<Func>(func));
        } else if constexpr (has_struct_tags_external_entrance_v<T>) {
            return __StructTagsExternal_Entrance(value_, options, std::forward<Func>(func));
        } else {
            static_assert(false_v<T>,
                    "T does not have T::__StructTags_Entrance() member function or __StructTagsExternal_Entrance() external function");
        }
    }

    T* value_;
};

template <typename T>
inline constexpr auto NewStructTags(T* value) {
    return StructTags<T>(value);
}

}  // namespace struct_tags

#endif  // STRUCT_TAGS_INTERNAL_STRUCT_TAGS_H
