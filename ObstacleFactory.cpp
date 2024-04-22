#include "ObstacleFactory.h"
#include "Wall.h" 

GameObject* ObstacleFactory::CreateObstacle(int objectType, PlayScene* scene, int xPos) {
    switch (objectType) {
    case 0:
        Instantiate<Wall>(scene, xPos);
        break;

    default:
        return nullptr;
    }
}
