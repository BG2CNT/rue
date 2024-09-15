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
        Object_Position Position;

        // Sound handler.
        struct{
            mm_sound_effect Handle;
            int Counter;
        } Sound;

        int HealthCounter; // This is for checking how much health there is.
        int ID; // ID of the object.
        int iframes; // iframes, please don't touch unless you are making a object that interacts with the player

        /*
            Creates a health object.

            @param id ID of the object.
        */
        void Create(int id);

        /*
            Update function.
        */
        void Update();
};

/*
    Player Object, uses movement. Supports animation

    @note If you don't allow the object to scroll the background it may break.
*/
class Object16_Player{
    public:
        // Position of the Object16.
        Object_Position Position;

        // Speedcap.
        struct{
            int LimitX = 512, LimitY = 512;
            int AccelerationX = 64, AccelerationY = 51;
            int DeAccelerationX = 64;
        } Speeds;

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

        struct{
            int addgravity;
        } killswitches;

        struct{
            int timer;
            int touchingGround;
        } Jump_Timer;

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

        // Detects if player is jumping.
        static inline void StartJump(int *timer, int *touchingGround){
            *timer = 0;
            *touchingGround =  !(kheld&KEY_A || kheld&KEY_B);
        }
};

#endif
