#include "OneButtonDriver.h"

#include <Arduino.h>


OneButtonDriver::OneButtonDriver(uint8_t pin)
    : pin(pin),
      button(pin, true, true)
{
}


void OneButtonDriver::begin()
{
    /*
     * OneButton handles physical press detection.
     *
     * There is no attachRelease() in the installed
     * OneButton library, so release detection is
     * handled manually in tick().
     */

    button.attachPress(
        handlePress,
        static_cast<void*>(this)
    );
}


void OneButtonDriver::tick()
{
    /*
     * Let OneButton process its normal gestures.
     */
    button.tick();


    /*
     * Detect physical release ourselves.
     *
     * The button is configured as active LOW:
     *
     * LOW  = pressed
     * HIGH = released
     *
     * Only generate the release event when we were
     * previously pressed.
     */
    if (pressed && digitalRead(pin) == HIGH)
    {
        pressed = false;

        if (releaseCallback)
            releaseCallback();
    }
}


bool OneButtonDriver::isPressed() const
{
    return pressed;
}


// ============================================================
// Physical press
// ============================================================

void OneButtonDriver::onPress(
    const std::function<void()>& callback)
{
    pressCallback = callback;
}


// ============================================================
// Physical release
// ============================================================

void OneButtonDriver::onRelease(
    const std::function<void()>& callback)
{
    releaseCallback = callback;
}


// ============================================================
// Click
// ============================================================

void OneButtonDriver::onClick(
    const std::function<void()>& callback)
{
    clickCallback = callback;

    button.attachClick(
        handleClick,
        static_cast<void*>(this)
    );
}


// ============================================================
// Double click
// ============================================================

void OneButtonDriver::onDoubleClick(
    const std::function<void()>& callback)
{
    doubleClickCallback = callback;

    button.attachDoubleClick(
        handleDoubleClick,
        static_cast<void*>(this)
    );
}


// ============================================================
// Multi click
// ============================================================

void OneButtonDriver::onMultiClick(
    const std::function<void()>& callback)
{
    multiClickCallback = callback;

    button.attachMultiClick(
        handleMultiClick,
        static_cast<void*>(this)
    );
}


// ============================================================
// Long press start
// ============================================================

void OneButtonDriver::onLongPressStart(
    const std::function<void()>& callback)
{
    longPressStartCallback = callback;

    button.attachLongPressStart(
        handleLongPressStart,
        static_cast<void*>(this)
    );
}


// ============================================================
// Long press stop
// ============================================================

void OneButtonDriver::onLongPressStop(
    const std::function<void()>& callback)
{
    longPressStopCallback = callback;

    button.attachLongPressStop(
        handleLongPressStop,
        static_cast<void*>(this)
    );
}


// ============================================================
// During long press
// ============================================================

void OneButtonDriver::onLongPress(
    const std::function<void()>& callback)
{
    longPressCallback = callback;

    button.attachDuringLongPress(
        handleLongPress,
        static_cast<void*>(this)
    );
}


// ============================================================
// Internal physical press handler
// ============================================================

void OneButtonDriver::handlePress(void* parameter)
{
    auto* driver =
        static_cast<OneButtonDriver*>(parameter);

    /*
     * Prevent duplicate press notifications.
     */
    if (driver->pressed)
        return;

    driver->pressed = true;

    if (driver->pressCallback)
        driver->pressCallback();
}


// ============================================================
// Click
// ============================================================

void OneButtonDriver::handleClick(void* parameter)
{
    auto* driver =
        static_cast<OneButtonDriver*>(parameter);

    if (driver->clickCallback)
        driver->clickCallback();
}


// ============================================================
// Double click
// ============================================================

void OneButtonDriver::handleDoubleClick(void* parameter)
{
    auto* driver =
        static_cast<OneButtonDriver*>(parameter);

    if (driver->doubleClickCallback)
        driver->doubleClickCallback();
}


// ============================================================
// Multi click
// ============================================================

void OneButtonDriver::handleMultiClick(void* parameter)
{
    auto* driver =
        static_cast<OneButtonDriver*>(parameter);

    if (driver->multiClickCallback)
        driver->multiClickCallback();
}


// ============================================================
// Long press start
// ============================================================

void OneButtonDriver::handleLongPressStart(void* parameter)
{
    auto* driver =
        static_cast<OneButtonDriver*>(parameter);

    if (driver->longPressStartCallback)
        driver->longPressStartCallback();
}


// ============================================================
// Long press stop
// ============================================================

void OneButtonDriver::handleLongPressStop(void* parameter)
{
    auto* driver =
        static_cast<OneButtonDriver*>(parameter);

    if (driver->longPressStopCallback)
        driver->longPressStopCallback();
}


// ============================================================
// During long press
// ============================================================

void OneButtonDriver::handleLongPress(void* parameter)
{
    auto* driver =
        static_cast<OneButtonDriver*>(parameter);

    if (driver->longPressCallback)
        driver->longPressCallback();
}