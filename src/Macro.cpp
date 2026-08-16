#include "Macro.h"

#include <Arduino.h>

Macro& Macro::press(uint8_t key)
{
    actions.push_back(makePress(key));
    return *this;
}

Macro& Macro::release(uint8_t key)
{
    actions.push_back(makeRelease(key));
    return *this;
}

Macro& Macro::click(uint8_t key)
{
    actions.push_back(makeClick(key));
    return *this;
}

Macro& Macro::delay(uint32_t ms)
{
    actions.push_back(makeDelay(ms));
    return *this;
}

Macro& Macro::releaseAll()
{
    actions.push_back(makeReleaseAll());
    return *this;
}

Macro& Macro::typeText(const std::string& text)
{
    actions.push_back(makeTypeText(text));
    return *this;
}

Macro& Macro::callback(const std::function<void()>& fn)
{
    actions.push_back(makeCallback(fn));
    return *this;
}

// void Macro::execute(IKeyboardDriver& driver)
// {
//     for (const Action& action : actions)
//     {
//         switch (action.type)
//         {
//         case ActionType::PRESS:
//             driver.press(action.key);
//             break;

//         case ActionType::RELEASE:
//             driver.release(action.key);
//             break;

//         case ActionType::CLICK:
//             driver.click(action.key);
//             break;

//         case ActionType::RELEASE_ALL:
//             driver.releaseAll();
//             break;

//         case ActionType::DELAY:
//             ::delay(action.delay);
//             break;

//         case ActionType::TYPE_TEXT:
//             driver.type(action.text);
//             break;

//         case ActionType::CALLBACK:
//             if (action.callback)
//             {
//                 action.callback();
//             }
//             break;
//         }
//     }
// }

void Macro::execute(IKeyboardDriver& driver)
{
    Serial.println("===== MACRO EXECUTE =====");

    int index = 0;

    for (const Action& action : actions)
    {
        Serial.print("ACTION ");
        Serial.print(index++);
        Serial.print(" = ");

        switch (action.type)
        {
            case ActionType::PRESS:
                Serial.println("PRESS");

                Serial.print("KEY = ");
                Serial.println(action.key);

                driver.press(action.key);
                break;


            case ActionType::RELEASE:
                Serial.println("RELEASE");

                Serial.print("KEY = ");
                Serial.println(action.key);

                driver.release(action.key);
                break;


            case ActionType::CLICK:
                Serial.println("CLICK");

                Serial.print("KEY = ");
                Serial.println(action.key);

                driver.click(action.key);
                break;


            case ActionType::RELEASE_ALL:
                Serial.println("RELEASE_ALL");

                driver.releaseAll();
                break;


            case ActionType::DELAY:
                Serial.println("DELAY");

                delay(action.delay);
                break;


            case ActionType::TYPE_TEXT:
                Serial.println("TYPE_TEXT");

                driver.type(action.text);
                break;


            case ActionType::CALLBACK:
                Serial.println("CALLBACK");

                if (action.callback)
                    action.callback();

                break;
        }
    }

    Serial.println("=========================");
}