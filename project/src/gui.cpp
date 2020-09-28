#include <iostream>

#include "gui.hpp"

Gui::Gui() : library(FT_Library()) {
    FT_Init_FreeType(&library);
}
