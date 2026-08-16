#pragma once

#include <vector>
#include <functional>

#include "IMacro.h"


class CycleMacro : public IMacro
{
private:

    std::vector<std::reference_wrapper<IMacro>> macros;

    // Index of the currently selected/last executed macro.
    size_t currentIndex = 0;

    // True before the first execution.
    bool hasExecuted = false;


public:

    CycleMacro& add(
        IMacro& macro);


    // Default execution = forward
    void execute(
        IKeyboardDriver& driver) override;


    // Explicit directions
    void forwardExecute(
        IKeyboardDriver& driver);


    void backwardExecute(
        IKeyboardDriver& driver);


    void reset();


    size_t size() const;


    bool empty() const;
};