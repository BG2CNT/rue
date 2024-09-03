#include "objects_player.h" // This object interacts with the player.

#ifndef OBJECTS_CRYSTALS_H
#define OBJECTS_CRYSTALS_H


/*
    Crystal Object, collectable. Interacts with player and does support sprite animation.
*/
class Object16_Crystal {
    public:
        //Position of the Object16.
        struct{
            int X, Y; //Coordinates.
            int sX, sY; //Screen coordinates.
        } Position;

        int ID; // Sprite ID.
        bool Collected; // If crystal was collected.
        Object16_Insider_AnimationConfig AnimationHandler; // Animation handler... it's best to not mess with this.


        /*
            Create function... It sets the ID, X and Y.

            @param id ID of the Object16.
            @param x X coordinate of the Object16.
            @param Y Y coordinate of the Object16.
        */
        void Create(int id, int x, int y);



        /*
            Create GFX.
        */
        static inline void CreateGfx(){
            LoadSpritePal(0, "engine/sprites/pal", 1, 1);
            LoadSpriteGfx(0, "engine/sprites/crystal", 2, 2, 16, 16, true);
        }



        /*
            Update function... It updates screen coordinates, it checks for collision with player.

            @param Player Pointer to ``Object16_Player``
        */
        void Update(Object16_Player* Player);
};

#endif
