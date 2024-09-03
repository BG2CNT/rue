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

static inline void UFX_GlowCreate(int screen, int layer, int color){
    GlowEffect[screen][layer].enabled = true;
    GlowEffect[screen][layer].Color = color;
    GlowEffect[screen][layer].darknen = 7936;
}
void UFX_GlowVBL(int screen, int layer);

void UFX_WindowAlpha2(int bg);


#endif
