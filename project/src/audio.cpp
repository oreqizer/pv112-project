#include <string>

#include "audio.hpp"

const std::string& Audio::nom = "../sound/crunch.mp3";
const std::string& Audio::background = "../sound/portal.mp3";
const std::string& Audio::crash = "../sound/trombone.mp3";

irrklang::ISoundEngine* Audio::engine = irrklang::createIrrKlangDevice();

void Audio::play(const std::string &sound, bool loop) {
    Audio::engine->play2D(sound.data(), loop);
}
