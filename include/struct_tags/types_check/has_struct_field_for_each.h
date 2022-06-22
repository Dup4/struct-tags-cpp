#ifndef STRUCT_TAGS_TYPES_CHECK_HAS_STRUCT_FIELD_FOR_EACH_H
#define STRUCT_TAGS_TYPES_CHECK_HAS_STRUCT_FIELD_FOR_EACH_H

#include <type_traits>

namespace struct_tags {

template <typename T>
class has_struct_field_for_each {
private:
    template <typename U>
    static constexpr auto check(int) -> decltype(std::declval<U>().FieldForEach(), std::true_type());

    template <typename>
    static constexpr std::false_type check(...);

    typedef decltype(check<T>(0)) type;

public:
    static constexpr bool value = type::value;
};

template <typename T>
inline constexpr bool has_struct_field_for_each_v = has_struct_field_for_each<T>::value;

}  // namespace struct_tags

#endif  // STRUCT_TAGS_TYPES_CHECK_HAS_STRUCT_FIELD_FOR_EACH_H
