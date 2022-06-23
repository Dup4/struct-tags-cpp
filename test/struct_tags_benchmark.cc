#include <benchmark/benchmark.h>

#include "struct_tags/internal/struct_tags.h"
#include "struct_tags/struct_tags.h"

struct A {
    int a{0};
    int b{0};
    int c{0};
    int d{0};
    int e{0};
    int f{0};
    int g{0};
    int h{0};
    int i{0};
    int j{0};
    int k{0};
    int l{0};
    int m{0};
    int n{0};
    int o{0};
    int p{0};
    int q{0};
    int r{0};
    int s{0};
    int t{0};
    int u{0};
    int v{0};
    int w{0};
    int x{0};
    int y{0};
    int z{0};

    STRUCT_TAGS_DECLARE_BEGIN(A)
    STRUCT_TAGS_DECLARE_FIELD(a, {"json", "_a"})
    STRUCT_TAGS_DECLARE_FIELD(b, {"json", "_b"})
    STRUCT_TAGS_DECLARE_FIELD(c, {"json", "_c"})
    STRUCT_TAGS_DECLARE_FIELD(d, {"json", "_d"})
    STRUCT_TAGS_DECLARE_FIELD(e, {"json", "_e"})
    STRUCT_TAGS_DECLARE_FIELD(f, {"json", "_f"})
    STRUCT_TAGS_DECLARE_FIELD(g, {"json", "_g"})
    STRUCT_TAGS_DECLARE_FIELD(h, {"json", "_h"})
    STRUCT_TAGS_DECLARE_FIELD(i, {"json", "_i"})
    STRUCT_TAGS_DECLARE_FIELD(j, {"json", "_j"})
    STRUCT_TAGS_DECLARE_FIELD(k, {"json", "_k"})
    STRUCT_TAGS_DECLARE_FIELD(l, {"json", "_l"})
    STRUCT_TAGS_DECLARE_FIELD(m, {"json", "_m"})
    STRUCT_TAGS_DECLARE_FIELD(n, {"json", "_n"})
    STRUCT_TAGS_DECLARE_FIELD(o, {"json", "_o"})
    STRUCT_TAGS_DECLARE_FIELD(p, {"json", "_p"})
    STRUCT_TAGS_DECLARE_FIELD(q, {"json", "_q"})
    STRUCT_TAGS_DECLARE_FIELD(r, {"json", "_r"})
    STRUCT_TAGS_DECLARE_FIELD(s, {"json", "_s"})
    STRUCT_TAGS_DECLARE_FIELD(t, {"json", "_t"})
    STRUCT_TAGS_DECLARE_FIELD(u, {"json", "_u"})
    STRUCT_TAGS_DECLARE_FIELD(v, {"json", "_v"})
    STRUCT_TAGS_DECLARE_FIELD(w, {"json", "_w"})
    STRUCT_TAGS_DECLARE_FIELD(x, {"json", "_x"})
    STRUCT_TAGS_DECLARE_FIELD(y, {"json", "_y"})
    STRUCT_TAGS_DECLARE_FIELD(z, {"json", "_z"})
    STRUCT_TAGS_DECLARE_END
};

static void BenchmarkStructTagsFieldForEachWithoutReflect(benchmark::State& state) {
    for (auto _ : state) {
        A a;

        a.a = 1;
        a.b = 1;
        a.c = 1;
        a.d = 1;
        a.e = 1;
        a.f = 1;
        a.g = 1;
        a.h = 1;
        a.i = 1;
        a.j = 1;
        a.k = 1;
        a.l = 1;
        a.m = 1;
        a.n = 1;
        a.o = 1;
        a.p = 1;
        a.q = 1;
        a.r = 1;
        a.s = 1;
        a.t = 1;
        a.u = 1;
        a.v = 1;
        a.w = 1;
        a.x = 1;
        a.y = 1;
        a.z = 1;

        assert(a.a == 1);
    }
}

BENCHMARK(BenchmarkStructTagsFieldForEachWithoutReflect);

static void BenchmarkStructTagsNumField(benchmark::State& state) {
    for (auto _ : state) {
        A a;

        auto s = struct_tags::NewStructTags(&a);

        s.NumField();
    }
}

BENCHMARK(BenchmarkStructTagsNumField);

static void BenchmarkStructTagsFieldForEach(benchmark::State& state) {
    for (auto _ : state) {
        A a;

        auto s = struct_tags::NewStructTags(&a);

        s.FieldForEach([](auto&& field) {
            field.Value() = 1;
        });

        assert(a.a == 1);
    }
}

BENCHMARK(BenchmarkStructTagsFieldForEach);

static void BenchmarkStructTagsFieldByIndex(benchmark::State& state) {
    for (auto _ : state) {
        A a;

        auto s = struct_tags::NewStructTags(&a);

        s.FieldByIndex(25, [](auto&& field) {
            field.Value() = 1;
        });

        assert(a.z == 1);
    }
}

BENCHMARK(BenchmarkStructTagsFieldByIndex);

static void BenchmarkStructTagsFieldByName(benchmark::State& state) {
    for (auto _ : state) {
        A a;

        auto s = struct_tags::NewStructTags(&a);

        s.FieldByName("z", [](auto&& field) {
            field.Value() = 1;
        });

        assert(a.z == 1);
    }
}

BENCHMARK(BenchmarkStructTagsFieldByName);

static void BenchmarkStructTagsVisitEachFieldByFieldByIndex(benchmark::State& state) {
    for (auto _ : state) {
        A a;

        auto s = struct_tags::NewStructTags(&a);

        size_t n = s.NumField();
        for (size_t i = 0; i < n; i++) {
            s.FieldByIndex(i, [](auto&& field) {
                field.Value() = 1;
            });
        }

        assert(a.a == 1);
    }
}

BENCHMARK(BenchmarkStructTagsVisitEachFieldByFieldByIndex);
