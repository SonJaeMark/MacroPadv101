#pragma once

#include <cstdint>
#include <string>

class IKeyboardDriver
{
public:
    virtual ~IKeyboardDriver() = default;

    virtual void begin() = 0;

    virtual bool connected() const = 0;

    virtual void press(uint8_t key) = 0;
    virtual void release(uint8_t key) = 0;
    virtual void click(uint8_t key) = 0;
    virtual void releaseAll() = 0;
    virtual void type(const std::string& text) = 0;
};