#include <gtest/gtest.h>

#include "struct_tags/struct_tags.h"

namespace struct_tags {

class StructTagsTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

struct A {
    int a{0};
    char c{'a'};

    STRUCT_TAGS_BEGIN
    STRUCT_TAGS_DECLARE_FIELD(a, {"json", "_a"})
    STRUCT_TAGS_DECLARE_FIELD(c, {"json", "_c"})
    STRUCT_TAGS_END
};

TEST_F(StructTagsTest, struct_tags_test) {
    A a;

    static_assert(a.NumField() == 2);

    a.FieldByIndex(0, [&a](auto&& field) {
        EXPECT_EQ(field.Name(), "a");
        EXPECT_EQ(field.Value(), 0);
        EXPECT_EQ(field.Tag("json").value(), "_a");

        field.Value() = 1;
        EXPECT_EQ(a.a, 1);
    });

    EXPECT_EQ(a.a, 1);

    a.FieldByIndex(1, [](auto&& field) {
        EXPECT_EQ(field.Name(), "c");
        EXPECT_EQ(field.Value(), 'a');
        EXPECT_EQ(field.Tag("json").value(), "_c");

        field.Value() = 'b';
    });

    EXPECT_EQ(a.c, 'b');

    a.FieldByName("a", [&a](auto&& field) {
        EXPECT_EQ(field.Name(), "a");
        EXPECT_EQ(field.Value(), 1);

        field.Value() = 2;
        EXPECT_EQ(a.a, 2);
    });

    EXPECT_EQ(a.a, 2);
}

}  // namespace struct_tags
