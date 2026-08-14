#pragma once

#include <vector>

#include "IMacro.h"
#include "Action.h"

class Macro : public IMacro
{
private:
    std::vector<Action> actions;

public:
    Macro& press(uint8_t key);
    Macro& release(uint8_t key);
    Macro& click(uint8_t key);
    Macro& delay(uint32_t ms);
    Macro& releaseAll();
    Macro& typeText(const std::string& text);
    Macro& callback(const std::function<void()>& fn);

    void execute(IKeyboardDriver& driver) override;
};