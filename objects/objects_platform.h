#include "../player/objects_player.h" // This object interacts with the player.

#ifndef OBJECTS_PLATFORM_H
#define OBJECTS_PLATFORM_H


typedef struct{
    int TargetX;
    int TargetY;
    int StartX;
    int StartY;
    bool MoveX;
    bool MoveY;
    int MaxSpeed;
} Object16_Platform_MoveCode;
/*
    Platform object.
*/
class Object16_Platform {
    public:
        //Position of the Object16.
        Object_Position Position;
        
        Object16_Platform_MoveCode MoveCode;

        int ID; // Sprite ID.


        /*
            Create function... It sets the ID, X and Y.

            @param id ID of the Object16.
            @param x X coordinate of the Object16.
            @param Y Y coordinate of the Object16.
        */
        void Create(int id, int x, int y, int TargetX, int TargetY, int speed);



        /*
            Create GFX.
        */
        static inline void CreateGfx(){
            LoadSpritePal(0, "engine/sprites/objects/palette", 1, 1);
            LoadSpriteGfx(0, "engine/sprites/objects/platform", 2, 2, 64, 32, true);
        }

        /*
            Update function... It updates screen coordinates, it checks for collision with player.

            @param Player Pointer to ``Object16_Player``
        */
        void Update(Object16_Player* Player);
};

#endif
