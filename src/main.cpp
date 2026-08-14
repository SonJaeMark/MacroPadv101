#include <Arduino.h>

#include "ota.h"

#include "BleKeyboardDriver.h"
#include "OneButtonDriver.h"
#include "MacroButton.h"
#include "Macro.h"
#include "ComboManager.h"

BleKeyboardDriver keyboard("MacroPad Test", "SonJaeMark", 100);

// Drivers
OneButtonDriver driver0(0);
OneButtonDriver driver1(1);

// Buttons
MacroButton button0(driver0);
MacroButton button1(driver1);

// Combo Manager
ComboManager comboManager;

// ---------------- Button 0 ----------------

Macro b0Click;
Macro b0Double;
Macro b0Multi;
Macro b0Start;
Macro b0Hold;
Macro b0Stop;

// ---------------- Button 1 ----------------

Macro b1Click;
Macro b1Double;
Macro b1Multi;
Macro b1Start;
Macro b1Hold;
Macro b1Stop;

// ---------------- Combo ----------------

Macro comboMacro;

void setup()
{
    begin();

    keyboard.begin();

    // ---------------- Button 0 ----------------

    b0Click.typeText("BUTTON0 CLICK");
    b0Double.typeText("BUTTON0 DOUBLE");
    b0Multi.typeText("BUTTON0 MULTI");
    b0Start.typeText("BUTTON0 START");
    b0Hold.typeText(".");
    b0Stop.typeText("BUTTON0 STOP");

    button0
        .onClick(b0Click)
        .onDoubleClick(b0Double)
        .onMultiClick(b0Multi)
        .onLongPressStart(b0Start)
        .onLongPress(b0Hold)
        .onLongPressStop(b0Stop);

    // ---------------- Button 1 ----------------

    b1Click.typeText("BUTTON1 CLICK");
    b1Double.typeText("BUTTON1 DOUBLE");
    b1Multi.typeText("BUTTON1 MULTI");
    b1Start.typeText("BUTTON1 START");
    b1Hold.typeText("*");
    b1Stop.typeText("BUTTON1 STOP");

    button1
        .onClick(b1Click)
        .onDoubleClick(b1Double)
        .onMultiClick(b1Multi)
        .onLongPressStart(b1Start)
        .onLongPress(b1Hold)
        .onLongPressStop(b1Stop);

    // Initialize buttons
    button0.begin(keyboard);
    button1.begin(keyboard);

    // ---------------- Combo ----------------

    comboMacro
        .press(KEY_LEFT_SHIFT)
        .click('D')
        .releaseAll();

    comboManager.addCombo(
    {
        &button0,
        &button1
    },
    comboMacro);
}

void loop()
{
    update();

    button0.tick();
    button1.tick();

    comboManager.update(keyboard);
}