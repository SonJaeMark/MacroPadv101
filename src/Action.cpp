#include "Action.h"

Action makePress(uint8_t key)
{
    return {
        ActionType::PRESS,
        key,
        0,
        {},
        {}
    };
}

Action makeRelease(uint8_t key)
{
    return {
        ActionType::RELEASE,
        key,
        0,
        {},
        {}
    };
}

Action makeClick(uint8_t key)
{
    return {
        ActionType::CLICK,
        key,
        0,
        {},
        {}
    };
}

Action makeDelay(uint32_t ms)
{
    return {
        ActionType::DELAY,
        0,
        ms,
        {},
        {}
    };
}

Action makeTypeText(const std::string& text)
{
    return {
        ActionType::TYPE_TEXT,
        0,
        0,
        text,
        {}
    };
}

Action makeReleaseAll()
{
    return {
        ActionType::RELEASE_ALL,
        0,
        0,
        {},
        {}
    };
}

Action makeCallback(const std::function<void()>& fn)
{
    return {
        ActionType::CALLBACK,
        0,
        0,
        {},
        fn
    };
}