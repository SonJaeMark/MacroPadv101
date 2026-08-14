#pragma once
#include <cstdint>
#include <string>
#include <functional>


enum class ActionType
{
    PRESS,
    RELEASE,
    CLICK,
    RELEASE_ALL,
    DELAY,
    TYPE_TEXT,
    CALLBACK
};

struct Action
{
    ActionType type;

    uint8_t key = 0;

    uint32_t delay = 0;

    std::string text{};

    std::function<void()> callback{};
};

// Factory Functions
Action makePress(uint8_t key);
Action makeRelease(uint8_t key);
Action makeClick(uint8_t key);
Action makeDelay(uint32_t ms);
Action makeTypeText(const std::string& text);
Action makeReleaseAll();
Action makeCallback(const std::function<void()>& fn);