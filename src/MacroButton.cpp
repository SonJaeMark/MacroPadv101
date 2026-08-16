#include "MacroButton.h"


// ============================================================
// Constructor
// ============================================================

MacroButton::MacroButton(
    IButtonDriver& driver)
    : driver(driver)
{
}


// ============================================================
// Begin
// ============================================================

void MacroButton::begin(
    IKeyboardDriver& keyboard)
{
    keyboardDriver = &keyboard;

    driver.begin();


    // ========================================================
    // Physical press
    // ========================================================

    driver.onPress(
        [this]()
        {
            handlePress();
        }
    );


    // ========================================================
    // Physical release
    // ========================================================

    driver.onRelease(
        [this]()
        {
            handleRelease();
        }
    );


    // ========================================================
    // Click
    // ========================================================

    driver.onClick(
        [this]()
        {
            if (gesturesSuppressedFlag)
                return;

            if (keyboardDriver == nullptr)
                return;


            // ------------------------------------------------
            // CycleMacro has priority
            // ------------------------------------------------

            if (clickCycle != nullptr)
            {
                clickCycle->forwardExecute(
                    *keyboardDriver
                );

                return;
            }


            // ------------------------------------------------
            // Normal Macro
            // ------------------------------------------------

            if (clickMacro == nullptr)
                return;

            clickMacro->execute(
                *keyboardDriver
            );
        }
    );


    // ========================================================
    // Double click
    // ========================================================

    driver.onDoubleClick(
        [this]()
        {
            if (gesturesSuppressedFlag)
                return;

            if (keyboardDriver == nullptr)
                return;


            // ------------------------------------------------
            // CycleMacro goes BACKWARD
            // ------------------------------------------------

            if (doubleClickCycle != nullptr)
            {
                doubleClickCycle->backwardExecute(
                    *keyboardDriver
                );

                return;
            }


            // ------------------------------------------------
            // Normal Macro
            // ------------------------------------------------

            if (doubleClickMacro == nullptr)
                return;

            doubleClickMacro->execute(
                *keyboardDriver
            );
        }
    );


    // ========================================================
    // Multi click
    // ========================================================

    driver.onMultiClick(
        [this]()
        {
            if (gesturesSuppressedFlag)
                return;

            if (multiClickMacro == nullptr)
                return;

            if (keyboardDriver == nullptr)
                return;

            multiClickMacro->execute(
                *keyboardDriver
            );
        }
    );


    // ========================================================
    // Long press start
    // ========================================================

    driver.onLongPressStart(
        [this]()
        {
            if (gesturesSuppressedFlag)
                return;

            if (longPressStartMacro == nullptr)
                return;

            if (keyboardDriver == nullptr)
                return;

            longPressStartMacro->execute(
                *keyboardDriver
            );
        }
    );


    // ========================================================
    // Long press
    // ========================================================

    driver.onLongPress(
        [this]()
        {
            if (gesturesSuppressedFlag)
                return;

            if (longPressMacro == nullptr)
                return;

            if (keyboardDriver == nullptr)
                return;

            longPressMacro->execute(
                *keyboardDriver
            );
        }
    );


    // ========================================================
    // Long press stop
    // ========================================================

    driver.onLongPressStop(
        [this]()
        {
            if (gesturesSuppressedFlag)
                return;

            if (longPressStopMacro == nullptr)
                return;

            if (keyboardDriver == nullptr)
                return;

            longPressStopMacro->execute(
                *keyboardDriver
            );
        }
    );
}


// ============================================================
// Tick
// ============================================================

void MacroButton::tick()
{
    driver.tick();
}


// ============================================================
// State
// ============================================================

bool MacroButton::isPressed() const
{
    return driver.isPressed();
}


// ============================================================
// Normal Macro: Click
// ============================================================

MacroButton& MacroButton::onClick(
    IMacro& macro)
{
    clickMacro = &macro;

    clickCycle = nullptr;

    return *this;
}


// ============================================================
// Normal Macro: Double Click
// ============================================================

MacroButton& MacroButton::onDoubleClick(
    IMacro& macro)
{
    doubleClickMacro = &macro;

    doubleClickCycle = nullptr;

    return *this;
}


// ============================================================
// Normal Macro: Multi Click
// ============================================================

MacroButton& MacroButton::onMultiClick(
    IMacro& macro)
{
    multiClickMacro = &macro;

    return *this;
}


// ============================================================
// Normal Macro: Long Press Start
// ============================================================

MacroButton& MacroButton::onLongPressStart(
    IMacro& macro)
{
    longPressStartMacro = &macro;

    return *this;
}


// ============================================================
// Normal Macro: Long Press
// ============================================================

MacroButton& MacroButton::onLongPress(
    IMacro& macro)
{
    longPressMacro = &macro;

    return *this;
}


// ============================================================
// Normal Macro: Long Press Stop
// ============================================================

MacroButton& MacroButton::onLongPressStop(
    IMacro& macro)
{
    longPressStopMacro = &macro;

    return *this;
}


// ============================================================
// CycleMacro: Click = FORWARD
// ============================================================

MacroButton& MacroButton::onClick(
    CycleMacro& cycle)
{
    clickCycle = &cycle;

    clickMacro = nullptr;

    return *this;
}


// ============================================================
// CycleMacro: Double Click = BACKWARD
// ============================================================

MacroButton& MacroButton::onDoubleClick(
    CycleMacro& cycle)
{
    doubleClickCycle = &cycle;

    doubleClickMacro = nullptr;

    return *this;
}


// ============================================================
// Button listener registration
// ============================================================

void MacroButton::addButtonListener(
    IButtonListener& listener)
{
    listeners.push_back(
        &listener
    );
}


// ============================================================
// Physical press
// ============================================================

void MacroButton::handlePress()
{
    /*
     * A new physical press begins a fresh gesture cycle.
     *
     * If a previous chord suppressed this button,
     * clear suppression here.
     */
    if (gesturesSuppressedFlag)
        gesturesSuppressedFlag = false;

    notifyPress();
}


// ============================================================
// Physical release
// ============================================================

void MacroButton::handleRelease()
{
    notifyRelease();
}


// ============================================================
// Notify press
// ============================================================

void MacroButton::notifyPress()
{
    for (IButtonListener* listener : listeners)
    {
        if (listener == nullptr)
            continue;

        listener->onButtonPress(
            *this
        );
    }
}


// ============================================================
// Notify release
// ============================================================

void MacroButton::notifyRelease()
{
    for (IButtonListener* listener : listeners)
    {
        if (listener == nullptr)
            continue;

        listener->onButtonRelease(
            *this
        );
    }
}


// ============================================================
// Suppress gestures
// ============================================================

void MacroButton::suppressGestures()
{
    gesturesSuppressedFlag = true;
}


// ============================================================
// Release gesture suppression
// ============================================================

void MacroButton::releaseGestures()
{
    /*
     * Intentionally do nothing.
     *
     * OneButton may deliver the click/double-click/multi-click
     * callback after physical release.
     *
     * Suppression is therefore cleared on the next real
     * physical press in handlePress().
     */
}


// ============================================================
// Suppression state
// ============================================================

bool MacroButton::gesturesSuppressed() const
{
    return gesturesSuppressedFlag;
}