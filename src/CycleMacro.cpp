#include "CycleMacro.h"


// ============================================================
// Add
// ============================================================

CycleMacro& CycleMacro::add(
    IMacro& macro)
{
    macros.emplace_back(macro);

    return *this;
}


// ============================================================
// Default execute
// ============================================================

void CycleMacro::execute(
    IKeyboardDriver& driver)
{
    forwardExecute(driver);
}


// ============================================================
// Forward
// ============================================================

void CycleMacro::forwardExecute(
    IKeyboardDriver& driver)
{
    if (macros.empty())
        return;


    // ========================================================
    // First execution
    // ========================================================

    if (!hasExecuted)
    {
        currentIndex = 0;

        macros[currentIndex]
            .get()
            .execute(driver);

        hasExecuted = true;

        return;
    }


    // ========================================================
    // Move forward
    // ========================================================

    currentIndex =
        (currentIndex + 1) % macros.size();


    macros[currentIndex]
        .get()
        .execute(driver);
}


// ============================================================
// Backward
// ============================================================

void CycleMacro::backwardExecute(
    IKeyboardDriver& driver)
{
    if (macros.empty())
        return;


    // ========================================================
    // First execution
    // ========================================================

    if (!hasExecuted)
    {
        /*
         * If the very first operation is backward,
         * start from the last macro.
         */
        currentIndex = macros.size() - 1;

        macros[currentIndex]
            .get()
            .execute(driver);

        hasExecuted = true;

        return;
    }


    // ========================================================
    // Move backward
    // ========================================================

    if (currentIndex == 0)
    {
        currentIndex = macros.size() - 1;
    }
    else
    {
        --currentIndex;
    }


    macros[currentIndex]
        .get()
        .execute(driver);
}


// ============================================================
// Reset
// ============================================================

void CycleMacro::reset()
{
    currentIndex = 0;

    hasExecuted = false;
}


// ============================================================
// Size
// ============================================================

size_t CycleMacro::size() const
{
    return macros.size();
}


// ============================================================
// Empty
// ============================================================

bool CycleMacro::empty() const
{
    return macros.empty();
}