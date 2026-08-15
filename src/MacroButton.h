#pragma once

#include <vector>

#include "IMacroButton.h"
#include "IButtonDriver.h"
#include "IButtonListener.h"
#include "IMacro.h"
#include "IKeyboardDriver.h"

class MacroButton : public IMacroButton
{
public:
    explicit MacroButton(IButtonDriver& driver);

    void begin(IKeyboardDriver& keyboard);
    void tick() override;

    bool isPressed() const override;

    void addButtonListener(
        IButtonListener& listener) override;

    MacroButton& onClick(IMacro& macro);
    MacroButton& onDoubleClick(IMacro& macro);
    MacroButton& onMultiClick(IMacro& macro);

    MacroButton& onLongPressStart(IMacro& macro);
    MacroButton& onLongPressStop(IMacro& macro);
    MacroButton& onLongPress(IMacro& macro);

private:
    IButtonDriver& driver;

    IKeyboardDriver* keyboardDriver = nullptr;

    std::vector<IButtonListener*> listeners;

    IMacro* clickMacro = nullptr;
    IMacro* doubleClickMacro = nullptr;
    IMacro* multiClickMacro = nullptr;

    IMacro* longPressStartMacro = nullptr;
    IMacro* longPressStopMacro = nullptr;
    IMacro* longPressMacro = nullptr;

    void notifyButtonPress();
    void notifyButtonRelease();
};