#pragma once

#include <BleKeyboard.h>
#include <string>

#include "IKeyboardDriver.h"

class BleKeyboardDriver : public IKeyboardDriver
{
private:
    BleKeyboard keyboard;

public:
    // Declare only
    BleKeyboardDriver();

    BleKeyboardDriver(
        const std::string& deviceName,
        const std::string& manufacturer,
        uint8_t batteryLevel);

    void begin() override;

    bool connected() const override;

    void press(uint8_t key) override;
    void release(uint8_t key) override;
    void click(uint8_t key) override;
    void releaseAll() override;
    void type(const std::string& text) override;
};