#pragma once

class IMacroButton
{
public:
    virtual ~IMacroButton() = default;

    virtual void tick() = 0;

    virtual bool isPressed() const = 0;

    // Chord control
    virtual void suppressGestures() = 0;

    virtual void releaseGestures() = 0;

    virtual bool gesturesSuppressed() const = 0;
};