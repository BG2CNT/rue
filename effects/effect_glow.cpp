/*
    Effect: Glow
    By: BG2CNT

    Makes a Window (Color Yellow) Glow.
    Used in: Test stage 1 (Tutorial)
*/

// Includes
#include <nf_lib.h>
#include "effect_glow.h"


GlowEffectVar GlowEffect[2][4]; // Data struct.


void UFX_DisableAllGlowEffects(){
    for(u8 layer = 0; layer <= 3; layer ++){
        GlowEffect[0][layer] = {};
        GlowEffect[1][layer] = {};
    }
}


void UFX_GlowVBL(int screen, int layer){
    GlowEffectVar* Effect = &GlowEffect[screen][layer];
    if(!Effect->enabled) return;

    // We need fixed point math.
    if(Effect->darknen > 7936) Effect->Change = true;
    else if(Effect->darknen < 5120) Effect->Change = false;

    // Add slower using fixed point math (64/256=0,25)
    Effect->darknen += (Effect->Change ? -64 : 64);

    // Apply effect.
    if((Effect->darknen >> 8)%2 == 0) { // Color effect.
        NF_BgEditPalColor(screen, layer, Effect->Color, Effect->darknen >> 8, Effect->darknen >> 8, 0);
        NF_BgUpdatePalette(screen, layer);
    }
}
