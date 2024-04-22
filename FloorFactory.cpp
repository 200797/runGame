#include "FloorFactory.h"
#include "FloorTypes.h"
#include "Normal.h"

GameObject* FloorFactory::CreateFloor(int objectType, PlayScene* scene, int xPos) {
    switch (objectType) {
    case 0:
        Instantiate<Normal>(scene, xPos);
        break;

    default:
        return nullptr;
    }
}
