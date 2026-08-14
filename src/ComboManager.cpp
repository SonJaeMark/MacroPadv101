#include "ComboManager.h"

#include "IMacroButton.h"
#include "IMacro.h"

void ComboManager::addCombo(
    const std::vector<IMacroButton*>& buttons,
    IMacro& macro)
{
    Combo combo;
    combo.buttons = buttons;
    combo.macro = &macro;
    combo.executed = false;

    combos.push_back(std::move(combo));
}

void ComboManager::update(IKeyboardDriver& driver)
{
    Serial.println("----- Combo Update -----");

    for (Combo& combo : combos)
    {
        bool allPressed = true;

        int index = 0;

        for (IMacroButton* button : combo.buttons)
        {
            bool pressed = false;

            if (button != nullptr)
                pressed = button->isPressed();

            Serial.print("Button ");
            Serial.print(index++);
            Serial.print(" = ");
            Serial.println(pressed ? "PRESSED" : "RELEASED");

            if (!pressed)
            {
                allPressed = false;
            }
        }

        Serial.print("All pressed = ");
        Serial.println(allPressed ? "YES" : "NO");

        if (allPressed)
        {
            Serial.println("Combo detected");

            if (!combo.executed && combo.macro != nullptr)
            {
                Serial.println("Executing combo");

                combo.macro->execute(driver);
                combo.executed = true;
            }
        }
        else
        {
            combo.executed = false;
        }
    }

    Serial.println();
}