/*
    This is just the defines of the player code.
*/

#include "wrappers.h"
#include "objects_wrappers.h"
#include <nf_lib.h>

#ifndef OBJECTS_PLAYER_H
#define OBJECTS_PLAYER_H

/*
    Health object, it is internally used by the Player object.
    @note This object shouldn't be used unless it's on the player class :P
*/
class Object16_Health{
    public:
        struct{
            int X, Y;
        } Position;

        struct{
            mm_sound_effect Handle;
            int Counter;
        } Sound;
        int HealthCounter;
        int ID;
        int iframes;

        void Create(int id);

        void Update();
};

/*
    Player Object, uses movement. Supports animation

    @note If you don't allow the object to scroll the background it may break.
*/
class Object16_Player{
    public:
        // Position of the Object16.
        struct{
            int X, Y; // Coordinates.
            int sX, sY; // Screen coordinates.
            int vY, vX; // Speed.
        } Position;

        // Background scrolling.
        struct{
            int X, Y;
            int vX, vY;
            u8 layer;
        } BgScroll;

        // Jump sound.
        struct{
                mm_sound_effect Handle;
        } JumpSound;

        u8 ID; // Sprite ID of the Object16.
        u16 CrystalsCollected; // Collected crystals.
        Object16_Insider_AnimationConfig Animation; // Animation handler... it's best to not mess with this.
        Object16_Health Health;

        /*
            Creates a object...

            @param screen Screen for the object to be created on.
            @param id ID of the object.
            @param x X position of the object.
            @param y Y position of the object.
        */
        void Create(int screen, u32 id, s32 x, s32 y);

        // Makes this Object16 move horizontally.
        void Move();

        // Makes this Object16 have gravity physics.
        void Gravity();

        // Updates the sprite to the values of the Object16.
        void Update();

        void UpdateHealth();

        // Updates background position.
        void UpdateBg();
};

#endif
