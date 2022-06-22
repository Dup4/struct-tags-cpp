#ifndef STRUCT_TAGS_INTERNAL_MACROS_H
#define STRUCT_TAGS_INTERNAL_MACROS_H

#include <utility>

#include "./constant.h"
#include "./field.h"
#include "./visit_tuple.h"

#define STRUCT_TAGS_STR(x) #x

#define STRUCT_TAGS_DECLARE_FIELD_BEGIN(Struct)                      \
private:                                                             \
    friend class ::struct_tags::StructTags<Struct>;                  \
    friend class ::struct_tags::has_struct_tags_field_tuple<Struct>; \
                                                                     \
    auto __StructTags_FieldTuple() {                                 \
        static auto tuple = std::make_tuple(

#define STRUCT_TAGS_DECLARE_FIELD(field, ...) \
    ::struct_tags::Field<decltype(field)>{    \
            STRUCT_TAGS_STR(field), &field, std::map<std::string, std::string>{__VA_ARGS__}},

#define STRUCT_TAGS_DECLARE_FIELD_END                                                            \
::struct_tags::Field<char> \
        {::struct_tags::Constant::kStructTagsEndFlag, nullptr});                                 \
                                                                                                 \
    return tuple;                                                                                \
    }                                                                                            \
                                                                                                 \
public:                                                                                          \
    constexpr size_t NumField() {                                                                \
        return std::tuple_size_v<decltype(__StructTags_FieldTuple())> - 1;                       \
    }                                                                                            \
                                                                                                 \
    template <typename Func>                                                                     \
    constexpr void FieldByIndex(size_t ix, Func&& f) {                                           \
        ::struct_tags::VisitTupleByIndex(ix, __StructTags_FieldTuple(), std::forward<Func>(f));  \
    }                                                                                            \
                                                                                                 \
    template <typename Func>                                                                     \
    constexpr void FieldByName(const char* name, Func&& f) {                                     \
        ::struct_tags::VisitTupleByName(name, __StructTags_FieldTuple(), std::forward<Func>(f)); \
    }                                                                                            \
                                                                                                 \
    template <typename Func>                                                                     \
    constexpr void FieldForEach(Func&& f) {                                                      \
        ::struct_tags::VisitTupleForEach(__StructTags_FieldTuple(), std::forward<Func>(f));      \
    }                                                                                            \
                                                                                                 \
private:

template <typename T>
inline auto __StructTagsExternal_FieldTuple([[maybe_unused]] T&& s) {
    return std::make_tuple();
}

#define STRUCT_TAGS_EXTERNAL_DECLARE_FIELD_BEGIN(Struct)     \
    /* NOLINTNEXTLINE(bugprone-macro-parentheses) */         \
    inline auto __StructTagsExternal_FieldTuple(Struct* s) { \
        using _Struct = Struct;                              \
        static auto tuple = std::make_tuple(

// https://stackoverflow.com/questions/2402579/function-pointer-to-member-function
#define STRUCT_TAGS_EXTERNAL_DECLARE_FIELD(field, ...)                   \
    ::struct_tags::Field<std::decay_t<decltype(s->*(&_Struct::field))>>{ \
            STRUCT_TAGS_STR(field), &(s->*(&_Struct::field)), std::map<std::string, std::string>{__VA_ARGS__}},

#define STRUCT_TAGS_EXTERNAL_DECLARE_FIELD_END               \
    ::struct_tags::Field<char> {                             \
        ::struct_tags::Constant::kStructTagsEndFlag, nullptr \
    });                                                      \
                                                             \
    return tuple;                                            \
    }

#endif  // STRUCT_TAGS_INTERNAL_MACROS_H
