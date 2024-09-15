#include "objects_player.h"
#include "objects_wrappers.h"
#include "soundbank.h"

////////////////////////////////////////////////////////
// Some functions for collision dectection :)
////////////////////////////////////////////////////////
static u8 GetYCollision(int x, int y) {
    u8 pixel = NF_GetPoint(0, x + 22, y + 64);
    if(pixel != 0) return pixel;

    pixel = NF_GetPoint(0, x + 35, y + 64);
    return pixel;
}




static inline void CeilingCollision(Object_Position * Position){
    if(GetYCollision(Position->X, Position->Y - 36 + (Position->vY >> 8)) != 0) Position->vY = 0;
}



static void UphillCollision(Object_Position *Position){
    if(GetYCollision(Position->X, Position->Y) != 0){

        int updistance = 0;
		for(int i = 0; i < 63; i ++){
            updistance -= (GetYCollision(Position->X, Position->Y + updistance) != 0);
		}

        Position->Y += (updistance + 1);
        Position->vY += 32;
    }

}


void Object16_Player::Gravity(){
    Position.vY += Speeds.AccelerationY;  // Apply gravity.


    if((kheld&KEY_A || kheld&KEY_B) && Jump_Timer.touchingGround == true){
        if(Jump_Timer.timer == 0) mmEffectEx(&JumpSound.Handle);
        if(Jump_Timer.timer > 15) Jump_Timer.touchingGround = false;
        else{
            Position.vY = -640;
        }
        Jump_Timer.timer ++;
    }
    else Jump_Timer.touchingGround = false;


    if(GetYCollision(Position.X, Position.Y + (Position.vY >> 8)) != 0) {
        int distance = 0;
        // a bug fix, I don't know how this works but if it isn't here the collision looks, off...
		for(int i = 0; i < (Position.vY >> 8); i ++){
            if(GetYCollision(Position.X, Position.Y + distance) == 0) distance ++;
		}
		Position.Y += distance;
		distance = 0;
        Position.vY = 0;

        StartJump(&Jump_Timer.timer, &Jump_Timer.touchingGround);
    }

    // Uphill collision.
    UphillCollision(&Position);

    // Ceiling collision... Seems simple and it shouldn't cause any issues.
    CeilingCollision(&Position);

    if(Position.vY > 1024) Position.vY = 1024; // Speed cap.

    // Changes are applied in Update function.
}
