/*
This is the most complicated and most overengineered part of the
RUE source code, it has basically the worst code of all time :)

To do:
    Improve this f-cking piece of dogsh-t code.
*/
#include "objects_player.h"
#include "objects_wrappers.h"
#include "soundbank.h"





////////////////////////////////////////////////////////
// Some functions for object creation/destruction :)
////////////////////////////////////////////////////////


void Object16_Player::Create(int screen, u32 id, s32 x, s32 y){
    // Store sprite information.
    Position.X = x;
    Position.Y = y;
    Position.sX = 0;
    Position.sY = 0;

    BgScroll = {x - 128, y - 96, 0, 0};

    Animation.Speed = 48;
    ID = id;

    // Load sprites.
    LoadSpritePal(0, "engine/sprites/player/palette", 0, 0);
    LoadSpriteGfx(0, "engine/sprites/player/body", 0, 0, 64, 64, true);

    // Create sprites.
    NF_CreateSprite(0, id, 0, 0, -64, 0);
    NF_SpriteLayer(0, id, 2);
    // Load jump sound.
    mmLoadEffect(SFX_JUMP);
    MaxModDefaultHandle(&JumpSound.Handle, SFX_JUMP);
    JumpSound.Handle.volume = 127; // Set volume.

    Health.Create(ID + 1); // Create Health counter.
}


void Object16_Player::UpdateBg(){
    BgScroll.X = Position.X - 105;
    BgScroll.Y = Position.Y - 70;
}


void Object16_Player::Update(){
    Position.X += (Position.vX >> 8);
    Position.Y += (Position.vY >> 8);

    Health.Update();

    // Code to get sprite position.
    GetScreenCoordinates(&Position.sX, &Position.sY, Position.X, Position.Y,
                        BgScroll.X, BgScroll.Y);
    SetObjectCameraLimits(&Position.sX, &Position.sY, 0, 0);
    // These are functions to help with usage...
    UpdateSpriteAnim(&Animation);

    // Body sprite.
    NF_SpriteFrame(0, ID, Animation.Frame >> 8);
    NF_MoveSprite(0, ID, Position.sX, Position.sY + 4);

    // Hide sprite if iframes.
    if((Health.iframes&4) != 0) NF_MoveSprite(0, ID, -64, 0);
}
