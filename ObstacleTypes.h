#pragma once

enum class ObstacleType
{
    Wall = 0,
    Fall,
    Count
};

class Obstacle 
{
public:
    static int GetTypeCount() 
    {
        return static_cast<int>(ObstacleType::Count);
    }
};
