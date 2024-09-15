#ifndef EFFECT_GLOW_H_INCLUDED
#define EFFECT_GLOW_H_INCLUDED
#include <nds.h>
typedef struct{
    bool enabled;
    int Color;

    bool Change;
    int darknen;
} GlowEffectVar;

extern GlowEffectVar GlowEffect[2][4];

/*
    Create Glow effect. Please don't use unless you are using Effect Loading.

    @param screen Screen for the effect to be enabled.
    @param layer layer for the effect to be enabled.
    @color color Pal color number.
*/
static inline void UFX_GlowCreate(int screen, int layer, int color){
    GlowEffect[screen][layer].enabled = true;
    GlowEffect[screen][layer].Color = color;
    GlowEffect[screen][layer].darknen = 7936;
}

/*
    Disables glow effects :)

    @param screen Screen.
    @param layer Bg layer where the effect is enabled.
*/
static inline void UFX_GlowDisable(int screen, int layer){
    GlowEffect[screen][layer] = {};
}

/*
    Disables all glow effects :)
*/
void UFX_DisableAllGlowEffects();

/*
    Glow effect vbl.
    @param screen Screen.
    @param layer Background layer.
*/
void UFX_GlowVBL(int screen, int layer);

/*
    Window alpha effect...

    @param bg Background for the effect to be enabled.
*/
void UFX_WindowAlpha2(int bg);


#endif
