#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <iostream>
#include <memory>
#include <vector>

class DJ {
private:
    std::map<std::string, std::unique_ptr<sf::Music>> backgroundMusic; // For background music
    std::map<std::string, sf::SoundBuffer> soundEffects; // For sound effects
    sf::Sound sound; // For playing sound effects

public:
    DJ() = default;

    // Load background music from a file
    bool loadBackgroundMusic(const std::string& identifier, const std::string& filePath) {
        auto music = std::make_unique<sf::Music>(); // Use unique_ptr for dynamic allocation
        if (!music->openFromFile(filePath)) {
            return false; // Failed to load music
        }
        backgroundMusic[identifier] = std::move(music);
        return true;
    }

    // Load sound effects from a file
    bool loadSoundEffect(const std::string& identifier, const std::string& filePath) {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(filePath)) {
            return false; // Failed to load sound effect
        }
        soundEffects[identifier] = std::move(buffer);
        return true;
    }

    // Play background music
    void playBackgroundMusic(const std::string& identifier, bool loop = true) {
        auto it = backgroundMusic.find(identifier);
        if (it != backgroundMusic.end()) {
            it->second->setLoop(loop);
            it->second->play();
        } else {
            std::cerr << "Background music not found: " << identifier << std::endl;
        }
    }

    // Stop background music
    void stopBackgroundMusic(const std::string& identifier) {
        auto it = backgroundMusic.find(identifier);
        if (it != backgroundMusic.end()) {
            it->second->stop();
        } else {
            std::cerr << "Background music not found: " << identifier << std::endl;
        }
    }

    // Play sound effect
    void playSoundEffect(const std::string& identifier) {
        auto it = soundEffects.find(identifier);
        if (it != soundEffects.end()) {
            sound.setBuffer(it->second);
            sound.play();
        } else {
            std::cerr << "Sound effect not found: " << identifier << std::endl;
        }
    }
    // Pseudo-code for using SoundBuffer instead of Music for muffling
    void muffleSoundBuffer(const std::string& identifier, float cutoffFrequency) {
        auto it = soundEffects.find(identifier);
        if (it != soundEffects.end()) {
            const sf::SoundBuffer& buffer = it->second;

            // Get sample data from the buffer
            const sf::Int16* samples = buffer.getSamples();
            std::size_t sampleCount = buffer.getSampleCount();
            std::vector<sf::Int16> filteredSamples(sampleCount);

            // Apply low-pass filter to the samples
            // (filtering logic here...)

            // Create a new SoundBuffer with filtered samples
            sf::SoundBuffer filteredBuffer;
            filteredBuffer.loadFromSamples(filteredSamples.data(), sampleCount, buffer.getChannelCount(), buffer.getSampleRate());

            // Play the muffled sound
            sound.setBuffer(filteredBuffer);
            sound.play();
        } else {
            std::cerr << "Sound effect not found: " << identifier << std::endl;
        }
    }


    // Set volume for music and sound effects
    void setVolume(float volume) {
        for (auto& pair : backgroundMusic) {
            pair.second->setVolume(volume);
        }
        sound.setVolume(volume); // Set volume for sound effects
    }
};
