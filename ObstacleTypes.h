#pragma once

enum class ObstacleTypes
{
    // �b��A���O�͎v��������ς���
    Wall = 0,
    Count
};

class Obstacle 
{
public:
    static int GetTypeCount() 
    {
        return static_cast<int>(ObstacleTypes::Count);
    }
};
