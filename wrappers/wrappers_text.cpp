#include <nf_lib.h>

void BoxText(u8 screen, u8 layer, u16 x, u16 y, const char* text, u32 start, u32 end){
    // Duplicate the string.
    char* substring = strdup(text);
    substring[end] = 0; // Set end.

    NF_WriteText(screen, layer, x, y, substring + start);

    free(substring);
}

void InitColoredText(u8 screen, u8 layer){
    // This just defines a ton of text colors.
	NF_DefineTextColor(screen, layer, 1, 31, 0, 0);
	NF_DefineTextColor(screen, layer, 2, 0, 31, 0);
	NF_DefineTextColor(screen, layer, 3, 0, 0, 31);
	NF_DefineTextColor(screen, layer, 4, 31, 0, 31);
	NF_DefineTextColor(screen, layer, 5, 0, 31, 31);
	NF_DefineTextColor(screen, layer, 6, 31, 31, 0);
	NF_DefineTextColor(screen, layer, 7, 25, 25, 25);
	NF_DefineTextColor(screen, layer, 8, 20, 20, 20);
	NF_DefineTextColor(screen, layer, 9, 0, 0, 0);
}

void Colored_Text(u8 screen, u8 layer, u16 x, u16 y, const char* text, bool vbl){
    u16 numtext = 0;
    char substring[2];
    substring[1] = 0;
    while(numtext < strlen(text)){
        substring[0] = text[numtext];

        NF_SetTextColor(screen, layer, rand() % 9);
        NF_WriteText(screen, layer, x + numtext, y, substring);

        if(vbl==true){
            NF_UpdateTextLayers();
            swiWaitForVBlank();
            swiWaitForVBlank();
            swiWaitForVBlank();
        }
        numtext ++;
    }
}

void TypeWriterEffect(int screen, u32 layer, u32 x, u32 y, const char* string){
    u32 string_size = strlen(string) << 8;

    for(u32 i = 0; i < string_size + 1;  i += 128){
        BoxText(screen, layer, x, y, string, 0, i >> 8);
        NF_UpdateTextLayers();
        swiWaitForVBlank();
    }
}
