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

#define STRUCT_TAGS_DECLARE_END                                                                            \
                                                                                                           \
    return size;                                                                                           \
    }                                                                                                      \
                                                                                                           \
public:                                                                                                    \
    size_t NumField() {                                                                                    \
        static auto options = ::struct_tags::OptionsBuilder().WithVisitField().Build();                    \
        return __StructTags_Entrance(this, options, []([[maybe_unused]] auto&& field) {});                 \
    }                                                                                                      \
                                                                                                           \
    template <typename Func>                                                                               \
    void FieldByIndex(size_t ix, Func&& f) {                                                               \
        static auto options =                                                                              \
                ::struct_tags::OptionsBuilder().WithVisitField().WithVisitByIndex().WithIndex(ix).Build(); \
        __StructTags_Entrance(this, options, std::forward<Func>(f));                                       \
    }                                                                                                      \
                                                                                                           \
    template <typename Func>                                                                               \
    void FieldByName(const char* name, Func&& f) {                                                         \
        static auto options =                                                                              \
                ::struct_tags::OptionsBuilder().WithVisitField().WithVisitByName().WithName(name).Build(); \
        __StructTags_Entrance(this, options, std::forward<Func>(f));                                       \
    }                                                                                                      \
                                                                                                           \
    template <typename Func>                                                                               \
    void FieldForEach(Func&& f) {                                                                          \
        static auto options = ::struct_tags::OptionsBuilder().WithVisitField().WithVisitForEach().Build(); \
        __StructTags_Entrance(this, options, std::forward<Func>(f));                                       \
    }                                                                                                      \
                                                                                                           \
private:

#define STRUCT_TAGS_EXTERNAL_DECLARE_BEGIN(Struct)                                                               \
    template <typename Func> /* NOLINTNEXTLINE(bugprone-macro-parentheses) */                                    \
    inline size_t __StructTagsExternal_Entrance(Struct* s, const ::struct_tags::Options& options, Func&& func) { \
        using _Struct = Struct;                                                                                  \
        size_t size = 0;

#define STRUCT_TAGS_EXTERNAL_DECLARE_FIELD(field, ...) STRUCT_TAGS_DECLARE_FIELD(field, ##__VA_ARGS__)

#define STRUCT_TAGS_EXTERNAL_DECLARE_END \
    return size;                         \
    }

#endif  // STRUCT_TAGS_INTERNAL_MACROS_H
