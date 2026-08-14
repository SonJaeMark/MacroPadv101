#pragma once

#include <Arduino.h>

#include "IComboManager.h"

class ComboManager : public IComboManager
{
private:

    std::vector<Combo> combos;

public:

    void addCombo(
        const std::vector<IMacroButton*>& buttons,
        IMacro& macro) override;

    void update(IKeyboardDriver& driver) override;
};