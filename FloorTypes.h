#pragma once

enum class FloorTypes
{
    // �b��A���O�͎v��������ς���
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
