#pragma once

enum class ObstacleTypes
{
    // Floor‚ð0‚É‚µ‚½‚¹‚¢‚ÅŽáŠ±‘¼‚Ì‰ü•Ï•K—v‚É‚È‚Á‚½‚©‚ç•û–@•Ï‚¦‚é‚©‚à
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
