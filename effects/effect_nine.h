#ifndef EFFECT_NINE_H
#define EFFECT_NINE_H


typedef struct {
    bool Enabled;
    int Screen;
    int Layer;
    int Timer;
} UFXV_NineEffect;

extern UFXV_NineEffect UFX_NineEffect;

void UFX_NineVBL();

#endif