#pragma once

enum class ObstacleTypes
{
    // Floorを0にしたせいで若干他の改変必要になったから方法変えるかも
    Floor = 0,
    Wall,
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
