#ifndef EFFECT_WRAPPER_H
#define EFFECT_WRAPPER_H
#include "effects.h"

/*
    Disables all alpha effects.
*/
static inline void UFX_DisableAllAlphaEffects(){
    REG_BLDCNT = 0;
    REG_BLDCNT_SUB = 0;
}

/*
    Disables all effects.
*/
void UFX_DisableAllEffects();

#endif
