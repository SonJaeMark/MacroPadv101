#include "MacroPad.h"


// ============================================================
// Constructor
// ============================================================

MacroPad::MacroPad(
    IKeyboardDriver& keyboard)
    : keyboard(keyboard)
{
}


// ============================================================
// Add Button
// ============================================================

MacroPad& MacroPad::add(
    IMacroButton& button)
{
    buttons.emplace_back(button);

    return *this;
}


// ============================================================
// Add Chord
// ============================================================

MacroPad& MacroPad::chord(
    const std::vector<IMacroButton*>& buttons,
    IMacro& macro)
{
    chordManager.addChord(
        buttons,
        macro
    );

    return *this;
}


// ============================================================
// Begin
// ============================================================

void MacroPad::begin()
{
    // --------------------------------------------------------
    // Keyboard
    // --------------------------------------------------------

    keyboard.begin();


    // --------------------------------------------------------
    // Buttons
    // --------------------------------------------------------

    for (auto& button : buttons)
    {
        IMacroButton& macroButton = button.get();

        macroButton.begin(
            keyboard
        );

        macroButton.addButtonListener(
            chordManager
        );
    }
}


// ============================================================
// Tick
// ============================================================

void MacroPad::tick()
{
    // --------------------------------------------------------
    // Buttons
    // --------------------------------------------------------

    for (auto& button : buttons)
    {
        button.get().tick();
    }


    // --------------------------------------------------------
    // Chords
    // --------------------------------------------------------

    chordManager.update(
        keyboard
    );
}