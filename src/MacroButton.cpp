#include "MacroButton.h"


MacroButton::MacroButton(IButtonDriver& driver)
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

            if (clickMacro == nullptr)
                return;

            if (keyboardDriver == nullptr)
                return;

            clickMacro->execute(*keyboardDriver);
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

            if (doubleClickMacro == nullptr)
                return;

            if (keyboardDriver == nullptr)
                return;

            doubleClickMacro->execute(*keyboardDriver);
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

            multiClickMacro->execute(*keyboardDriver);
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

            longPressStartMacro->execute(*keyboardDriver);
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

            longPressMacro->execute(*keyboardDriver);
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

            longPressStopMacro->execute(*keyboardDriver);
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
// Gesture configuration
// ============================================================

MacroButton& MacroButton::onClick(
    IMacro& macro)
{
    clickMacro = &macro;

    return *this;
}


MacroButton& MacroButton::onDoubleClick(
    IMacro& macro)
{
    doubleClickMacro = &macro;

    return *this;
}


MacroButton& MacroButton::onMultiClick(
    IMacro& macro)
{
    multiClickMacro = &macro;

    return *this;
}


MacroButton& MacroButton::onLongPressStart(
    IMacro& macro)
{
    longPressStartMacro = &macro;

    return *this;
}


MacroButton& MacroButton::onLongPress(
    IMacro& macro)
{
    longPressMacro = &macro;

    return *this;
}


MacroButton& MacroButton::onLongPressStop(
    IMacro& macro)
{
    longPressStopMacro = &macro;

    return *this;
}


// ============================================================
// Button listener registration
// ============================================================

void MacroButton::addButtonListener(
    IButtonListener& listener)
{
    listeners.push_back(&listener);
}


// ============================================================
// Physical press
// ============================================================

void MacroButton::handlePress()
{
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

        listener->onButtonPress(*this);
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

        listener->onButtonRelease(*this);
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
     * Do not clear suppression immediately when a chord is released.
     *
     * OneButton can queue click/double-click/multi-click callbacks
     * after the physical release is detected. If we clear the flag
     * during the same release cycle, those queued events can still fire
     * and leak the individual button gestures after the chord action.
     *
     * Keep the suppression active until the next real physical press,
     * which is when a fresh gesture cycle begins.
     */
}


// ============================================================
// Suppression state
// ============================================================

bool MacroButton::gesturesSuppressed() const
{
    return gesturesSuppressedFlag;
}