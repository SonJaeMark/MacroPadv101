#include <Arduino.h>

#include "ota.h"

#include "BleKeyboardDriver.h"
#include "OneButtonDriver.h"
#include "MacroButton.h"
#include "Macro.h"
#include "IButtonListener.h"


// ============================================================
// Keyboard
// ============================================================

BleKeyboardDriver keyboard(
    "MacroPad Physical Test",
    "SonJaeMark",
    100
);


// ============================================================
// Physical drivers
// ============================================================

OneButtonDriver driver0(0);
OneButtonDriver driver1(1);


// ============================================================
// Macro buttons
// ============================================================

MacroButton button0(driver0);
MacroButton button1(driver1);


// ============================================================
// Test listener
// ============================================================

class DebugButtonListener : public IButtonListener
{
public:

    void onButtonPress(IMacroButton& button) override
    {
        if (&button == button0Reference)
        {
            Serial.println("BUTTON0 PRESS");
        }
        else if (&button == button1Reference)
        {
            Serial.println("BUTTON1 PRESS");
        }
    }

    void onButtonRelease(IMacroButton& button) override
    {
        if (&button == button0Reference)
        {
            Serial.println("BUTTON0 RELEASE");
        }
        else if (&button == button1Reference)
        {
            Serial.println("BUTTON1 RELEASE");
        }
    }

    void setButtons(
        IMacroButton& button0,
        IMacroButton& button1)
    {
        button0Reference = &button0;
        button1Reference = &button1;
    }

private:

    IMacroButton* button0Reference = nullptr;
    IMacroButton* button1Reference = nullptr;
};

// ============================================================
// Listener
// ============================================================

DebugButtonListener debugListener;


// ============================================================
// Button 0 macros
// ============================================================

Macro b0Click;
Macro b0Double;
Macro b0Multi;
Macro b0Start;
Macro b0Hold;
Macro b0Stop;


// ============================================================
// Button 1 macros
// ============================================================

Macro b1Click;
Macro b1Double;
Macro b1Multi;
Macro b1Start;
Macro b1Hold;
Macro b1Stop;


void setup()
{
    Serial.begin(115200);

    delay(500);

    Serial.println();
    Serial.println("==============================");
    Serial.println(" PHYSICAL BUTTON TEST");
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
    // Button 0 macros
    // ========================================================

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


    // ========================================================
    // Button 1 macros
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
    // Initialize buttons
    // ========================================================

    button0.begin(keyboard);
    button1.begin(keyboard);


    // ========================================================
    // Register physical listener
    // ========================================================

    debugListener.setButtons(
        button0,
        button1
    );

    button0.addButtonListener(debugListener);
    button1.addButtonListener(debugListener);


    Serial.println();
    Serial.println("Ready.");
    Serial.println();
}


void loop()
{
    // OTA
    update();


    // Button processing
    button0.tick();
    button1.tick();
}