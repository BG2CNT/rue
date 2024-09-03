#include "level_loading.h"
#include <nds.h>
#include <filesystem.h>
#include "../effects/effect_loading.h"
#include <nf_lib.h>

void FreeLevelData(levelinfodata* level_info){
    free(level_info->cmaploc);
    free(level_info->name);
    free(level_info->description);
    for(u8 i = 0; i < 4; i ++){
        free(level_info->bg_info[i].loc);
        level_info->bg_info[i].width = 0;
        level_info->bg_info[i].height = 0;
    }
    level_info->name = NULL;
    level_info->cmaploc = NULL;
    level_info->description = NULL;
}


void LoadLevelData(u8 selection, levelinfodata* level_info){
    char buffer[150];

    // Allocate memory.
    level_info->name = (char*) malloc(40);
    level_info->cmaploc = (char*) malloc(150);
    level_info->description = (char*) malloc(150);
    for(u8 i = 0; i < 4; i ++) level_info->bg_info[i].loc = (char*) malloc(80); // Allocate memory for background location.

    // Open file.
    sprintf(buffer, "levels/%d/info.d16i", selection); // Get file location.
    FILE* file = fopen(buffer, "r"); // Open.

    while(fgets(buffer, 150, file)) {
        sscanf(buffer, "NAME:%[^\n]", level_info->name);
        sscanf(buffer, "NAME_COL:%d", &level_info->name_color);
        sscanf(buffer, "PLAYER_POS:%dx%d", &level_info->player_x, &level_info->player_y);
        sscanf(buffer, "CMAP_SIZE:%dx%d", &level_info->cmapwidth, &level_info->cmapheight);
        sscanf(buffer, "CAMERA_BOUNDS_X:%dx%d", &level_info->camera_bounds_x[0], &level_info->camera_bounds_x[1]);
        sscanf(buffer, "CAMERA_BOUNDS_Y:%dx%d", &level_info->camera_bounds_y[0], &level_info->camera_bounds_y[1]);
        sscanf(buffer, "CMAP_LOC:%s", level_info->cmaploc);

        sscanf(buffer, "BG3:%s", level_info->bg_info[3].loc);
        sscanf(buffer, "BG2:%s", level_info->bg_info[2].loc);
        sscanf(buffer, "BG1:%s", level_info->bg_info[1].loc);
        sscanf(buffer, "BG0:%s", level_info->bg_info[0].loc);
        sscanf(buffer, "BG3_SIZE:%dx%d", &level_info->bg_info[3].width, &level_info->bg_info[3].height);
        sscanf(buffer, "BG2_SIZE:%dx%d", &level_info->bg_info[2].width, &level_info->bg_info[2].height);
        
        sscanf(buffer, "BG1_SIZE:%dx%d", &level_info->bg_info[1].width, &level_info->bg_info[1].height);
        sscanf(buffer, "BG0_SIZE:%dx%d", &level_info->bg_info[0].width, &level_info->bg_info[0].height);

        // Description (last because slowest).
        while(1){
            char* newline;
            newline = strchr(buffer, '|');
            if(newline == NULL) break;
            *newline = 10;
        }
        sscanf(buffer, "DESC:%[^\n]", level_info->description);
    }
    fclose(file);
    // Load effects.
    LoadEffects(selection);
}

void Level_CreateBackgrounds(levelinfodata* level_info){
    if(strcmp("NULL", level_info->bg_info[0].loc) != 0){
        NF_LoadTiledBg(level_info->bg_info[0].loc, "bg0",
                        level_info->bg_info[0].width, level_info->bg_info[0].height);

        NF_CreateTiledBg(0, 0, "bg0");
    }
    if(strcmp("NULL", level_info->bg_info[1].loc) != 0){
        NF_LoadTiledBg(level_info->bg_info[1].loc, "bg1",
                        level_info->bg_info[1].width, level_info->bg_info[1].height);

        NF_CreateTiledBg(0, 1, "bg1");
    }
    if(strcmp("NULL", level_info->bg_info[2].loc) != 0){
        NF_LoadTiledBg(level_info->bg_info[2].loc, "bg2",
                        level_info->bg_info[2].width, level_info->bg_info[2].height);

        NF_CreateTiledBg(0, 2, "bg2");
    }
    if(strcmp("NULL", level_info->bg_info[3].loc) != 0){
        NF_LoadTiledBg(level_info->bg_info[3].loc, "bg3",
                        level_info->bg_info[3].width, level_info->bg_info[3].height);

        NF_CreateTiledBg(0, 3, "bg3");
    }

    // Create main collision map.
    NF_LoadCollisionBg(level_info->cmaploc, 0, level_info->cmapwidth, level_info->cmapheight);
}


////////////////////////////////
// Wrappers to facilitate usage
////////////////////////////////

void Level_ApplyCameraBoundaries(int* X, int* Y, levelinfodata* level){
    if(*X < level->camera_bounds_x[0]) *X = level->camera_bounds_x[0];
    else if(*X > level->camera_bounds_x[1]) *X = level->camera_bounds_x[1];

    if(*Y < level->camera_bounds_y[0]) *Y = level->camera_bounds_y[0];
    else if(*Y > level->camera_bounds_y[1]) *Y = level->camera_bounds_y[1];
}
