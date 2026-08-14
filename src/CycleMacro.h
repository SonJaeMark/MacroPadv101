#pragma once

#include <vector>
#include <functional>

#include "IMacro.h"

class CycleMacro : public IMacro
{
private:
    std::vector<std::reference_wrapper<IMacro>> macros;
    size_t currentIndex = 0;

public:
    CycleMacro& add(IMacro& macro);

    void execute(IKeyboardDriver& driver) override;

    void forwardExecute(IKeyboardDriver& driver);

    void backwardExecute(IKeyboardDriver& driver);

    void reset();

    size_t size() const;

    bool empty() const;
};