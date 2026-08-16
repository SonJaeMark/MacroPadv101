#pragma once

#include <vector>
#include <functional>

#include "IKeyboardDriver.h"
#include "IMacroButton.h"
#include "IMacro.h"
#include "ChordManager.h"


class MacroPad
{
public:

    explicit MacroPad(
        IKeyboardDriver& keyboard);


    // ========================================================
    // Buttons
    // ========================================================

    MacroPad& add(
        IMacroButton& button);


    // ========================================================
    // Chords
    // ========================================================

    MacroPad& chord(
        const std::vector<IMacroButton*>& buttons,
        IMacro& macro);


    // ========================================================
    // Lifecycle
    // ========================================================

    void begin();

    void tick();


private:

    // ========================================================
    // Dependencies
    // ========================================================

    IKeyboardDriver& keyboard;


    // ========================================================
    // Buttons
    // ========================================================

    std::vector<
        std::reference_wrapper<IMacroButton>
    > buttons;


    // ========================================================
    // Chord manager
    // ========================================================

    ChordManager chordManager;
};