#include "MacroButton.h"


MacroButton::MacroButton(IButtonDriver& driver)
    : driver(driver)
{
}


void MacroButton::begin(IKeyboardDriver& keyboard)
{
    this->keyboardDriver = &keyboard;

    driver.begin();

    driver.onClick([this]()
    {
        if (clickMacro == nullptr)
            return;

        if (keyboardDriver == nullptr)
            return;

        clickMacro->execute(*keyboardDriver);
    });

    driver.onDoubleClick([this]()
    {
        if (doubleClickMacro == nullptr)
            return;

        if (keyboardDriver == nullptr)
            return;

        doubleClickMacro->execute(*keyboardDriver);
    });

    driver.onMultiClick([this]()
    {
        if (multiClickMacro == nullptr)
            return;

        if (keyboardDriver == nullptr)
            return;

        multiClickMacro->execute(*keyboardDriver);
    });

    driver.onLongPressStart([this]()
    {
        if (longPressStartMacro == nullptr)
            return;

        if (keyboardDriver == nullptr)
            return;

        longPressStartMacro->execute(*keyboardDriver);
    });

    driver.onLongPressStop([this]()
    {
        if (longPressStopMacro == nullptr)
            return;

        if (keyboardDriver == nullptr)
            return;

        longPressStopMacro->execute(*keyboardDriver);
    });

    driver.onLongPress([this]()
    {
        if (longPressMacro == nullptr)
            return;

        if (keyboardDriver == nullptr)
            return;

        longPressMacro->execute(*keyboardDriver);
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