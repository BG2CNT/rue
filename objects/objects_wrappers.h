#include <nf_lib.h>

#ifndef OBJECTS_WRAPPERS_H
#define OBJECTS_WRAPPERS_H

// Defines for object animation
#define ANIM_NORMAL 1
#define ANIM_UPDOWN 2


typedef struct{
    int X, Y; // Coordinates.
    int sX, sY; // Screen coordinates.
    int vY, vX; // Speed.
} Object_Position;

/*
    Animation handler, please do not touch :P

    Use with the animation functions.
*/
class Object16_Insider_AnimationConfig {
    public:
        /*
            Contains variables usually for the inner working of the library
            Please, don't touch this unless you know what you are doing.
        */
        struct{
            bool animbool;
        } inner_workings;

        int Frame;
        u32 Speed; // Speed of the animation... It isn't FPS it's actually fixed point math.
        int Min_Frame; // First frame of the animation, in fixed point math.
        int Max_Frame; // Second frame of the animation, in fixed point math.
        u8 Anim_Type; // Animation type, these are ``ANIM_NORMAL`` and ``ANIM_UPDOWN``
        bool stopped;
};

/*
    Updates the sprite animation for any Object16 object that is compatible.

    @param anim Pointer to animation handler.
*/
void UpdateSpriteAnim(Object16_Insider_AnimationConfig* AnimationHandler);

/*
    Starts sprite animation for any Object that is compatible, needs to call ``UpdateSpriteAnim`` to work.

    @param animtype Type of animation, these are ``ANIM_NORMAL`` and ``ANIM_UPDOWN``
    @param startframe The first frame of the animation.
    @param endframe The last frame of the animation.
    @param speed Speed in fixed point.
    @param AnimationHandler Pointer to animation handler.
*/
void SpriteStartAnim(u8 AnimType, u16 StartFrame, u16 EndFrame, u8 Speed, Object16_Insider_AnimationConfig* AnimationHandler);

/*
    Stops sprite animation for any object that is compatible...
    @param AnimationHandler pointer to animation handler.
*/
static inline void StopSpriteAnim(Object16_Insider_AnimationConfig* AnimationHandler){
    AnimationHandler->Anim_Type = 0;
    AnimationHandler->Frame = 0;
}

/*
    Sets sX limits on sprite so that it doesn't wrap around the screen.

    @param sX int pointer to the X screen coordinates.
    @param sY int pointer to the Y screen coordinates.
    @param width Width of the object.
    @param height Height of the object.
*/
void SetObjectCameraLimits(int *sX, int *sY, int width, int height);


/*
    Checks if two points are in collision. Used mainly by objects since it's
    a great way to detect collision.

    @param X X coordinate of the first object.
    @param Y Y coordinate of the first object.
    @param sX X coordinate of the second object.
    @param sY Y coordinate of the second object.
    @param w Width of the second object.
    @param h Height of the second object.
*/
static inline bool GetObjectCollision(int X, int Y, int sX, int sY, int w, int h){
    return (Y < sY + h && Y > sY) && (X < sX + w && X > sX);
}

/*
    Gets screen coordinates of a sprite.

    @param sX screen X coordinate to write to.
    @param sY screen Y coordinate to write to.
    @param X X position of the object.
    @param Y Y position of the object.
    @param BgX Background X Scroll.
    @param BgY Background Y Scroll.
*/
static inline void GetScreenCoordinates(int *sX, int *sY, int X, int Y, int BgX, int BgY){
    *sX = (X) - (BgX) - 4;
    *sY = (Y) - (BgY) - 4;
}

#endif
