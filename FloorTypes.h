#pragma once

enum class FloorTypes
{
    // b’èA–¼‘O‚Ív‚¢‚Â‚¢‚½‚ç•Ï‚¦‚é
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
