#pragma once
#ifndef AUDIO_H
#define AUDIO_H

#include <string>

#include <irrKlang.h>

// === 3. Audio ===
class Audio {
public:
    static const std::string& nom;
    static const std::string& background;
    static const std::string& crash;

    Audio() {};
    ~Audio() = default;

    static void play(const std::string &sound, bool loop = false);

private:
    static irrklang::ISoundEngine* engine;
};

#endif
