#include <Arduino.h>

#include "ota.h"

#include "BleKeyboardDriver.h"
#include "OneButtonDriver.h"
#include "MacroButton.h"
#include "Macro.h"
#include "CycleMacro.h"
#include "MacroPad.h"


// ============================================================
// MacroPad
// ============================================================

BleKeyboardDriver keyboard(
    "MacroPad Cycle + Chord Test",
    "SonJaeMark",
    100
);

MacroPad pad(keyboard);


// ============================================================
// Button Drivers
// ============================================================

OneButtonDriver driver0(0);
OneButtonDriver driver1(1);


// ============================================================
// Buttons
// ============================================================

MacroButton button0(driver0);
MacroButton button1(driver1);


// ============================================================
// Macros
// ============================================================

Macro bzm;
Macro bcb;
Macro bcl;
Macro bmv;
Macro bds;
Macro bhp;

CycleMacro brushCycle;

Macro ctrlZ;
Macro brush;

Macro b1Click;
Macro b1Double;
Macro b1Multi;
Macro b1Start;
Macro b1Hold;
Macro b1Stop;

Macro shiftD;

void setup()
{
    Serial.begin(115200);

    delay(500);

    begin();


    // ========================================================
    // Button 0 Cycle
    // ========================================================

    bzm
        .click('b')
        .click('z')
        .click('m');

    bcb
        .click('b')
        .click('c')
        .click('b');

    bcl
        .click('b')
        .click('c')
        .click('l');

    bmv
        .click('b')
        .click('m')
        .click('v');

    bds
        .click('b')
        .click('d')
        .click('s');

    bhp
        .click('b')
        .click('h')
        .click('p');


    brushCycle
        .add(bzm)
        .add(bcb)
        .add(bcl)
        .add(bmv)
        .add(bds)
        .add(bhp);


    // ========================================================
    // Button 0
    // ========================================================

    ctrlZ
        .press(KEY_LEFT_CTRL)
        .click('z')
        .release(KEY_LEFT_CTRL);

    brush
        .click('b');


    button0
        .onClick(brushCycle)
        .onDoubleClick(brushCycle)
        .onMultiClick(ctrlZ)
        .onLongPressStart(brush);


    // ========================================================
    // Button 1
    // ========================================================

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


    // ========================================================
    // Chord
    // ========================================================

    shiftD
        .press(KEY_LEFT_SHIFT)
        .click('d')
        .release(KEY_LEFT_SHIFT);


    pad
        .add(button0)
        .add(button1)
        .chord(
            {
                &button0,
                &button1
            },
            shiftD
        );


    // ========================================================
    // Initialize everything
    // ========================================================

    pad.begin();
}

void loop()
{
    update();

    pad.tick();
}