#ifndef STRUCT_TAGS_INTERNAL_VISIT_TUPLE_H
#define STRUCT_TAGS_INTERNAL_VISIT_TUPLE_H

// https://stackoverflow.com/questions/8194227/how-to-get-the-i-th-element-from-an-stdtuple-when-i-isnt-know-at-compile-time?noredirect=1&lq=1
// https://stackoverflow.com/questions/28997271/c11-way-to-index-tuple-at-runtime-without-using-switch

#include <cstring>
#include <tuple>
#include <type_traits>

namespace struct_tags {

template <std::size_t I = 0, typename Func, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp) - 1, void>::type VisitTupleByIndex(
        size_t, std::tuple<Tp...>&&, Func&&) {}

template <std::size_t I = 0, typename Func, typename... Tp>
        inline typename std::enable_if <
        I<sizeof...(Tp) - 1, void>::type VisitTupleByIndex(size_t index, std::tuple<Tp...>&& t, Func&& f) {
    if (index == 0) {
        f(std::get<I>(std::forward<std::decay_t<decltype(t)>>(t)));
        return;
    }

    VisitTupleByIndex<I + 1, Func, Tp...>(index - 1, std::forward<std::decay_t<decltype(t)>>(t), std::forward<Func>(f));
}

template <std::size_t I = 0, typename Func, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp) - 1, void>::type VisitTupleByName(
        const char*, std::tuple<Tp...>&&, Func&&) {}

template <std::size_t I = 0, typename Func, typename... Tp>
        inline typename std::enable_if <
        I<sizeof...(Tp) - 1, void>::type VisitTupleByName(const char* name, std::tuple<Tp...>&& t, Func&& f) {
    if (!strcmp(std::get<I>(std::forward<std::decay_t<decltype(t)>>(t)).Name(), name)) {
        f(std::get<I>(std::forward<std::decay_t<decltype(t)>>(t)));
        return;
    }

    VisitTupleByName<I + 1, Func, Tp...>(name, std::forward<std::decay_t<decltype(t)>>(t), std::forward<Func>(f));
}

template <std::size_t I = 0, typename Func, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp) - 1, void>::type VisitTupleForEach(std::tuple<Tp...>&&, Func&&) {}

template <std::size_t I = 0, typename Func, typename... Tp>
        inline typename std::enable_if <
        I<sizeof...(Tp) - 1, void>::type VisitTupleForEach(std::tuple<Tp...>&& t, Func&& f) {
    f(std::get<I>(std::forward<std::decay_t<decltype(t)>>(t)));

    VisitTupleForEach<I + 1, Func, Tp...>(std::forward<std::decay_t<decltype(t)>>(t), std::forward<Func>(f));
}

}  // namespace struct_tags

#endif  // STRUCT_TAGS_INTERNAL_VISIT_TUPLE_H
