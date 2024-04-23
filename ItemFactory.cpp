#include "ItemFactory.h"
#include "Wall.h" 
#include "Feed.h"

GameObject* ItemFactory::CreateItem(int objectType, PlayScene* scene, int xPos, float scrollSpe) {
    switch (objectType) {
    case 0:
        Instantiate<Feed>(scene, xPos, scrollSpe);
        break;

    default:
        return nullptr;
    }
}
