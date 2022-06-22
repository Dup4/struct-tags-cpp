#ifndef STRUCT_TAGS_INTERNAL_MACROS_H
#define STRUCT_TAGS_INTERNAL_MACROS_H

#include "./constant.h"
#include "./field.h"
#include "./visit_tuple.h"

#define STRUCT_TAGS_STR(x) #x

#define STRUCT_TAGS_BEGIN         \
private:                          \
    auto structTagsFieldTuple() { \
        static auto tuple = std::make_tuple(

#define STRUCT_TAGS_DECLARE_FIELD(field, ...) \
    ::struct_tags::Field<decltype(field)>{    \
            STRUCT_TAGS_STR(field), &field, std::map<std::string, std::string>{__VA_ARGS__}},

#define STRUCT_TAGS_END                                                  \
::struct_tags::Field<char> \
        {::struct_tags::Constant::kStructTagsEndFlag, nullptr});         \
                                                                         \
    return tuple;                                                        \
    }                                                                    \
                                                                         \
public:                                                                  \
    constexpr size_t NumField() {                                        \
        return std::tuple_size_v<decltype(structTagsFieldTuple())> - 1;  \
    }                                                                    \
                                                                         \
    template <typename Func>                                             \
    void FieldByIndex(size_t ix, Func f) {                               \
        ::struct_tags::VisitTupleByIndex(ix, structTagsFieldTuple(), f); \
    }                                                                    \
                                                                         \
    auto FieldByName([[maybe_unused]] const std::string& name) {         \
        return 0;                                                        \
    }

#endif  // STRUCT_TAGS_INTERNAL_MACROS_H
