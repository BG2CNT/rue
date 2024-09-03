#include <nf_lib.h>
#include "objects_wrappers.h"

void SetObjectCameraLimits(int *sX, int *sY, int width, int height){
    if(*sX < -width) *sX = -width;
    else if(*sX > (256 + width)) *sX = 256 + width;

    if(*sY < -height) *sY = -height;
    else if(*sY > (192 + height)) *sY = 192 + height;
}


void UpdateSpriteAnim(Object16_Insider_AnimationConfig* anim){
    if(anim->stopped) return;
    switch(anim->Anim_Type){
        case ANIM_NORMAL: // NORMAL.
            anim->Frame += anim->Speed;
            if(anim->Frame > anim->Max_Frame) anim->Frame= anim->Min_Frame << 8;
        break;
        case ANIM_UPDOWN: // UPDOWN.
            anim->Frame += (anim->inner_workings.animbool ?- anim->Speed : anim->Speed);

            if(anim->Frame >= (anim->Max_Frame) ) anim->inner_workings.animbool = true;
            else if(anim->Frame <= (anim->Min_Frame) )anim->inner_workings.animbool = false;
        break;
    }
}


void SpriteStartAnim(u8 animtype, u16 startframe, u16 endframe, u8 speed, Object16_Insider_AnimationConfig* animconfig){
    animconfig->Frame = startframe << 8;
    animconfig->Min_Frame = startframe << 8;
    animconfig->Max_Frame = endframe << 8;
    animconfig->Speed = speed;

    animconfig->Anim_Type = animtype;
    animconfig->inner_workings.animbool = false;
    animconfig->stopped = false;
}
