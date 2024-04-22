#pragma once

#include "Engine/GameObject.h"
#include "PlayScene.h"

class ObstacleFactory 
{
public:
    /// <summary>
    /// </summary>
    /// <param name="objectType"> どのオブジェクトか </param>
    /// <param name="scene"> どのシーンに生成するか </param>
    /// <param name="xPos"> 出現時のX座標 </param>
    /// <returns> 渡された引数を元に障害物を生成</returns>
    static GameObject* CreateObstacle(int objectType, PlayScene* scene, int xPos);
};
