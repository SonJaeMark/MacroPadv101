#include "ChordManager.h"

#include <Arduino.h>


// ============================================================
// Add chord
// ============================================================

void ChordManager::addChord(
    const std::vector<IMacroButton*>& buttons,
    IMacro& macro)
{
    if (buttons.empty())
        return;


    Chord chord;

    chord.buttons = buttons;

    chord.macro = &macro;

    chord.executed = false;


    chords.push_back(
        std::move(chord)
    );
}


// ============================================================
// Update
// ============================================================

void ChordManager::update(
    IKeyboardDriver& driver)
{
    keyboardDriver = &driver;


    /*
     * Do NOT detect the chord here.
     *
     * Physical press/release events are handled
     * immediately through IButtonListener.
     *
     * update() only keeps the keyboard reference
     * available for the event callbacks.
     */
}


// ============================================================
// Physical button press
// ============================================================

void ChordManager::onButtonPress(
    IMacroButton& button)
{
    (void)button;


    if (keyboardDriver == nullptr)
        return;


    for (Chord& chord : chords)
    {
        if (chord.executed)
            continue;


        if (!allPressed(chord))
            continue;


        executeChord(chord);
    }
}


// ============================================================
// Physical button release
// ============================================================

void ChordManager::onButtonRelease(
    IMacroButton& button)
{
    (void)button;


    for (Chord& chord : chords)
    {
        if (!chord.executed)
            continue;


        if (!allReleased(chord))
            continue;


        Serial.println("CHORD RESET");


        releaseChordButtons(chord);


        chord.executed = false;
    }
}


// ============================================================
// Execute chord
// ============================================================

void ChordManager::executeChord(
    Chord& chord)
{
    if (chord.macro == nullptr)
        return;


    if (keyboardDriver == nullptr)
        return;


    Serial.println("CHORD DETECTED");


    /*
     * VERY IMPORTANT:
     *
     * Suppress the individual buttons BEFORE
     * executing the macro.
     *
     * This prevents their later CLICK /
     * DOUBLE CLICK / MULTI CLICK events.
     */

    suppressChordButtons(chord);


    chord.macro->execute(
        *keyboardDriver
    );


    chord.executed = true;
}


// ============================================================
// All buttons pressed?
// ============================================================

bool ChordManager::allPressed(
    const Chord& chord) const
{
    for (IMacroButton* button : chord.buttons)
    {
        if (button == nullptr)
            return false;


        if (!button->isPressed())
            return false;
    }


    return true;
}


// ============================================================
// All buttons released?
// ============================================================

bool ChordManager::allReleased(
    const Chord& chord) const
{
    for (IMacroButton* button : chord.buttons)
    {
        if (button == nullptr)
            continue;


        if (button->isPressed())
            return false;
    }


    return true;
}


// ============================================================
// Suppress chord buttons
// ============================================================

void ChordManager::suppressChordButtons(
    const Chord& chord)
{
    for (IMacroButton* button : chord.buttons)
    {
        if (button == nullptr)
            continue;


        button->suppressGestures();
    }
}


// ============================================================
// Release suppression
// ============================================================

void ChordManager::releaseChordButtons(
    const Chord& chord)
{
    for (IMacroButton* button : chord.buttons)
    {
        if (button == nullptr)
            continue;


        button->releaseGestures();
    }
}