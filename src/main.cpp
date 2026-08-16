#include <Arduino.h>

#include "ota.h"

#include "BleKeyboardDriver.h"
#include "OneButtonDriver.h"
#include "MacroButton.h"
#include "Macro.h"
#include "CycleMacro.h"
#include "ChordManager.h"


// ============================================================
// Keyboard
// ============================================================

BleKeyboardDriver keyboard(
    "MacroPad Cycle + Chord Test",
    "SonJaeMark",
    100
);


// ============================================================
// Drivers
// ============================================================

OneButtonDriver driver0(0);
OneButtonDriver driver1(1);


// ============================================================
// Buttons
// ============================================================

MacroButton button0(driver0);
MacroButton button1(driver1);


// ============================================================
// Chord manager
// ============================================================

ChordManager chordManager;


// ============================================================
// Button 0 Cycle Macros
// ============================================================

Macro bzm;
Macro bcb;
Macro bcl;
Macro bmv;
Macro bds;
Macro bhp;


// ============================================================
// Button 0 Cycle
// ============================================================

CycleMacro brushCycle;


// ============================================================
// Button 0 additional gestures
// ============================================================

Macro ctrlZ;
Macro brush;


// ============================================================
// Button 1 gesture macros
// ============================================================

Macro b1Click;
Macro b1Double;
Macro b1Multi;
Macro b1Start;
Macro b1Hold;
Macro b1Stop;


// ============================================================
// Chord macro
// ============================================================

Macro shiftD;


void setup()
{
    Serial.begin(115200);

    delay(500);


    Serial.println();
    Serial.println("==============================");
    Serial.println(" CYCLE + CHORD TEST");
    Serial.println("==============================");


    // ========================================================
    // OTA
    // ========================================================

    begin();


    // ========================================================
    // Keyboard
    // ========================================================

    keyboard.begin();


    // ========================================================
    // Button 0 Cycle Macros
    // ========================================================

    /*
     * B + Z + M
     */
    bzm
        .click('b')
        .click('z')
        .click('m');


    /*
     * B + C + B
     */
    bcb
        .click('b')
        .click('c')
        .click('b');


    /*
     * B + C + L
     */
    bcl
        .click('b')
        .click('c')
        .click('l');


    /*
     * B + M + V
     */
    bmv
        .click('b')
        .click('m')
        .click('v');


    /*
     * B + D + S
     */
    bds
        .click('b')
        .click('d')
        .click('s');


    /*
     * B + H + P
     */
    bhp
        .click('b')
        .click('h')
        .click('p');


    // ========================================================
    // Build Cycle
    // ========================================================

    brushCycle
        .add(bzm)
        .add(bcb)
        .add(bcl)
        .add(bmv)
        .add(bds)
        .add(bhp);
    

    // ========================================================
    // Button 0 additional gestures
    // ========================================================

    /*
     * Multi-click:
     *
     * CTRL + Z
     */
    ctrlZ
        .press(KEY_LEFT_CTRL)
        .click('z')
        .release(KEY_LEFT_CTRL);


    /*
     * Long-press start:
     *
     * B
     */
    brush
        .click('b');


    // ========================================================
    // Button 0
    // ========================================================

    /*
     * Single click
     *
     * Cycle FORWARD
     */
    button0.onClick(
        brushCycle
    );


    /*
     * Double click
     *
     * Cycle BACKWARD
     */
    button0.onDoubleClick(
        brushCycle
    );


    /*
     * Multi click
     *
     * CTRL + Z
     */
    button0.onMultiClick(
        ctrlZ
    );


    /*
     * Long press start
     *
     * B
     */
    button0.onLongPressStart(
        brush
    );


    /*
     * During long press
     *
     * Nothing
     */


    /*
     * Long press stop
     *
     * Nothing
     */


    // ========================================================
    // Button 1 gesture macros
    // ========================================================

    /*
     * These are normal individual button gestures.
     */

    b1Click.typeText("BUTTON1 CLICK");

    b1Double.typeText("BUTTON1 DOUBLE");

    b1Multi.typeText("BUTTON1 MULTI");

    b1Start.typeText("BUTTON1 START");

    b1Hold.typeText("*");

    b1Stop.typeText("BUTTON1 STOP");


    // ========================================================
    // Button 1
    // ========================================================

    button1
        .onClick(b1Click)
        .onDoubleClick(b1Double)
        .onMultiClick(b1Multi)
        .onLongPressStart(b1Start)
        .onLongPress(b1Hold)
        .onLongPressStop(b1Stop);


    // ========================================================
    // Initialize buttons
    // ========================================================

    button0.begin(keyboard);

    button1.begin(keyboard);


    // ========================================================
    // Register ChordManager listeners
    // ========================================================

    button0.addButtonListener(
        chordManager
    );

    button1.addButtonListener(
        chordManager
    );


    // ========================================================
    // Chord macro
    // ========================================================

    shiftD
        .press(KEY_LEFT_SHIFT)
        .click('d')
        .release(KEY_LEFT_SHIFT);


    // ========================================================
    // Register chord
    // ========================================================

    chordManager.addChord(
    {
        &button0,
        &button1
    },
    shiftD);


    // ========================================================
    // Test information
    // ========================================================

    Serial.println();
    Serial.println("==============================");
    Serial.println(" BUTTON 0");
    Serial.println("==============================");

    Serial.println("CLICK       = Cycle FORWARD");
    Serial.println("DOUBLE      = Cycle BACKWARD");
    Serial.println("MULTI       = CTRL + Z");
    Serial.println("LONG START  = B");
    Serial.println("LONG HOLD   = NOTHING");
    Serial.println("LONG STOP   = NOTHING");


    Serial.println();
    Serial.println("==============================");
    Serial.println(" CYCLE");
    Serial.println("==============================");

    Serial.println("0 = BZM");
    Serial.println("1 = BCB");
    Serial.println("2 = BCL");
    Serial.println("3 = BMV");
    Serial.println("4 = BDS");
    Serial.println("5 = BHP");


    Serial.println();
    Serial.println("==============================");
    Serial.println(" BUTTON 1");
    Serial.println("==============================");

    Serial.println("CLICK       = BUTTON1 CLICK");
    Serial.println("DOUBLE      = BUTTON1 DOUBLE");
    Serial.println("MULTI       = BUTTON1 MULTI");
    Serial.println("LONG START  = BUTTON1 START");
    Serial.println("LONG HOLD   = *");
    Serial.println("LONG STOP   = BUTTON1 STOP");


    Serial.println();
    Serial.println("==============================");
    Serial.println(" CHORD");
    Serial.println("==============================");

    Serial.println("BUTTON0 + BUTTON1 = SHIFT + D");


    Serial.println();
    Serial.println("==============================");
    Serial.println(" READY");
    Serial.println("==============================");
    Serial.println();
}


void loop()
{
    // ========================================================
    // OTA
    // ========================================================

    update();


    // ========================================================
    // Button processing
    // ========================================================

    button0.tick();

    button1.tick();


    // ========================================================
    // Chord processing
    // ========================================================

    chordManager.update(
        keyboard
    );
}