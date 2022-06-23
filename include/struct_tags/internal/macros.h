#ifndef STRUCT_TAGS_INTERNAL_MACROS_H
#define STRUCT_TAGS_INTERNAL_MACROS_H

#include <cstring>
#include <map>
#include <string>
#include <utility>

#include "./field.h"

#define STRUCT_TAGS_STR(x) #x

#define STRUCT_TAGS_DECLARE_BEGIN(Struct)                                                                \
private:                                                                                                 \
    friend class ::struct_tags::StructTags<Struct>;                                                      \
    friend class ::struct_tags::has_struct_tags_entrance<Struct>;                                        \
                                                                                                         \
    template <typename Func>                                                                             \
    static size_t __StructTags_Entrance(Struct* s, const ::struct_tags::Options& options, Func&& func) { \
        using _Struct = Struct;                                                                          \
        size_t size = 0;

// https://stackoverflow.com/questions/2402579/function-pointer-to-member-function
#define STRUCT_TAGS_DECLARE_FIELD(field, ...)                                                  \
    if (options.visit_field) {                                                                 \
        ++size;                                                                                \
                                                                                               \
        const char* name = STRUCT_TAGS_STR(field);                                             \
        static const auto tags = std::map<std::string, std::string>{__VA_ARGS__};              \
        using field_type = std::decay_t<decltype(s->*(&_Struct::field))>;                      \
        using field_struct_type = ::struct_tags::Field<field_type>;                            \
                                                                                               \
        if (options.visit_for_each || (options.visit_by_index && options.index == size - 1) || \
                (options.visit_by_name && !strcmp(options.name, name))) {                      \
            func(field_struct_type(name, &(s->field), tags));                                  \
        }                                                                                      \
    }

#define STRUCT_TAGS_DECLARE_END \
                                \
    return size;                \
    }

#define STRUCT_TAGS_EXTERNAL_DECLARE_BEGIN(Struct)                                                               \
    template <typename Func>                                                                                     \
    inline size_t __StructTagsExternal_Entrance(Struct* s, const ::struct_tags::Options& options, Func&& func) { \
        using _Struct = Struct;                                                                                  \
        size_t size = 0;

#define STRUCT_TAGS_EXTERNAL_DECLARE_FIELD(field, ...) STRUCT_TAGS_DECLARE_FIELD(field, ##__VA_ARGS__)

#define STRUCT_TAGS_EXTERNAL_DECLARE_END \
    return size;                         \
    }

#endif  // STRUCT_TAGS_INTERNAL_MACROS_H
