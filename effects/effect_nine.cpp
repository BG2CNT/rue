/*
    Effect: Nine.
    By: BG2CNT.

    Based heavily around the Nine Circles effect.

*/
#include <nf_lib.h>

#include "effect_nine.h"

UFXV_NineEffect UFX_NineEffect;

static void ResetColors(){
    for(u8 i = 1; i <= 6; i ++) NF_BgEditPalColor(UFX_NineEffect.Screen, UFX_NineEffect.Layer, i, 1, 1, 1);
}

void UFX_NineVBL(){
    if(UFX_NineEffect.Enabled == false) return;
    int Screen = UFX_NineEffect.Screen;
    int Layer = UFX_NineEffect.Layer;


    UFX_NineEffect.Timer += 64;
    if(UFX_NineEffect.Timer > 1280) UFX_NineEffect.Timer = 0;


    int ColorNum = (UFX_NineEffect.Timer >> 8);

    ResetColors();

    NF_BgEditPalColor(Screen, Layer, ColorNum + 1, 10, 0, 0);
    NF_BgEditPalColor(Screen, Layer, ColorNum + 2, 20, 0, 0);
    NF_BgEditPalColor(Screen, Layer, ColorNum + 3, 30, 0, 0);
    NF_BgUpdatePalette(Screen, Layer);
}