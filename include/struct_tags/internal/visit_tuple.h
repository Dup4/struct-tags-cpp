#ifndef STRUCT_TAGS_INTERNAL_VISIT_TUPLE_H
#define STRUCT_TAGS_INTERNAL_VISIT_TUPLE_H

#include <tuple>
#include <type_traits>

namespace struct_tags {

template <std::size_t I = 0, typename Func, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type VisitTupleByIndex(size_t, std::tuple<Tp...>, Func&&) {}

template <std::size_t I = 0, typename Func, typename... Tp>
        inline typename std::enable_if <
        I<sizeof...(Tp), void>::type VisitTupleByIndex(size_t index, std::tuple<Tp...> t, Func&& f) {
    if (index == 0) {
        f(std::get<I>(t));
    }

    VisitTupleByIndex<I + 1, Func, Tp...>(index - 1, t, f);
}

}  // namespace struct_tags

#endif  // STRUCT_TAGS_INTERNAL_VISIT_TUPLE_H
