#include <nf_lib.h>
#include <maxmod9.h>


int kheld;
int kdown;
int kreleased;

void InitNFlib(){
    NF_Set2D(1,0);
    NF_Set2D(0,0);

    NF_InitTiledBgBuffers();
    NF_InitTiledBgSys(0);
    NF_InitTiledBgSys(1);

    NF_InitTextSys(0);
    NF_InitTextSys(1);

    NF_InitSpriteBuffers();
    NF_InitSpriteSys(0);
    NF_InitSpriteSys(1);

    NF_InitCmapBuffers();
}

void UpdateOAM(u8 screen){
    switch(screen){
        case 0:
            NF_SpriteOamSet(0);
            oamUpdate(&oamMain);
        break;
        case 1:
            NF_SpriteOamSet(1);
            oamUpdate(&oamSub);
        break;
        case 2:
            NF_SpriteOamSet(1);
            NF_SpriteOamSet(0);
            oamUpdate(&oamMain);
            oamUpdate(&oamSub);
        break;
    }
}

bool Nothing(){
    return 0;
}

bool Wait(u32 frames, bool (*func)(void)){
    for(u32 i = 0; i < frames; i ++){
        swiWaitForVBlank();
		if((*func)() == 1) return 1;
    }
    return 0;
}

void DeleteEverySprite(){
    for(u8 i = 0; i < 127; i++){
        if(NF_SPRITEOAM[1][i].created) NF_DeleteSprite(1,i);
        if(NF_SPRITEOAM[0][i].created) NF_DeleteSprite(0,i);
    }
}


void D_ScanKeys(){
    scanKeys();
    kheld = keysHeld();
    kdown = keysDown();
    kreleased = keysUp();
}

void MaxModDefaultHandle(mm_sound_effect * Handle, mm_word id){
    Handle->id = id;
    Handle->rate = 1024;
    Handle->panning = 0;
    Handle->volume = 255;
    Handle->panning = 128;
}
