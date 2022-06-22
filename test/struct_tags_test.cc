#include <gtest/gtest.h>

#include "struct_tags/struct_tags.h"

namespace struct_tags {

class StructTagsTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

struct A {
    int a{0};
    char c;

    STRUCT_TAGS_BEGIN
    STRUCT_TAGS_DECLARE_FIELD(a)
    STRUCT_TAGS_DECLARE_FIELD(c)
    STRUCT_TAGS_END
};

TEST_F(StructTagsTest, struct_tags_test) {
    A a;

    EXPECT_EQ(a.NumField(), 2);

    a.FieldByIndex(0, [&a](auto&& field) {
        EXPECT_EQ(field.Name(), "a");
        EXPECT_EQ(*field.Value(), 0);

        *field.Value() = 1;
        EXPECT_EQ(a.a, 1);

        field.SetValue(2);
        EXPECT_EQ(a.a, 2);
    });
}

}  // namespace struct_tags
