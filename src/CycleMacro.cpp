#include "CycleMacro.h"

CycleMacro& CycleMacro::add(IMacro& macro)
{
    macros.emplace_back(macro);
    return *this;
}

void CycleMacro::execute(IKeyboardDriver& driver)
{
    forwardExecute(driver);
}

void CycleMacro::forwardExecute(IKeyboardDriver& driver)
{
    if (macros.empty())
        return;

    macros[currentIndex].get().execute(driver);

    currentIndex = (currentIndex + 1) % macros.size();
}

void CycleMacro::backwardExecute(IKeyboardDriver& driver)
{
    if (macros.empty())
        return;

    if (currentIndex == 0)
        currentIndex = macros.size() - 1;
    else
        --currentIndex;

    macros[currentIndex].get().execute(driver);
}

void CycleMacro::reset()
{
    currentIndex = 0;
}

size_t CycleMacro::size() const
{
    return macros.size();
}

bool CycleMacro::empty() const
{
    return macros.empty();
}