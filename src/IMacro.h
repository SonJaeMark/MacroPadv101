#pragma once
#include "IKeyboardDriver.h"

class IMacro
{
public:
    virtual ~IMacro() = default;

    virtual void execute(IKeyboardDriver& driver) = 0;
};