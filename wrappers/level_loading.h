#ifndef LEVEL_LOADING_H
#define LEVEL_LOADING_H

#include <nds.h>

typedef struct{
    char* name;
    char* description;

    int player_x;
    int player_y;
    int name_color;
    int camera_bounds_x[2];
    int camera_bounds_y[2];

    char* cmaploc;
    int cmapwidth;
    int cmapheight;

    struct{
        char* loc;
        int width;
        int height;
    } bg_info[4];
}levelinfodata;

/*
    Loads level data from ``info.d16i`` in ``levels/(selection)/info.d16i``

    @param selection Level number.
    @param level_info Pointer to level data.a
*/
void LoadLevelData(u8 selection, levelinfodata* level_info);
/*
    Frees up level data... This is to reduce mem leaks :)

    @param level_info Level Information to be wiped
*/
void FreeLevelData(levelinfodata* level_info);
/*
    Creates backgrounds using level data... It was messy so I decided to implement
    it on a function :)

    @param level_info level data.
*/
void Level_CreateBackgrounds(levelinfodata* level_info);

/*
    Sets boundaries for camera.

    @param X pointer to BgScroll.X
    @param Y pointer to BgScroll.Y
    @param level Pointer to level data.
*/
void Level_ApplyCameraBoundaries(int* X, int* Y, levelinfodata* level);

#endif
