#ifndef STRUCT_TAGS_INTERNAL_STRUCT_TAGS_H
#define STRUCT_TAGS_INTERNAL_STRUCT_TAGS_H

#include <cstddef>
#include <tuple>
#include <type_traits>

#include "../types_check/index.h"
#include "./macros.h"
#include "./visit_tuple.h"

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

    constexpr size_t NumField() {
        auto field_tuple = getFieldTuple();
        return std::tuple_size_v<std::decay_t<decltype(field_tuple)>> - 1;
    }

    template <typename Func>
    constexpr void FieldByIndex(size_t ix, Func&& f) {
        auto field_tuple = getFieldTuple();
        ::struct_tags::VisitTupleByIndex(
                ix, std::forward<std::decay_t<decltype(field_tuple)>>(field_tuple), std::forward<Func>(f));
    }

    template <typename Func>
    constexpr void FieldByName(const char* name, Func&& f) {
        auto field_tuple = getFieldTuple();
        ::struct_tags::VisitTupleByName(
                name, std::forward<std::decay_t<decltype(field_tuple)>>(field_tuple), std::forward<Func>(f));
    }

    template <typename Func>
    constexpr void FieldForEach(Func&& f) {
        auto field_tuple = getFieldTuple();
        ::struct_tags::VisitTupleForEach(
                std::forward<std::decay_t<decltype(field_tuple)>>(field_tuple), std::forward<Func>(f));
    }

private:
    constexpr auto getFieldTuple() {
        if constexpr (has_struct_tags_field_tuple_v<T>) {
            return value_->__StructTags_FieldTuple();
        } else {
            auto field_tuple = __StructTagsExternal_FieldTuple(value_);
            static_assert(std::tuple_size_v<std::decay_t<decltype(field_tuple)>> != 0,
                    "T does not have __StructTags_FieldTuple() member function or __StructTagsExternal_FieldTuple() external function");

            return field_tuple;
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
