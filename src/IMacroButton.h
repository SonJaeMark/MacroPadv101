#pragma once

class IMacroButton
{
public:
    virtual ~IMacroButton() = default;

    virtual void tick() = 0;

    virtual bool isPressed() const = 0;
};