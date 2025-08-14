#pragma once
#include "../Component.h"
#include <string>

struct NameComponent : public Component {
    std::string name;
    explicit NameComponent(std::string n) : name(std::move(n)) {}
};
