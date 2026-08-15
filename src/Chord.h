#pragma once

#include <vector>

class IMacroButton;
class IMacro;

struct Chord
{
    std::vector<IMacroButton*> buttons;

    IMacro* macro = nullptr;

    bool executed = false;
};