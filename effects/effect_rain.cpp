#include <nf_lib.h>
#include "effect_rain.h"

UFX_RainVar UFX_Rain = {0, 0, 0, 10, 10};


void UFX_RainVBL(bool tileanimation, int scrollx, int scrolly){
    if(UFX_Rain.current_screen == 10 && UFX_Rain.current_layer == 10) return;

    int screen = UFX_Rain.current_screen;
    int layer = UFX_Rain.current_layer;
    UFX_Rain.pos += 1;
    UFX_Rain.timer ++;

    if(UFX_Rain.timer < 30) UFX_Rain.tile = 1;
    else if(UFX_Rain.timer > 30) UFX_Rain.tile = 2;
    if(UFX_Rain.timer > 60) UFX_Rain.timer = 0;

    for(int x = 0; x < 32; x ++){
        for(int y = 0; y < 32; y ++){
            u32 currenttile = NF_GetTileOfMap(screen, layer, x, y);
            if(currenttile == 1 || currenttile == 2) NF_SetTileOfMap(screen, layer, x, y, UFX_Rain.tile);
        }
    }
    NF_UpdateVramMap(screen, layer);
    NF_ScrollBg(screen, layer, UFX_Rain.pos + scrollx, -UFX_Rain.pos + scrolly);
}
