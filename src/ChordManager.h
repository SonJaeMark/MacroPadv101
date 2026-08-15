#pragma once

#include <vector>

#include "IButtonListener.h"
#include "Chord.h"

class IKeyboardDriver;

class ChordManager : public IButtonListener
{
public:
    explicit ChordManager(IKeyboardDriver& keyboard);

    void addChord(
        const std::vector<IMacroButton*>& buttons,
        IMacro& macro);

    void onButtonPress(
        IMacroButton& button) override;

    void onButtonRelease(
        IMacroButton& button) override;

private:
    IKeyboardDriver& keyboard;

    std::vector<Chord> chords;

    std::vector<IMacroButton*> pressedButtons;

    bool containsPressed(
        IMacroButton* button) const;

    bool chordIsPressed(
        const Chord& chord) const;

    void executeChord(Chord& chord);
};