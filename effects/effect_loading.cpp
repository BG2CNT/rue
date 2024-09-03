#include "effects.h"
#include <nds.h>
#include <filesystem.h>
#include <nf_lib.h>
#include "../objects/objects_player.h"



void LoadEffects(u8 selection){
    char buffer[150];

    // Open file.
    sprintf(buffer, "levels/%d/effects.d16i", selection); // Get file location.
    FILE* file = fopen(buffer, "r"); // Open.
    // Effects are optional.
    if(file == NULL) return;

    while(fgets(buffer, 150, file)) {
        int screen, layer, color;
        if(sscanf(buffer, "WINDOW_GLOW:%d,%d,%d", &screen, &layer, &color) == 3){
            UFX_GlowCreate(screen, layer, color);
        }
        if(sscanf(buffer, "RAIN:%d,%d", &screen, &layer) == 2){
            UFX_Rain.current_screen = screen;
            UFX_Rain.current_layer = layer;
        }
        if(sscanf(buffer, "WINDOW_ALPHA_EFFECT:%d", &layer) == 1){
            UFX_WindowAlpha2(layer);
        }
    }
    fclose(file);
}

////////////////////////////////
// Wrappers to facilitate usage.
////////////////////////////////
void UFX_UpdateEffects(Object16_Player* Player){
    for(int layer = 0; layer <= 3; layer ++){
        UFX_GlowVBL(1, layer);
        UFX_GlowVBL(0, layer);
    }
    UFX_RainVBL(true, Player->BgScroll.X, Player->BgScroll.Y);
}


void UFX_WindowAlpha2(int bg){
    switch(bg){
        case 0:
        REG_BLDCNT = BLEND_ALPHA | BLEND_SRC_SPRITE | BLEND_DST_BG0;
        break;

        case 1:
        REG_BLDCNT = BLEND_ALPHA | BLEND_SRC_SPRITE | BLEND_DST_BG1;
        break;

        case 2:
        REG_BLDCNT = BLEND_ALPHA | BLEND_SRC_SPRITE | BLEND_DST_BG2;
        break;

        case 3:
        REG_BLDCNT = BLEND_ALPHA | BLEND_SRC_SPRITE | BLEND_DST_BG3;
        break;
    }
}
