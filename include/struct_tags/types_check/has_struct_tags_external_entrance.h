#ifndef STRUCT_TAGS_TYPES_CHECK_HAS_STRUCT_TAGS_EXTERNAL_ENTRANCE_H
#define STRUCT_TAGS_TYPES_CHECK_HAS_STRUCT_TAGS_EXTERNAL_ENTRANCE_H

#include <type_traits>

#include "../internal/options.h"

namespace struct_tags {

template <typename T>
class has_struct_tags_external_entrance {
private:
    template <typename U>
    static constexpr auto check(int)
            -> decltype(__StructTagsExternal_Entrance(std::declval<U*>(), std::declval<Options>(), nullptr),
                        std::true_type());

    template <typename>
    static constexpr std::false_type check(...);

    typedef decltype(check<T>(0)) type;

public:
    static constexpr bool value = type::value;
};

template <typename T>
inline constexpr bool has_struct_tags_external_entrance_v = has_struct_tags_external_entrance<T>::value;

}  // namespace struct_tags

#endif  // STRUCT_TAGS_TYPES_CHECK_HAS_STRUCT_TAGS_EXTERNAL_ENTRANCE_H
