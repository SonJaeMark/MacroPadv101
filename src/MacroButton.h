#pragma once

#include <vector>

#include "IMacroButton.h"
#include "IButtonDriver.h"
#include "IMacro.h"
#include "IKeyboardDriver.h"
#include "IButtonListener.h"
#include "CycleMacro.h"


class MacroButton : public IMacroButton
{
public:

    explicit MacroButton(IButtonDriver& driver);


    // ========================================================
    // Lifecycle
    // ========================================================

    void begin(IKeyboardDriver& keyboard) override;

    void tick() override;


    // ========================================================
    // State
    // ========================================================

    bool isPressed() const override;


    // ========================================================
    // Normal Macro gestures
    // ========================================================

    MacroButton& onClick(IMacro& macro);

    MacroButton& onDoubleClick(IMacro& macro);

    MacroButton& onMultiClick(IMacro& macro);

    MacroButton& onLongPressStart(IMacro& macro);

    MacroButton& onLongPress(IMacro& macro);

    MacroButton& onLongPressStop(IMacro& macro);


    // ========================================================
    // CycleMacro gestures
    // ========================================================

    MacroButton& onClick(CycleMacro& cycle);

    MacroButton& onDoubleClick(CycleMacro& cycle);


    // ========================================================
    // Button listeners
    // ========================================================

    void addButtonListener(
        IButtonListener& listener) override;


    // ========================================================
    // Chord suppression
    // ========================================================

    void suppressGestures() override;

    void releaseGestures() override;

    bool gesturesSuppressed() const override;


private:

    // ========================================================
    // Dependencies
    // ========================================================

    IButtonDriver& driver;

    IKeyboardDriver* keyboardDriver = nullptr;


    // ========================================================
    // Normal gesture macros
    // ========================================================

    IMacro* clickMacro = nullptr;

    IMacro* doubleClickMacro = nullptr;

    IMacro* multiClickMacro = nullptr;

    IMacro* longPressStartMacro = nullptr;

    IMacro* longPressMacro = nullptr;

    IMacro* longPressStopMacro = nullptr;


    // ========================================================
    // Cycle macros
    // ========================================================

    CycleMacro* clickCycle = nullptr;

    CycleMacro* doubleClickCycle = nullptr;


    // ========================================================
    // Listeners
    // ========================================================

    std::vector<IButtonListener*> listeners;


    // ========================================================
    // Chord state
    // ========================================================

    bool gesturesSuppressedFlag = false;


    // ========================================================
    // Physical events
    // ========================================================

    void handlePress();

    void handleRelease();


    // ========================================================
    // Listener notifications
    // ========================================================

    void notifyPress();

    void notifyRelease();
};