#pragma once

enum class ObstacleTypes
{
    // 暫定、名前は思いついたら変える
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
