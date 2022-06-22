#ifndef STRUCT_TAGS_INTERNAL_STRUCT_TAGS_H
#define STRUCT_TAGS_INTERNAL_STRUCT_TAGS_H

#include <cstddef>
#include <tuple>

#include "../types_check/index.h"
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
        if constexpr (has_struct_tags_field_tuple_v<T>) {
            return std::tuple_size_v<decltype(value_->__StructTags_FieldTuple())> - 1;
        } else {
            static_assert(false_v<T>, "T does not have __StructTags_FieldTuple()");
        }
    }

    template <typename Func>
    constexpr void FieldByIndex(size_t ix, Func&& f) {
        if constexpr (has_struct_tags_field_tuple_v<T>) {
            ::struct_tags::VisitTupleByIndex(ix, value_->__StructTags_FieldTuple(), std::forward<Func>(f));
        } else {
            static_assert(false_v<T>, "T does not have __StructTags_FieldTuple()");
        }
    }

    template <typename Func>
    constexpr void FieldByName(const char* name, Func&& f) {
        if constexpr (has_struct_tags_field_tuple_v<T>) {
            ::struct_tags::VisitTupleByName(name, value_->__StructTags_FieldTuple(), std::forward<Func>(f));
        } else {
            static_assert(false_v<T>, "T does not have __StructTags_FieldTuple()");
        }
    }

    template <typename Func>
    constexpr void FieldForEach(Func&& f) {
        if constexpr (has_struct_tags_field_tuple_v<T>) {
            ::struct_tags::VisitTupleForEach(value_->__StructTags_FieldTuple(), std::forward<Func>(f));
        } else {
            static_assert(false_v<T>, "T does not have __StructTags_FieldTuple()");
        }
    }

private:
    T* value_;
};

template <typename T>
inline constexpr auto NewStructTags(T* value) {
    return StructTags<T>(value);
}

}  // namespace struct_tags

#endif  // STRUCT_TAGS_INTERNAL_STRUCT_TAGS_H
