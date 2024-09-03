#include <nds.h>
#include <maxmod9.h>
#include <nf_lib.h>

#ifndef ULTRA_WRAPPERS_H
#define ULTRA_WRAPPERS_H


//keys held right now.
extern int kheld;
//keys pressed right now.
extern int kdown;
//keys released right now.
extern int kreleased;

/*
    Initializes NFlib with default settings.
*/
void InitNFlib();

// Function that does... Nothing :P
// This is just here so that default arguments work properly
bool Nothing();

/*
    Loads a sprite palette to both RAM and VRAM.
    @param screen Screen (0-1)
    @param file Palette to load in nitroFS.
    @param ramid RAM slot to be loaded into.
    @param vramid VRAM slot to be loaded into.
*/
static inline void LoadSpritePal(u8 screen, const char* file, u8 ramid, u8 vramid){
    NF_LoadSpritePal(file,ramid);
    NF_VramSpritePal(screen,ramid,vramid);
}

/*
    Loads a sprite GFX to both RAM and VRAM.
    @param screen Screen (0-1)
    @param file GFX to load in nitroFS.
    @param ramid RAM slot to be loaded into.
    @param vramid VRAM slot to be loaded into.
*/
static inline void LoadSpriteGfx(u8 screen, const char* file, u8 ramid, u8 vramid, s32 width, s32 height, bool keepframes){
    NF_LoadSpriteGfx(file,ramid,width,height);
    NF_VramSpriteGfx(screen,ramid,vramid,keepframes);
}

// Waits a few frames :)
bool Wait(u32 frames, bool (*func)(void) = &Nothing);

// Deletes every sprite on the screen, it doesn't free it's VRAM though.
void DeleteEverySprite();

/*
    Calls scanKeys, updates values of kheld kdown and kreleased, basically scans inputs.
    @note Doesn't do touchscreen, yet :P
*/
void D_ScanKeys();

/*
    Updates OAM.

    @param screen Screen to update OAM to, 2 updates both screens.
*/
void UpdateOAM(u8 screen);

/*
    Sets MaxMod sound effect handles to default settings.

    @param Handle Pointer to handle.
*/
void MaxModDefaultHandle(mm_sound_effect * Handle, mm_word id);

#endif
