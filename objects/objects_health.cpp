/*
    Extends object_player.cpp :)
*/
#include <nf_lib.h>
#include "wrappers.h"
#include <maxmod9.h>
#include "soundbank.h"
#include "objects_player.h"

static inline void ShowHealth(int *Y){
    *Y += (*Y < 0);
}


static inline void HideHealth(int *Y){
    *Y -= (*Y > -32);
}


void Object16_Health::Create(int id){
    // Hide sprite.
    Position = {0, -32};
    ID = id;

    // Create sprite.
    LoadSpriteGfx(0, "engine/sprites/player/health", 1, 1, 32, 32, true);
    NF_CreateSprite(0, id, 1, 0, 0, -32);

    // Load Sound Effect
    mmLoadEffect(SFX_LOW_HP);
    MaxModDefaultHandle(&Sound.Handle, SFX_LOW_HP);
    Sound.Handle.volume = 64;
}



void Object16_Health::Update(){
    switch(HealthCounter){
        case 0:
            HideHealth(&Position.Y);
        break;
        case 1:
            ShowHealth(&Position.Y);
        break;
        case 2:
            ShowHealth(&Position.Y);
            Sound.Counter ++;

            if(Sound.Counter == 100) {
                mmEffectEx(&Sound.Handle);
                Sound.Counter = 0;
            }
        break;
    }
    // iframes.
    iframes -= (iframes>0);

    // Update sprite.
    NF_SpriteFrame(0, ID, HealthCounter);
    NF_MoveSprite(0, ID, Position.X, Position.Y);
}
