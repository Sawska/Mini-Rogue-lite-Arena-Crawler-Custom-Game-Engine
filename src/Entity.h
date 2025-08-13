#pragma once
#include <vector>
#include <memory>
#include <typeindex>
#include <unordered_map>

class Component;
#pragma once
#include <vector>
#include <memory>
#include <typeindex>
#include <unordered_map>

class Component;

class Entity {
public:
    Entity(int id) : id(id) {}
    int getId() const { return id; }

    template<typename T, typename... Args>
    T& addComponent(Args&&... args) {
        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        T& ref = *component;
        components[std::type_index(typeid(T))] = std::move(component);
        return ref;
    }

    template<typename T>
    T* getComponent() {
        auto it = components.find(std::type_index(typeid(T)));
        if (it != components.end()) {
            return static_cast<T*>(it->second.get());
        }
        return nullptr;
    }

private:
    int id;
    std::unordered_map<std::type_index, std::unique_ptr<Component>> components;
};

