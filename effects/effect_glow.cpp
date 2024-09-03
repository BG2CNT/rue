/*
    Effect: Glow
    By: BG2CNT

    Makes a Window (Color Yellow) Glow.
    Used in: Test stage 1 (Tutorial)
*/

// Includes
#include <nf_lib.h>
#include "effect_glow.h"

static inline int FixedPoint(int var){
    return (var << 8);
}

GlowEffectVar GlowEffect[2][4];

// Glow VBL.
void UFX_GlowVBL(int screen, int layer){
    GlowEffectVar* Effect = &GlowEffect[screen][layer];
    if(!Effect->enabled) return;

    // We need fixed point math.
    if(Effect->darknen > FixedPoint(31)) Effect->Change = true;
    else if(Effect->darknen < FixedPoint(20)) Effect->Change = false;

    // Add slower using fixed point math (64/256=0,25)
    Effect->darknen += (Effect->Change ? -64 : 64);

    // Apply effect.
    if((Effect->darknen >> 8)%3 == 0) { // Color effect.
        NF_BgEditPalColor(screen, layer, Effect->Color, Effect->darknen >> 8, Effect->darknen >> 8, 0);
        NF_BgUpdatePalette(screen, layer);
    }
}
