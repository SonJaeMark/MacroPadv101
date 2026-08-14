
#pragma once

#include <vector>

class IMacroButton;
class IMacro;
class IKeyboardDriver;

struct Combo
{
    std::vector<IMacroButton*> buttons;

    IMacro* macro = nullptr;

    bool executed = false;
};


class IComboManager
{
public:
    virtual ~IComboManager() = default;

    virtual void addCombo(
        const std::vector<IMacroButton*>& buttons,
        IMacro& macro) = 0;

    virtual void update(IKeyboardDriver& driver) = 0;
};