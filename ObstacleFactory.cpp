#include "ObstacleFactory.h"
#include "Wall.h" 
#include "Fall.h"

GameObject* ObstacleFactory::CreateObstacle(int objectType, PlayScene* scene, int xPos) {
    switch (objectType) {
    case 0:
        Instantiate<Wall>(scene, xPos);
        break;
    case 1:
        Instantiate<Fall>(scene, xPos);
        break;
    default:
        return nullptr;
    }
}
