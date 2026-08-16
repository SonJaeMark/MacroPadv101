#pragma once

#include "IKeyboardDriver.h"
#include "IButtonListener.h"

class IMacroButton
{
public:
    virtual ~IMacroButton() = default;


    // ========================================================
    // Lifecycle
    // ========================================================

    virtual void begin(
        IKeyboardDriver& keyboard) = 0;

    virtual void tick() = 0;


    // ========================================================
    // State
    // ========================================================

    virtual bool isPressed() const = 0;


    // ========================================================
    // Button listeners
    // ========================================================

    virtual void addButtonListener(
        IButtonListener& listener) = 0;


    // ========================================================
    // Chord control
    // ========================================================

    virtual void suppressGestures() = 0;

    virtual void releaseGestures() = 0;

    virtual bool gesturesSuppressed() const = 0;
};