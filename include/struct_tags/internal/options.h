#ifndef STRUCT_TAGS_INTERNAL_OPTIONS_H
#define STRUCT_TAGS_INTERNAL_OPTIONS_H

#include <map>
#include <string>

namespace struct_tags {

struct Options {
public:
    bool visit_field{false};
    bool visit_by_index{false};
    bool visit_by_name{false};
    bool visit_for_each{false};
    size_t index{0};
    const char* name{nullptr};
};

class OptionsBuilder {
public:
    OptionsBuilder() = default;

    OptionsBuilder& WithVisitField() {
        options_.visit_field = true;
        return *this;
    }

    OptionsBuilder& WithVisitByIndex() {
        options_.visit_by_index = true;
        return *this;
    }

    OptionsBuilder& WithVisitByName() {
        options_.visit_by_name = true;
        return *this;
    }

    OptionsBuilder& WithVisitForEach() {
        options_.visit_for_each = true;
        return *this;
    }

    OptionsBuilder& WithIndex(size_t ix) {
        options_.index = ix;
        return *this;
    }

    OptionsBuilder& WithName(const char* name) {
        options_.name = name;
        return *this;
    }

    Options Build() {
        return options_;
    }

private:
    Options options_;
};

}  // namespace struct_tags

#endif  // STRUCT_TAGS_INTERNAL_OPTIONS_H
