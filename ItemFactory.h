#pragma once

#include "Engine/GameObject.h"
#include "PlayScene.h"

class ItemFactory
{
public:
    static GameObject* CreateItem(int objectType, PlayScene* scene, int xPos, float scrollSpe);
};
