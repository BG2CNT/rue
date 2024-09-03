#ifndef EFFECTS_RAIN_H
#define EFFECTS_RAIN_H

typedef struct{
    int pos;
    int tile;
    int timer;

    int current_screen;
    int current_layer;
} UFX_RainVar;

extern UFX_RainVar UFX_Rain;

void UFX_RainVBL(bool tileanimation, int scrollx, int scrolly);

#endif
