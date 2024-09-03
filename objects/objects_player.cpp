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
    if(pixel != 0) return pixel;

    return 0;
}

static u8 GetYCollision(int x, int y) {
    u8 pixel = 0;

    pixel = NF_GetPoint(0, x + 22, y + 64);
    if(pixel != 0) return pixel;

    pixel = NF_GetPoint(0, x + 35, y + 64);
    if(pixel != 0) return pixel;

    return 0;
}


////////////////////////////////////////////////////////
// Some functions for object creation/destruction :)
////////////////////////////////////////////////////////


void Object16_Player::Create(int screen, u32 id, s32 x, s32 y){
    // Store sprite information.
    Position = {x, y, 0, 0, 0, 0};
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
    JumpSound.Handle.volume = 80; // Set volume.

    Health.Create(ID + 1); // Create Health counter.
}


void Object16_Player::Move(){
    if(kdown & KEY_LEFT) SpriteStartAnim(2, 0, 2, 64, &Animation);
    else if(kdown & KEY_RIGHT) SpriteStartAnim(2, 0, 2, 64, &Animation);

    if(kheld & KEY_LEFT){
        NF_HflipSprite(0, ID, true);
        Position.vX -= 64;
    }
    else if(kheld & KEY_RIGHT){
        NF_HflipSprite(0, ID, false);
        Position.vX += 64;
    }
    else {
        Position.vX += ((Position.vX > 0) ? -64 : 64);
        Animation.Anim_Type = 0;
        Animation.Frame = 0;
    }

    if(GetXCollision(Position.X + (Position.vX >> 8), Position.Y) != 0){
        int distance = 0;
        for(int i = 0; i < (Position.vX >> 8); i ++){
            if(GetXCollision(Position.X + distance, Position.Y) == 0) distance ++;
        }
        Position.X += distance;
        Position.vX = 0;
    }

    // Speed cap :)
    if(Position.vX > 512) Position.vX = 512;
    else if(Position.vX < -512) Position.vX = -512;

    // Apply changes :)
    Position.X += (Position.vX >> 8);
}


void Object16_Player::Gravity(){
    // Floor collision.
    if(GetYCollision(Position.X, Position.Y + (Position.vY >> 8) ) == 0){
        Position.vY += 51;  // Gravity.
    }
    else {
        int distance = 0;
        // a bug fix, I don't know how this works but if it isn't here the collision looks, off...
		for(int i = 0; i < (Position.vY >> 8); i ++){
            if(GetYCollision(Position.X, Position.Y + distance) == 0) distance ++;
		}
		Position.Y += distance;
		distance = 0;
        Position.vY = 0;

        if(kheld & KEY_B) {
            Position.vY = -1280; // Jumping.
            mmEffectEx(&JumpSound.Handle);
        }
    }

    // Uphill, this code basically moves the player up if it's stuck in collision...
    // Uses too much CPU if I can remember...
    if(GetYCollision(Position.X, Position.Y) != 0){
        int updistance = 0;
		for(int i = 0; i < 63; i ++){
            if(GetYCollision(Position.X, Position.Y + updistance) != 0) updistance --;
		}
        Position.Y += (updistance + 1);
        Position.vY += 32;
    }

    // Ceiling collision... Seems simple and it shouldn't cause any issues.
    if(GetYCollision(Position.X, Position.Y - 36 + (Position.vY >> 8)) != 0) Position.vY = 0;

    // Apply changes :)
    if(Position.vY > 1024) Position.vY = 1024; // Speed cap.
    Position.Y += Position.vY >> 8;
}


void Object16_Player::UpdateBg(){
    // Code for making the smooth bg scrolling on X.
    if(Position.sX > 105) BgScroll.vX += 512;
    else if(Position.sX < 96) BgScroll.vX -= 512;
    else BgScroll.vX += ((BgScroll.vX > 0) ? -128 : 128); // idk why this needs to be here, bg looks off if it isn't there.

    // Code for making the smooth bg scrolling on Y.
    if(Position.sY > 70) BgScroll.vY += 512;
    else if(Position.sY < 60) BgScroll.vY -= 512;
    else BgScroll.vY += ((BgScroll.vY > 0) ? -128 : 128); // idk why this needs to be here, bg looks off if it isn't there.

    // Without this the bg looks off? I don't know what's up with this code...
    BgScroll.vX += ((BgScroll.vX > 0) ? -128 : 128);
    BgScroll.vY += ((BgScroll.vY > 0) ? -128 : 128);

    // These are just speed caps that match with the player speed caps to prevent a bug.
    if(BgScroll.vX < -512) BgScroll.vX = -512;
    if(BgScroll.vX > 512) BgScroll.vX = 512;
    if(BgScroll.vY > 1024) BgScroll.vY = 1024;
    if(BgScroll.vY < -1024) BgScroll.vY = -1024;

    // Apply changes to bg variables. (still need to do BgScroll to apply to background)
    BgScroll.X += (BgScroll.vX >> 8);
    BgScroll.Y += (BgScroll.vY >> 8);
}


void Object16_Player::Update(){
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
