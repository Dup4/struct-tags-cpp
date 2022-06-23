#include <gtest/gtest.h>

#include "struct_tags/struct_tags.h"

struct A {
    int a{0};
    char c{'a'};
    uint flag{0};

    STRUCT_TAGS_DECLARE_BEGIN(A)
    STRUCT_TAGS_DECLARE_FIELD(a, {"json", "_a"})
    STRUCT_TAGS_DECLARE_FIELD(c, {"json", "_c"})
    STRUCT_TAGS_DECLARE_FIELD(flag, {"json", "_flag"})
    STRUCT_TAGS_DECLARE_END
};

struct B {
    int a{0};
    char c{'a'};
    uint flag{0};
};

STRUCT_TAGS_EXTERNAL_DECLARE_BEGIN(B)
STRUCT_TAGS_EXTERNAL_DECLARE_FIELD(a, {"json", "_a"})
STRUCT_TAGS_EXTERNAL_DECLARE_FIELD(c, {"json", "_c"})
STRUCT_TAGS_EXTERNAL_DECLARE_FIELD(flag, {"json", "_flag"})
STRUCT_TAGS_EXTERNAL_DECLARE_END

namespace struct_tags {

class StructTagsTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

TEST_F(StructTagsTest, struct_tags_test) {
    A a;

    auto s = NewStructTags(&a);

    // can not use `static_assert(s.NumField() == 3);`
    EXPECT_EQ(s.NumField(), 3);

    s.FieldByIndex(0, [&a](auto&& field) {
        EXPECT_EQ(field.Name(), "a");
        EXPECT_EQ(field.Value(), 0);
        EXPECT_EQ(field.Tag("json").value(), "_a");
        EXPECT_EQ(field.Tags().count("json"), 1);

        field.Value() = 1;
        EXPECT_EQ(a.a, 1);
    });

    EXPECT_EQ(a.a, 1);

    s.FieldByIndex(1, [](auto&& field) {
        EXPECT_EQ(field.Name(), "c");
        EXPECT_EQ(field.Value(), 'a');
        EXPECT_EQ(field.Tag("json").value(), "_c");
        EXPECT_EQ(field.Tags().count("json"), 1);

        field.Value() = 'b';
    });

    EXPECT_EQ(a.c, 'b');

    s.FieldByName("a", [&a](auto&& field) {
        EXPECT_EQ(field.Name(), "a");
        EXPECT_EQ(field.Value(), 1);

        field.Value() = 2;
        EXPECT_EQ(a.a, 2);
    });

    EXPECT_EQ(a.a, 2);

    s.FieldForEach(struct_tags::Overload(
            [](struct_tags::Field<int>&& field) {
                EXPECT_EQ(field.Name(), "a");
                EXPECT_EQ(field.Value(), 2);

                field.Value() = 3;
            },
            [](struct_tags::Field<char>&& field) {
                EXPECT_EQ(field.Name(), "c");
                EXPECT_EQ(field.Value(), 'b');

                field.Value() = 'c';
            },
            [](auto&& field) {
                EXPECT_EQ(field.Name(), "flag");
                EXPECT_EQ(field.Value(), 0);

                field.Value() = 1;
            }));

    EXPECT_EQ(a.a, 3);
    EXPECT_EQ(a.c, 'c');

    s.Interface().a = 4;
    EXPECT_EQ(a.a, 4);
}

TEST_F(StructTagsTest, struct_tags_const_test) {
    const A a = A();

    auto s = NewStructTags(&a);

    // can not use `static_assert(s.NumField() == 3);`
    EXPECT_EQ(s.NumField(), 3);

    s.FieldByIndex(0, [](auto&& field) {
        EXPECT_EQ(field.Name(), "a");
        EXPECT_EQ(field.Value(), 0);
        EXPECT_EQ(field.Tag("json").value(), "_a");
        EXPECT_EQ(field.Tags().count("json"), 1);
    });

    s.FieldForEach(struct_tags::Overload(
            [](struct_tags::Field<const int>&& field) {
                EXPECT_EQ(field.Name(), "a");
                EXPECT_EQ(field.Value(), 0);
            },
            [](struct_tags::Field<const char>&& field) {
                EXPECT_EQ(field.Name(), "c");
                EXPECT_EQ(field.Value(), 'a');
            },
            [](auto&& field) {
                EXPECT_EQ(field.Name(), "flag");
                EXPECT_EQ(field.Value(), 0);
            }));
}

TEST_F(StructTagsTest, struct_tags_tags_external_test) {
    B a;

    auto s = NewStructTags(&a);

    // can not use `static_assert(s.NumField() == 3);`
    EXPECT_EQ(s.NumField(), 3);

    s.FieldByIndex(0, [&a](auto&& field) {
        EXPECT_EQ(field.Name(), "a");
        EXPECT_EQ(field.Value(), 0);
        EXPECT_EQ(field.Tag("json").value(), "_a");
        EXPECT_EQ(field.Tags().count("json"), 1);

        field.Value() = 1;
        EXPECT_EQ(a.a, 1);
    });

    EXPECT_EQ(a.a, 1);

    s.FieldByIndex(1, [](auto&& field) {
        EXPECT_EQ(field.Name(), "c");
        EXPECT_EQ(field.Value(), 'a');
        EXPECT_EQ(field.Tag("json").value(), "_c");
        EXPECT_EQ(field.Tags().count("json"), 1);

        field.Value() = 'b';
    });

    EXPECT_EQ(a.c, 'b');

    s.FieldByName("a", [&a](auto&& field) {
        EXPECT_EQ(field.Name(), "a");
        EXPECT_EQ(field.Value(), 1);

        field.Value() = 2;
        EXPECT_EQ(a.a, 2);
    });

    EXPECT_EQ(a.a, 2);

    s.FieldForEach(struct_tags::Overload(
            [](struct_tags::Field<int>&& field) {
                EXPECT_EQ(field.Name(), "a");
                EXPECT_EQ(field.Value(), 2);

                field.Value() = 3;
            },
            [](struct_tags::Field<char>&& field) {
                EXPECT_EQ(field.Name(), "c");
                EXPECT_EQ(field.Value(), 'b');

                field.Value() = 'c';
            },
            [](auto&& field) {
                EXPECT_EQ(field.Name(), "flag");
                EXPECT_EQ(field.Value(), 0);

                field.Value() = 1;
            }));

    EXPECT_EQ(a.a, 3);
    EXPECT_EQ(a.c, 'c');

    s.Interface().a = 4;
    EXPECT_EQ(a.a, 4);
}

}  // namespace struct_tags
