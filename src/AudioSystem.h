#pragma once
#include <SFML/Audio.hpp>
#include <vector>

class AudioSystem {
public:
    void playSound(const sf::SoundBuffer& buffer) {
        sf::Sound sound;
        sound.setBuffer(buffer);
        sound.play();
        sounds.push_back(std::move(sound));
    }

    void update() {
        
        sounds.erase(std::remove_if(sounds.begin(), sounds.end(),
            [](const sf::Sound& s) { return s.getStatus() == sf::Sound::Stopped; }),
            sounds.end());
    }

private:
    std::vector<sf::Sound> sounds;
};


void playCombatSound() {
    if (!combatBuffer.loadFromFile("assets/slash.wav")) return;
    sf::Sound sound;
    sound.setBuffer(combatBuffer);
    sound.play();
    sounds.push_back(std::move(sound));
}

sf::SoundBuffer combatBuffer;