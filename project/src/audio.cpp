#include <string>

#include "audio.hpp"

// Audio::Audio() : engine(irrklang::createIrrKlangDevice()) {
Audio::Audio() {
    // auto list = irrklang::createSoundDeviceList();
}

Audio::~Audio() {
    // TODO destroy audio engine
}

void Audio::play(const std::string &sound) {
    // engine->play2D(sound.data());
}
