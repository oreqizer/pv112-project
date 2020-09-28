#pragma once
#ifndef AUDIO_H
#define AUDIO_H

#include <string>

#include <irrKlang.h>

class Audio {
public:
    Audio();
    ~Audio();

    void play(const std::string &sound);

private:
    // irrklang::ISoundEngine* engine;
};

#endif
