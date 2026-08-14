#pragma once

#include <cstdint>
#include <functional>
#include <OneButton.h>

#include "IButtonDriver.h"

class OneButtonDriver : public IButtonDriver
{
public:
    explicit OneButtonDriver(uint8_t pin);

    void begin() override;
    void tick() override;

    bool isPressed() const override;

    void onClick(
        const std::function<void()>& callback) override;

    void onDoubleClick(
        const std::function<void()>& callback) override;

    void onMultiClick(
        const std::function<void()>& callback) override;

    void onLongPressStart(
        const std::function<void()>& callback) override;

    void onLongPressStop(
        const std::function<void()>& callback) override;

    void onLongPress(
        const std::function<void()>& callback) override;

private:
    uint8_t pin;

    bool pressed = false;

    OneButton button;

    std::function<void()> clickCallback;
    std::function<void()> doubleClickCallback;
    std::function<void()> multiClickCallback;
    std::function<void()> longPressStartCallback;
    std::function<void()> longPressStopCallback;
    std::function<void()> longPressCallback;
    std::function<void()> idleCallback;
    
    static void handlePress(void* parameter);

    static void handleClick(void* parameter);

    static void handleDoubleClick(void* parameter);

    static void handleMultiClick(void* parameter);

    static void handleLongPressStart(void* parameter);

    static void handleLongPressStop(void* parameter);

    static void handleLongPress(void* parameter);

};