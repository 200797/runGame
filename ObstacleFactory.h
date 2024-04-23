#pragma once

#include "Engine/GameObject.h"
#include "PlayScene.h"

class ObstacleFactory 
{
public:
    static GameObject* CreateObstacle(int objectType, PlayScene* scene, int xPos, float scrollSpe);
};
