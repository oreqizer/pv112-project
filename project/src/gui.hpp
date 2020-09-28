#pragma once
#ifndef GUI_H
#define GUI_H

#include <map>

#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

struct Character {
    unsigned int textureID; // ID handle of the glyph texture
    glm::ivec2 size;        // Size of glyph
    glm::ivec2 bearing;     // Offset from baseline to left/top of glyph
    unsigned int advance;   // Offset to advance to next glyph
};

class Gui {
public:
    Gui();
    ~Gui() = default;

    FT_Face face;
    std::map<char, Character> characters;

private:
    FT_Library library;
};

#endif
