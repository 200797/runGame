#pragma once

enum class ItemTypes
{
    Coin = 0,
    Count
};

class Item
{
public:
    static int GetTypeCount()
    {
        return static_cast<int>(ItemTypes::Count);
    }
};
