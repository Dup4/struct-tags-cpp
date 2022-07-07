#ifndef STRUCT_TAGS_INTERNAL_MACROS_H
#define STRUCT_TAGS_INTERNAL_MACROS_H

#include <cstring>
#include <map>
#include <string>
#include <utility>

#include "./field.h"

#define STRUCT_TAGS_STR(x) #x

#define STRUCT_TAGS_DECLARE_BEGIN(Struct)                                                                  \
private:                                                                                                   \
    friend class ::struct_tags::StructTags<Struct>;                                                        \
    friend class ::struct_tags::has_struct_tags_entrance<Struct>;                                          \
    friend class ::struct_tags::StructTags<const Struct>;                                                  \
    friend class ::struct_tags::has_struct_tags_entrance<const Struct>;                                    \
                                                                                                           \
    template <typename T,                                                                                  \
              std::enable_if_t<std::is_same_v<Struct, T> || std::is_same_v<const Struct, T>, bool> = true, \
              typename Func>                                                                               \
    static size_t __StructTags_Entrance(T* s, const ::struct_tags::Options& options, Func&& func) {        \
        using _Struct = Struct;                                                                            \
        size_t size = 0;

// https://stackoverflow.com/questions/2402579/function-pointer-to-member-function
#define STRUCT_TAGS_DECLARE_FIELD(field, ...)                                                  \
    if (options.visit_field) {                                                                 \
        ++size;                                                                                \
                                                                                               \
        const char* name = STRUCT_TAGS_STR(field);                                             \
        static const auto tags = std::map<std::string, std::string>{__VA_ARGS__};              \
                                                                                               \
        if (options.visit_for_each || (options.visit_by_index && options.index == size - 1) || \
            (options.visit_by_name && !strcmp(options.name, name))) {                          \
            if constexpr (std::is_same_v<const _Struct, T>) {                                  \
                using field_type = const std::decay_t<decltype((s->field))>;                   \
                using field_struct_type = ::struct_tags::Field<field_type>;                    \
                                                                                               \
                func(field_struct_type(name, &(s->field), tags));                              \
            } else {                                                                           \
                using field_type = std::decay_t<decltype((s->field))>;                         \
                using field_struct_type = ::struct_tags::Field<field_type>;                    \
                                                                                               \
                func(field_struct_type(name, &(s->field), tags));                              \
            }                                                                                  \
        }                                                                                      \
    }

#define STRUCT_TAGS_DECLARE_END \
                                \
    return size;                \
    }

#define STRUCT_TAGS_EXTERNAL_DECLARE_BEGIN(Struct)                                                          \
    template <typename T,                                                                                   \
              std::enable_if_t<std::is_same_v<Struct, T> || std::is_same_v<const Struct, T>, bool> = true,  \
              typename Func>                                                                                \
    inline size_t __StructTagsExternal_Entrance(T* s, const ::struct_tags::Options& options, Func&& func) { \
        using _Struct = Struct;                                                                             \
        size_t size = 0;

#define STRUCT_TAGS_EXTERNAL_DECLARE_FIELD(field, ...) STRUCT_TAGS_DECLARE_FIELD(field, ##__VA_ARGS__)

#define STRUCT_TAGS_EXTERNAL_DECLARE_END \
    return size;                         \
    }

#endif  // STRUCT_TAGS_INTERNAL_MACROS_H
