#include "level_loading.h"
#include <nds.h>
#include <filesystem.h>
#include "../effects/effect_loading.h"
#include <nf_lib.h>

void FreeLevelData(RUE_LevelInfo *LevelInfo){
    free(LevelInfo->CMap.Location);
    free(LevelInfo->Information.Name);
    free(LevelInfo->Information.Description);
    for(u8 i = 0; i < 4; i ++){
        free(LevelInfo->BgInformation[i].Location);
        LevelInfo->BgInformation[i].Width = 0;
        LevelInfo->BgInformation[i].Height = 0;
    }
    LevelInfo->Information.Name = NULL;
    LevelInfo->Information.Description = NULL;
    LevelInfo->CMap.Location = NULL;
}


void LoadLevelData(u8 selection, RUE_LevelInfo *LevelInfo){
    char buffer[150];

    // AlLocationate memory.
    LevelInfo->Information.Name = (char*) malloc(40);
    LevelInfo->Information.Description = (char*) malloc(150);
    LevelInfo->CMap.Location = (char*) malloc(150);
    for(u8 i = 0; i < 4; i ++) LevelInfo->BgInformation[i].Location = (char*) malloc(80); // AlLocationate memory for background Location.

    // Open file.
    sprintf(buffer, "levels/%d/info.d16i", selection); // Get file Location.
    FILE* file = fopen(buffer, "r"); // Open.

    while(fgets(buffer, 150, file)) {
        sscanf(buffer, "NAME:%[^\n]", LevelInfo->Information.Name);
        sscanf(buffer, "NAME_COL:%d", &LevelInfo->Information.NameColor);
        sscanf(buffer, "PLAYER_POS:%dx%d", &LevelInfo->PlayerX, &LevelInfo->PlayerY);
        sscanf(buffer, "CMAP_SIZE:%dx%d", &LevelInfo->CMap.Width, &LevelInfo->CMap.Height);
        sscanf(buffer, "CAMERA_BOUNDS_X:%dx%d", &LevelInfo->CameraBoundsX[0], &LevelInfo->CameraBoundsX[1]);
        sscanf(buffer, "CAMERA_BOUNDS_Y:%dx%d", &LevelInfo->CameraBoundsY[0], &LevelInfo->CameraBoundsY[1]);
        sscanf(buffer, "CMAP_LOCATION:%s", LevelInfo->CMap.Location);

        sscanf(buffer, "BG3:%s", LevelInfo->BgInformation[3].Location);
        sscanf(buffer, "BG2:%s", LevelInfo->BgInformation[2].Location);
        sscanf(buffer, "BG1:%s", LevelInfo->BgInformation[1].Location);
        sscanf(buffer, "BG0:%s", LevelInfo->BgInformation[0].Location);

        sscanf(buffer, "BG3_SIZE:%dx%d", &LevelInfo->BgInformation[3].Width, &LevelInfo->BgInformation[3].Height);
        sscanf(buffer, "BG2_SIZE:%dx%d", &LevelInfo->BgInformation[2].Width, &LevelInfo->BgInformation[2].Height);
        sscanf(buffer, "BG1_SIZE:%dx%d", &LevelInfo->BgInformation[1].Width, &LevelInfo->BgInformation[1].Height);
        sscanf(buffer, "BG0_SIZE:%dx%d", &LevelInfo->BgInformation[0].Width, &LevelInfo->BgInformation[0].Height);

        // Description (last because slowest).
        if(sscanf(buffer, "DESC:%[^\n]", LevelInfo->Information.Description)== 1){
            while(1){
                char* newline;
                newline = strchr(LevelInfo->Information.Description, '|');
                if(newline == NULL) break;
                *newline = 10;
            }
        }
    }
    fclose(file);
    // Load effects.
    LoadEffects(selection);
}

void Level_CreateBackgrounds(RUE_LevelInfo *LevelInfo){
    if(strcmp("NULL", LevelInfo->BgInformation[0].Location) != 0){
        NF_LoadTiledBg(LevelInfo->BgInformation[0].Location, "bg0",
                        LevelInfo->BgInformation[0].Width, LevelInfo->BgInformation[0].Height);

        NF_CreateTiledBg(0, 0, "bg0");
    }
    if(strcmp("NULL", LevelInfo->BgInformation[1].Location) != 0){
        NF_LoadTiledBg(LevelInfo->BgInformation[1].Location, "bg1",
                        LevelInfo->BgInformation[1].Width, LevelInfo->BgInformation[1].Height);

        NF_CreateTiledBg(0, 1, "bg1");
    }
    if(strcmp("NULL", LevelInfo->BgInformation[2].Location) != 0){
        NF_LoadTiledBg(LevelInfo->BgInformation[2].Location, "bg2",
                        LevelInfo->BgInformation[2].Width, LevelInfo->BgInformation[2].Height);

        NF_CreateTiledBg(0, 2, "bg2");
    }
    if(strcmp("NULL", LevelInfo->BgInformation[3].Location) != 0){
        NF_LoadTiledBg(LevelInfo->BgInformation[3].Location, "bg3",
                        LevelInfo->BgInformation[3].Width, LevelInfo->BgInformation[3].Height);

        NF_CreateTiledBg(0, 3, "bg3");
    }

    // Create main collision map.
    NF_LoadCollisionBg(LevelInfo->CMap.Location, 0, LevelInfo->CMap.Width, LevelInfo->CMap.Height);
}


////////////////////////////////
// Wrappers to facilitate usage
////////////////////////////////

void Level_ApplyCameraBoundaries(int* X, int* Y, RUE_LevelInfo *LevelInfo){
    if(*X < LevelInfo->CameraBoundsX[0]) *X = LevelInfo->CameraBoundsX[0];
    else if(*X > LevelInfo->CameraBoundsX[1]) *X = LevelInfo->CameraBoundsX[1];

    if(*Y < LevelInfo->CameraBoundsY[0]) *Y = LevelInfo->CameraBoundsY[0];
    else if(*Y > LevelInfo->CameraBoundsY[1]) *Y = LevelInfo->CameraBoundsY[1];
}
