#pragma once

#include "Engine/GameObject.h"
#include "PlayScene.h"

class ObstacleFactory 
{
public:
    /// <summary>
    /// </summary>
    /// <param name="objectType"> �ǂ̃I�u�W�F�N�g�� </param>
    /// <param name="scene"> �ǂ̃V�[���ɐ������邩 </param>
    /// <param name="xPos"> �o������X���W </param>
    /// <returns> �n���ꂽ���������ɏ�Q���𐶐�</returns>
    static GameObject* CreateObstacle(int objectType, PlayScene* scene, int xPos);
};
