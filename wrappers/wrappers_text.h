#ifndef WRAPPERS_TEXT_H
#define WRAPPERS_TEXT_H
#include <nf_lib.h>

/*
    Displays text in a box.

    @param screen Screen for the text to be displayed.
    @param layer Text layer.
    @param x X tile position of the text.
    @param y Y tile position of the text.
    @param text Text to be displayed.
    @param start Start of the text.
    @param end End of the text.
*/
void BoxText(u8 screen, u8 layer, u16 x, u16 y, const char* text, u32 start, u32 end);

/*
    Inits a ton of colors to use with ``NF_SetTextColor``.

    @param screen Screen.
    @param layer Text layer.
*/
void InitColoredText(u8 screen, u8 layer);

/*
    Legacy func, this is actually pretty useless but I love it so I'll leave it there :)
    Displays random color every letter.

    @param screen Screen for the text to be displayed.
    @param layer Text layer.
    @param x X tile position of the text.
    @param y Y tile position of the text.
    @param text Text to be displayed.
    @param vbl Makes a typewriter effect.
*/
void Colored_Text(u8 screen, u8 layer, u16 x, u16 y, const char* text, bool vbl = false);

/*
    Typewriter effect... I use it for easier colored text.

    @param screen Screen for the text to be displayed
    @param layer Text layer.
    @param x X tile position of the text.
    @param y Y tile position of the text.
    @param string Text to be displayed
*/
void TypeWriterEffect(int screen, u32 layer, u32 x, u32 y, const char* string);


#endif
