#pragma once

#include <functional>

class IButtonDriver
{
public:
    virtual ~IButtonDriver() = default;

    // Lifecycle
    virtual void begin() = 0;
    virtual void tick() = 0;

    // State
    virtual bool isPressed() const = 0;

    // Events

    virtual void onClick(const std::function<void()>& callback) = 0;

    virtual void onDoubleClick(const std::function<void()>& callback) = 0;

    virtual void onMultiClick(const std::function<void()>& callback) = 0;

    virtual void onLongPressStart(
        const std::function<void()>& callback) = 0;

    virtual void onLongPressStop(
        const std::function<void()>& callback) = 0;

    virtual void onLongPress(
        const std::function<void()>& callback) = 0;

};