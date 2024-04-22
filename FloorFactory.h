#pragma once

#include "Engine/GameObject.h"
#include "PlayScene.h"

class FloorFactory 
{
public:
    static GameObject* CreateFloor(int objectType, PlayScene* scene, int xPos);
};
