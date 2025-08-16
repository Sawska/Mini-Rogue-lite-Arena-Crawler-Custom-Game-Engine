#pragma once
#include <string>
#include <unordered_map>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class AssetManager {
public:
    sf::Texture& loadTexture(const std::string& path) {
        if (!textures[path].loadFromFile(path))
            throw std::runtime_error("Failed to load texture: " + path);
        return textures[path];
    }

    sf::SoundBuffer& loadSound(const std::string& path) {
        if (!sounds[path].loadFromFile(path))
            throw std::runtime_error("Failed to load sound: " + path);
        return sounds[path];
    }

private:
    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::SoundBuffer> sounds;
};
