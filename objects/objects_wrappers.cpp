#include <nf_lib.h>
#include "objects_wrappers.h"

void SetObjectCameraLimits(int *sX, int *sY, int width, int height){
    if(*sX < -width) *sX = -width;
    else if(*sX > (256 + width)) *sX = 256 + width;

    if(*sY < -height) *sY = -height;
    else if(*sY > (192 + height)) *sY = 192 + height;
}


void UpdateSpriteAnim(Object16_Insider_AnimationConfig* AnimationHandler){
    if(AnimationHandler->stopped) return;
    switch(AnimationHandler->Anim_Type){
        case ANIM_NORMAL: // NORMAL.
            AnimationHandler->Frame += AnimationHandler->Speed;
            if(AnimationHandler->Frame > AnimationHandler->Max_Frame) {
                AnimationHandler->Frame = AnimationHandler->Min_Frame << 8;
            }
        break;
        case ANIM_UPDOWN: // UPDOWN.
            AnimationHandler->Frame += (AnimationHandler->inner_workings.animbool ?- AnimationHandler->Speed : AnimationHandler->Speed);

            if(AnimationHandler->Frame >= (AnimationHandler->Max_Frame)) AnimationHandler->inner_workings.animbool = true;
            else if(AnimationHandler->Frame <= (AnimationHandler->Min_Frame))AnimationHandler->inner_workings.animbool = false;
        break;
    }
}


void SpriteStartAnim(u8 AnimType, u16 StartFrame, u16 EndFrame, u8 Speed, Object16_Insider_AnimationConfig* AnimationHandler){
    AnimationHandler->Frame = StartFrame << 8;
    AnimationHandler->Min_Frame = StartFrame << 8;
    AnimationHandler->Max_Frame = EndFrame << 8;
    AnimationHandler->Speed = Speed;

    AnimationHandler->Anim_Type = AnimType;
    AnimationHandler->inner_workings.animbool = false;
    AnimationHandler->stopped = false;
}
