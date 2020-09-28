#pragma once
#ifndef GUI_H
#define GUI_H

#include <ft2build.h>
#include FT_FREETYPE_H

class Gui {
public:
    Gui();
    ~Gui() = default;

private:
    FT_Library library;
};

#endif
