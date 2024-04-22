#pragma once

enum class ObstacleTypes
{
    // b’èA–¼‘O‚Ív‚¢‚Â‚¢‚½‚ç•Ï‚¦‚é
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
