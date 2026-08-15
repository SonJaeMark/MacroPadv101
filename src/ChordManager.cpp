#include "ChordManager.h"

#include <algorithm>

#include "IMacroButton.h"
#include "IMacro.h"
#include "IKeyboardDriver.h"


ChordManager::ChordManager(
    IKeyboardDriver& keyboard)
    : keyboard(keyboard)
{
}


// ============================================================
// Add chord
// ============================================================

void ChordManager::addChord(
    const std::vector<IMacroButton*>& buttons,
    IMacro& macro)
{
    Chord chord;

    chord.buttons = buttons;
    chord.macro = &macro;
    chord.executed = false;

    chords.push_back(std::move(chord));
}


// ============================================================
// Button pressed
// ============================================================

void ChordManager::onButtonPress(
    IMacroButton& button)
{
    IMacroButton* buttonPtr = &button;

    // Prevent duplicate entries.
    if (!containsPressed(buttonPtr))
    {
        pressedButtons.push_back(buttonPtr);
    }

    // Check every registered chord.
    for (Chord& chord : chords)
    {
        if (chord.executed)
            continue;

        if (!chordIsPressed(chord))
            continue;

        executeChord(chord);
    }
}


// ============================================================
// Button released
// ============================================================

void ChordManager::onButtonRelease(
    IMacroButton& button)
{
    IMacroButton* buttonPtr = &button;

    auto it = std::find(
        pressedButtons.begin(),
        pressedButtons.end(),
        buttonPtr
    );

    if (it != pressedButtons.end())
    {
        pressedButtons.erase(it);
    }

    // A chord can be triggered again after
    // at least one of its buttons is released.
    for (Chord& chord : chords)
    {
        if (!chordIsPressed(chord))
        {
            chord.executed = false;
        }
    }
}


// ============================================================
// Check whether a button is currently pressed
// ============================================================

bool ChordManager::containsPressed(
    IMacroButton* button) const
{
    return std::find(
        pressedButtons.begin(),
        pressedButtons.end(),
        button
    ) != pressedButtons.end();
}


// ============================================================
// Check whether every button in a chord is pressed
// ============================================================

bool ChordManager::chordIsPressed(
    const Chord& chord) const
{
    if (chord.buttons.empty())
        return false;

    for (IMacroButton* button : chord.buttons)
    {
        if (button == nullptr)
            return false;

        if (!containsPressed(button))
            return false;
    }

    return true;
}


// ============================================================
// Execute chord
// ============================================================

void ChordManager::executeChord(
    Chord& chord)
{
    if (chord.macro == nullptr)
        return;

    chord.macro->execute(keyboard);

    chord.executed = true;
}