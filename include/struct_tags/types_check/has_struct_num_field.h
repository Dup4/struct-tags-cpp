#ifndef STRUCT_TAGS_TYPES_CHECK_HAS_STRUCT_NUM_FIELD_H
#define STRUCT_TAGS_TYPES_CHECK_HAS_STRUCT_NUM_FIELD_H

#include <type_traits>

namespace struct_tags {

template <typename T>
class has_struct_num_field {
private:
    template <typename U>
    static constexpr auto check(int) -> decltype(std::declval<U>().NumField(), std::true_type());

    template <typename>
    static constexpr std::false_type check(...);

    typedef decltype(check<T>(0)) type;

public:
    static constexpr bool value = type::value;
};

template <typename T>
inline constexpr bool has_struct_num_field_v = has_struct_num_field<T>::value;

}  // namespace struct_tags

#endif  // STRUCT_TAGS_TYPES_CHECK_HAS_STRUCT_NUM_FIELD_H
