#ifndef LEVEL_LOADING_H
#define LEVEL_LOADING_H

#include <nds.h>

/*
    Level data struct... This is meant to be used with ``LoadLevelData``
*/
typedef struct{
    struct{
        char* Name; // Level name.
        int NameColor; // Name color when starting up.
        char* Description; // Level description.
    } Information;

    int PlayerX; // Initial Player X position.
    int PlayerY; // Initial Player Y position.
    int CameraBoundsX[2]; // Camera X bounds, these are two :P
    int CameraBoundsY[2]; // Camera Y bounds, these are two :P

    struct{
        char* Location; // Collision map location.
        int Width; // Collision map width.
        int Height; // Collision map height.
    } CMap;

    /*
        Bg information struct :P
    */
    struct{
        char* Location; // Location of the background.
        int Width; // Width of the background.
        int Height; // Height of the background.
    } BgInformation[4];
} RUE_LevelInfo;

/*
    Loads level data from ``info.d16i`` in ``levels/(selection)/info.d16i``

    @param selection Level number.
    @param level_info Pointer to level data.a
*/
void LoadLevelData(u8 selection, RUE_LevelInfo *LevelInfo);
/*
    Frees up level data... This is to reduce mem leaks :)

    @param level_info Level Information to be wiped
*/
void FreeLevelData(RUE_LevelInfo *LevelInfo);
/*
    Creates backgrounds using level data... It was messy so I decided to implement
    it on a function :)

    @param level_info level data.
*/
void Level_CreateBackgrounds(RUE_LevelInfo *LevelInfo);

/*
    Sets boundaries for camera.

    @param X pointer to BgScroll.X
    @param Y pointer to BgScroll.Y
    @param level Pointer to level data.
*/
void Level_ApplyCameraBoundaries(int* X, int* Y, RUE_LevelInfo *LevelInfo);

#endif
