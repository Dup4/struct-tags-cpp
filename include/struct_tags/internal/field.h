#ifndef STRUCT_TAGS_INTERNAL_FIELD_H
#define STRUCT_TAGS_INTERNAL_FIELD_H

#include <map>
#include <string>

namespace struct_tags {

template <typename T>
class Field {
public:
    Field() = delete;
    Field(const char* name, T* value, std::map<std::string, std::string> tags = {})
            : name_(name), value_(value), tags_(tags) {}

    constexpr const char* Name() const {
        return name_;
    }

    T& Value() {
        return *value_;
    }

    std::optional<std::string> Tag(const std::string& key) const {
        if (tags_.count(key) == 0) {
            return std::nullopt;
        }

        return tags_.at(key);
    }

    const std::map<std::string, std::string>& Tags() const {
        return tags_;
    }

private:
    const char* name_;
    T* value_;
    std::map<std::string, std::string> tags_{};
};

}  // namespace struct_tags

#endif  // STRUCT_TAGS_INTERNAL_FIELD_H
