#include <nf_lib.h>
#include "effect_rain.h"

UFX_RainVar UFX_Rain = {0, 10, 10};


void UFX_RainVBL(bool tileanimation, int scrollx, int scrolly){
    if(UFX_Rain.current_screen == 10 && UFX_Rain.current_layer == 10) return;

    int screen = UFX_Rain.current_screen;
    int layer = UFX_Rain.current_layer;
    UFX_Rain.pos ++;

    NF_UpdateVramMap(screen, layer);
    NF_ScrollBg(screen, layer, UFX_Rain.pos + scrollx, -UFX_Rain.pos + scrolly);
}
