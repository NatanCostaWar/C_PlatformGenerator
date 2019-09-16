#ifndef STRUCT_H
#define STRUCT_H
#include <stdio.h>
#include <SDL2/SDL.h>


/* Struct used to open a file and save it configs like number of lines and charcters and the size of the archive */
typedef struct SystemFile
{
	char** line;
	int line_amount;
	int ch_amount;
	int size;
}SystemFile;

typedef struct SystemImage
{
	SDL_Texture* image;
	SDL_Rect rect;
}SystemImage;

#endif