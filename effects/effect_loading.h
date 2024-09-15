#include <nf_lib.h>
#include "../player/objects_player.h"
#ifndef EFFECT_LOADING_H
#define EFFECT_LOADING_H


void LoadEffects(u8 selection);


////////////////////////////////
// Wrappers to facilitate usage.
////////////////////////////////
void UFX_UpdateEffects(Object16_Player* Player);

#endif
