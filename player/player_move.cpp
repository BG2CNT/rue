#include "objects_player.h"
#include "objects_wrappers.h"
#include "soundbank.h"


////////////////////////////////////////////////////////
// Some functions for collision dectection :)
////////////////////////////////////////////////////////

static u8 GetXCollision(int x, int y){
    u8 pixel = 0;

    pixel = NF_GetPoint(0, x + 21, y + 63);
    if(pixel != 0) return pixel;

    pixel = NF_GetPoint(0, x + 36, y + 63);
    if(pixel != 0) return pixel;

    pixel = NF_GetPoint(0, x + 21, y + 28);
    if(pixel != 0) return pixel;

    pixel = NF_GetPoint(0, x + 36, y + 28);
    return pixel;

}


static void Collision(Object_Position *Position){
    if(GetXCollision(Position->X + (Position->vX >> 8), Position->Y) != 0){
        int distance = 0;
        for(int i = 0; i < (Position->vX >> 8); i ++){
            if(GetXCollision(Position->X + distance, Position->Y) == 0) distance ++;
        }
        Position->X += distance;
        Position->vX = 0;
    }
}


// Move function.
void Object16_Player::Move(){
    if(kdown & KEY_LEFT) SpriteStartAnim(2, 0, 2, 64, &Animation);
    else if(kdown & KEY_RIGHT) SpriteStartAnim(2, 0, 2, 64, &Animation);

    if(kheld & KEY_LEFT){
        NF_HflipSprite(0, ID, true);
        Position.vX -= Speeds.AccelerationX;
    }
    else if(kheld & KEY_RIGHT){
        NF_HflipSprite(0, ID, false);
        Position.vX += Speeds.AccelerationX;
    }
    else {
        Position.vX += ((Position.vX > 0) ? -Speeds.DeAccelerationX : Speeds.DeAccelerationX);
        StopSpriteAnim(&Animation);
    }

    // Speed cap :)
    if(Position.vX > Speeds.LimitX) Position.vX = Speeds.LimitX;
    else if(Position.vX < -Speeds.LimitX) Position.vX = -Speeds.LimitX;

    Collision(&Position);
}
