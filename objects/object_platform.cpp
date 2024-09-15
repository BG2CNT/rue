#include <nf_lib.h>
#include "objects_platform.h"

void Object16_Platform::Create(int id, int x, int y, int TargetX, int TargetY, int speed){
    CreateGfx();
    ID = id;
    Position.X = x;
    Position.Y = y;
    MoveCode = {TargetX, TargetY, x, y, false, false, speed};

    NF_CreateSprite(0, ID, 2, 1, -64, 0);
}

void MovePlatformX(Object_Position *Position, Object16_Platform_MoveCode *MoveCode){
    if(MoveCode->TargetX != MoveCode->StartX){
        if(Position->X > MoveCode->TargetX) MoveCode->MoveX = true;
        else if(Position->X < MoveCode->StartX) MoveCode->MoveX = false;

        Position->vX += (MoveCode->MoveX ? -32 : 32);

        if(Position->vX > 256) Position->vX = 256;
        else if(Position->vX < -256) Position->vX = -256;

        Position->vX += Position->vX >> 8;
    }
}

void MovePlatformY(Object_Position *Position, Object16_Platform_MoveCode *MoveCode){
    if(MoveCode->StartY != MoveCode->TargetY){
        if(Position->Y > MoveCode->TargetY) MoveCode->MoveY = true;
        else if(Position->Y < MoveCode->StartY) MoveCode->MoveY = false;

        Position->vY += (MoveCode->MoveY ? -32 : 32);

        if(Position->vY > MoveCode->MaxSpeed) Position->vY = MoveCode->MaxSpeed;
        else if(Position->vY < -MoveCode->MaxSpeed) Position->vY = -MoveCode->MaxSpeed;

        Position->Y += Position->vY >> 8;
    }
}

void Object16_Platform::Update(Object16_Player* Player){

    if(GetObjectCollision(Position.X + 32, Position.Y - 40, Player->Position.X, Player->Position.Y, 64, 32) && Player->Position.vY >= 0){
        int distance = 0;
		for(int i = 0; i < (Position.vY >> 8); i ++){
            if(!GetObjectCollision(Position.X + 32, Position.Y - 40, Player->Position.X, Player->Position.Y + distance, 64, 32))
                distance ++;
		}
        Player->Position.Y += distance;
        distance = 0;
        Player->Position.vY = 0;
        Player->StartJump(&Player->Jump_Timer.timer, &Player->Jump_Timer.touchingGround);
        Player->Position.Y += Position.vY >> 8;
    }
    if(GetObjectCollision(Position.X + 32, Position.Y - 36, Player->Position.X, Player->Position.Y, 64, 32) && Player->Position.vY >= 0){
        int updistance = 0;
		for(int i = 0; i < 63; i ++){
            updistance -= (GetObjectCollision(Position.X + 32, Position.Y - 36, Player->Position.X, Player->Position.Y, 64, 32));
		}
        Player->Position.Y += (updistance + 1);
        Player->Position.Y += 32;
    }

    MovePlatformX(&Position, &MoveCode);
    MovePlatformY(&Position, &MoveCode);

    GetScreenCoordinates(&Position.sX, &Position.sY, Position.X, Position.Y,
                        Player->BgScroll.X, Player->BgScroll.Y);
    SetObjectCameraLimits(&Position.sX, &Position.sY, 64, 32);
    NF_MoveSprite(0, ID, Position.sX, Position.sY);
}
