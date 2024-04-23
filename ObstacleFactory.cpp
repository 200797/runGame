#include "ObstacleFactory.h"
#include "Wall.h" 

GameObject* ObstacleFactory::CreateObstacle(int objectType, PlayScene* scene, int xPos, float scrollSpe) {
    switch (objectType) {
    case 0:
        Instantiate<Wall>(scene, xPos, scrollSpe);
        break;

    default:
        return nullptr;
    }
}
