#include <nf_lib.h>
#include "objects_wrappers.h"
#include "objects_crystals.h"

void Object16_Crystal::Create(int id, int x, int y){
    // Store sprite information.
    Position = {x, y, 0, 0};
    AnimationHandler.Speed = 48;
    ID = id;
    Collected = false;


    NF_CreateSprite(0, id, 2, 1, -64, 0); // Create sprite.
    SpriteStartAnim(2, 0, 3, 48, &AnimationHandler);
}





void Object16_Crystal::Update(Object16_Player* Player){
    // Object code.
    if(!Collected && GetObjectCollision(Position.X, Position.Y, Player->Position.X, Player->Position.Y, 38, 38)){
        Player->CrystalsCollected ++;
        Player->Health.HealthCounter -= (Player->Health.HealthCounter > 0);

        Collected = true;
        SpriteStartAnim(1, 4, 8, 56, &AnimationHandler);
    }
    if(AnimationHandler.Frame == 1792) AnimationHandler.stopped = true;

    // Sprite code.
    GetScreenCoordinates(&Position.sX, &Position.sY, Position.X, Position.Y,
                        Player->BgScroll.X, Player->BgScroll.Y);
    SetObjectCameraLimits(&Position.sX, &Position.sY, 16, 16);
    UpdateSpriteAnim(&AnimationHandler);
    NF_SpriteFrame(0, ID, AnimationHandler.Frame >> 8);
    NF_MoveSprite(0, ID, Position.sX, Position.sY);
}
