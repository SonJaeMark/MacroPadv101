#include "BleKeyboardDriver.h"

BleKeyboardDriver::BleKeyboardDriver()
    : keyboard(
        "Default Device Name",
        "Defalut Manufacturer",
        100)
{
}

BleKeyboardDriver::BleKeyboardDriver(
    const std::string& deviceName,
    const std::string& manufacturer,
    uint8_t batteryLevel)
    : keyboard(
        deviceName,
        manufacturer,
        batteryLevel)
{
}

void BleKeyboardDriver::begin()
{
    keyboard.begin();
}

bool BleKeyboardDriver::connected() const
{
    return const_cast<BleKeyboard&>(keyboard).isConnected();
}

void BleKeyboardDriver::press(uint8_t key)
{
    if (!connected())
        return;

    keyboard.press(key);
}

void BleKeyboardDriver::release(uint8_t key)
{
    if (!connected())
        return;

    keyboard.release(key);
}

void BleKeyboardDriver::click(uint8_t key)
{
    if (!connected())
        return;

    keyboard.press(key);
    delay(50);
    keyboard.release(key);
}

void BleKeyboardDriver::releaseAll()
{
    if (!connected())
        return;

    keyboard.releaseAll();
}

void BleKeyboardDriver::type(const std::string& text)
{
    if (!connected())
        return;

    keyboard.print(text.c_str());
}