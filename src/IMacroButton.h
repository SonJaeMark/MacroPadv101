#pragma once

class IButtonListener;

class IMacroButton
{
public:
    virtual ~IMacroButton() = default;

    virtual void tick() = 0;

    virtual bool isPressed() const = 0;

    virtual void addButtonListener(
        IButtonListener& listener) = 0;
};