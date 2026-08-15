#pragma once

class IMacroButton;

class IButtonListener
{
public:
    virtual ~IButtonListener() = default;

    virtual void onButtonPress(
        IMacroButton& button) = 0;

    virtual void onButtonRelease(
        IMacroButton& button) = 0;
};