#pragma once

#include <vector>

#include "IMacroButton.h"
#include "IButtonDriver.h"
#include "IMacro.h"
#include "IKeyboardDriver.h"
#include "IButtonListener.h"


class MacroButton : public IMacroButton
{
public:

    explicit MacroButton(IButtonDriver& driver);


    // ========================================================
    // Lifecycle
    // ========================================================

    void begin(IKeyboardDriver& keyboard);

    void tick() override;


    // ========================================================
    // State
    // ========================================================

    bool isPressed() const override;


    // ========================================================
    // Gesture configuration
    // ========================================================

    MacroButton& onClick(IMacro& macro);

    MacroButton& onDoubleClick(IMacro& macro);

    MacroButton& onMultiClick(IMacro& macro);

    MacroButton& onLongPressStart(IMacro& macro);

    MacroButton& onLongPress(IMacro& macro);

    MacroButton& onLongPressStop(IMacro& macro);


    // ========================================================
    // Button listeners
    // ========================================================

    void addButtonListener(
        IButtonListener& listener);


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
    // Gesture macros
    // ========================================================

    IMacro* clickMacro = nullptr;

    IMacro* doubleClickMacro = nullptr;

    IMacro* multiClickMacro = nullptr;

    IMacro* longPressStartMacro = nullptr;

    IMacro* longPressMacro = nullptr;

    IMacro* longPressStopMacro = nullptr;


    // ========================================================
    // Button listeners
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