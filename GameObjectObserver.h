#pragma once
#include "Engine/GameObject.h"

class GameObjectObserver
{
public:
    virtual void OnCollision(GameObject* pSelf) = 0;
};
