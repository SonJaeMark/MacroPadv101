#pragma once

#include <vector>

#include "IButtonListener.h"
#include "IMacroButton.h"
#include "IMacro.h"
#include "IKeyboardDriver.h"

struct Chord
{
    std::vector<IMacroButton*> buttons;

    IMacro* macro = nullptr;

    bool executed = false;
};


class ChordManager : public IButtonListener
{
public:

    void addChord(
        const std::vector<IMacroButton*>& buttons,
        IMacro& macro);


    void update(
        IKeyboardDriver& driver);


    // IButtonListener

    void onButtonPress(
        IMacroButton& button) override;


    void onButtonRelease(
        IMacroButton& button) override;


private:

    std::vector<Chord> chords;

    IKeyboardDriver* keyboardDriver = nullptr;


    bool allPressed(
        const Chord& chord) const;


    bool allReleased(
        const Chord& chord) const;


    void executeChord(
        Chord& chord);


    void suppressChordButtons(
        const Chord& chord);


    void releaseChordButtons(
        const Chord& chord);
};