#pragma once

enum class FloorTypes
{
    // 暫定、名前は思いついたら変える
    Normal = 0,
    Accelerat,
    Decelerat,
    Count
};

class Floor
{
public:
    static int GetTypeCount()
    {
        return static_cast<int>(FloorTypes::Count);
    }
};
