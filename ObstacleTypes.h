#pragma once

enum class ObstacleTypes
{
    // Floor��0�ɂ��������Ŏ኱���̉��ϕK�v�ɂȂ���������@�ς��邩��
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
