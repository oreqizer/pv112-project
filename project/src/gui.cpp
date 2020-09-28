#include <iostream>

#include "gui.hpp"

Gui::Gui() : library(FT_Library()) {
    FT_Init_FreeType(&library);

    if (FT_New_Face(library, "../fonts/bebas.ttf", 0, &face)) {
        std::cerr << "[gui.cpp] Failed to load font :(" << std::endl;
    }
    FT_Set_Pixel_Sizes(face, 0, 48);
}
