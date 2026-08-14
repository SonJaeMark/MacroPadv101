#include "OneButtonDriver.h"
#include <OneButton.h>

OneButtonDriver::OneButtonDriver(uint8_t pin)
    : pin(pin),
      button(pin, true, true)
{
}


void OneButtonDriver::begin()
{
    // Internal only: track the physical button state.
    button.attachPress(
        handlePress,
        static_cast<void*>(this)
    );
}


void OneButtonDriver::tick()
{
    button.tick();
}


bool OneButtonDriver::isPressed() const
{
    return pressed;
}


void OneButtonDriver::onClick(
    const std::function<void()>& callback)
{
    clickCallback = callback;

    button.attachClick(
        handleClick,
        static_cast<void*>(this)
    );
}


void OneButtonDriver::onDoubleClick(
    const std::function<void()>& callback)
{
    doubleClickCallback = callback;

    button.attachDoubleClick(
        handleDoubleClick,
        static_cast<void*>(this)
    );
}


void OneButtonDriver::onMultiClick(
    const std::function<void()>& callback)
{
    multiClickCallback = callback;

    button.attachMultiClick(
        handleMultiClick,
        static_cast<void*>(this)
    );
}


void OneButtonDriver::onLongPressStart(
    const std::function<void()>& callback)
{
    longPressStartCallback = callback;

    button.attachLongPressStart(
        handleLongPressStart,
        static_cast<void*>(this)
    );
}


void OneButtonDriver::onLongPressStop(
    const std::function<void()>& callback)
{
    longPressStopCallback = callback;

    button.attachLongPressStop(
        handleLongPressStop,
        static_cast<void*>(this)
    );
}


void OneButtonDriver::onLongPress(
    const std::function<void()>& callback)
{
    longPressCallback = callback;

    button.attachDuringLongPress(
        handleLongPress,
        static_cast<void*>(this)
    );
}


/*
 * Static callback bridges
 */

void OneButtonDriver::handlePress(void* parameter)
{
    auto* driver = static_cast<OneButtonDriver*>(parameter);

    driver->pressed = true;
}


void OneButtonDriver::handleClick(void* parameter)
{
    auto* driver = static_cast<OneButtonDriver*>(parameter);

    driver->pressed = false;

    if (driver->clickCallback)
        driver->clickCallback();
}


void OneButtonDriver::handleDoubleClick(void* parameter)
{
    auto* driver = static_cast<OneButtonDriver*>(parameter);

    driver->pressed = false;

    if (driver->doubleClickCallback)
        driver->doubleClickCallback();
}


void OneButtonDriver::handleMultiClick(void* parameter)
{
    auto* driver = static_cast<OneButtonDriver*>(parameter);

    driver->pressed = false;

    if (driver->multiClickCallback)
        driver->multiClickCallback();
}


void OneButtonDriver::handleLongPressStart(void* parameter)
{
    auto* driver = static_cast<OneButtonDriver*>(parameter);

    // already true from handlePress()

    if (driver->longPressStartCallback)
        driver->longPressStartCallback();
}


void OneButtonDriver::handleLongPressStop(void* parameter)
{
    auto* driver = static_cast<OneButtonDriver*>(parameter);

    driver->pressed = false;

    if (driver->longPressStopCallback)
        driver->longPressStopCallback();
}


void OneButtonDriver::handleLongPress(void* parameter)
{
    auto* driver = static_cast<OneButtonDriver*>(parameter);

    if (driver->longPressCallback)
        driver->longPressCallback();
}
