#include "MacroButton.h"


MacroButton::MacroButton(IButtonDriver& driver)
    : driver(driver)
{
}


void MacroButton::begin(IKeyboardDriver& keyboard)
{
    keyboardDriver = &keyboard;

    driver.begin();

    // ========================================================
    // Physical button events
    // ========================================================

    driver.onPress([this]()
    {
        notifyButtonPress();
    });

    driver.onRelease([this]()
    {
        notifyButtonRelease();
    });

    // ========================================================
    // Click
    // ========================================================

    driver.onClick([this]()
    {
        if (clickMacro == nullptr)
            return;

        if (keyboardDriver == nullptr)
            return;

        clickMacro->execute(*keyboardDriver);
    });

    // ========================================================
    // Double click
    // ========================================================

    driver.onDoubleClick([this]()
    {
        if (doubleClickMacro == nullptr)
            return;

        if (keyboardDriver == nullptr)
            return;

        doubleClickMacro->execute(*keyboardDriver);
    });

    // ========================================================
    // Multi click
    // ========================================================

    driver.onMultiClick([this]()
    {
        if (multiClickMacro == nullptr)
            return;

        if (keyboardDriver == nullptr)
            return;

        multiClickMacro->execute(*keyboardDriver);
    });

    // ========================================================
    // Long press start
    // ========================================================

    driver.onLongPressStart([this]()
    {
        if (longPressStartMacro == nullptr)
            return;

        if (keyboardDriver == nullptr)
            return;

        longPressStartMacro->execute(*keyboardDriver);
    });

    // ========================================================
    // Long press
    // ========================================================

    driver.onLongPress([this]()
    {
        if (longPressMacro == nullptr)
            return;

        if (keyboardDriver == nullptr)
            return;

        longPressMacro->execute(*keyboardDriver);
    });

    // ========================================================
    // Long press stop
    // ========================================================

    driver.onLongPressStop([this]()
    {
        if (longPressStopMacro == nullptr)
            return;

        if (keyboardDriver == nullptr)
            return;

        longPressStopMacro->execute(*keyboardDriver);
    });
}


void MacroButton::tick()
{
    driver.tick();
}


bool MacroButton::isPressed() const
{
    return driver.isPressed();
}


// ============================================================
// Button listeners
// ============================================================

void MacroButton::addButtonListener(
    IButtonListener& listener)
{
    listeners.push_back(&listener);
}


void MacroButton::notifyButtonPress()
{
    for (IButtonListener* listener : listeners)
    {
        if (listener == nullptr)
            continue;

        listener->onButtonPress(*this);
    }
}


void MacroButton::notifyButtonRelease()
{
    for (IButtonListener* listener : listeners)
    {
        if (listener == nullptr)
            continue;

        listener->onButtonRelease(*this);
    }
}


// ============================================================
// Macro assignments
// ============================================================

MacroButton& MacroButton::onClick(IMacro& macro)
{
    clickMacro = &macro;

    return *this;
}


MacroButton& MacroButton::onDoubleClick(IMacro& macro)
{
    doubleClickMacro = &macro;

    return *this;
}


MacroButton& MacroButton::onMultiClick(IMacro& macro)
{
    multiClickMacro = &macro;

    return *this;
}


MacroButton& MacroButton::onLongPressStart(IMacro& macro)
{
    longPressStartMacro = &macro;

    return *this;
}


MacroButton& MacroButton::onLongPressStop(IMacro& macro)
{
    longPressStopMacro = &macro;

    return *this;
}


MacroButton& MacroButton::onLongPress(IMacro& macro)
{
    longPressMacro = &macro;

    return *this;
}