#ifndef SYSTEM_H
#define SYSTEM_H
#include <stdio.h>
#include "structs.h"

/*strtg*/
SDL_Window* System_Start(char* window_name,int window_width,int window_height); /* Function to Start SDL, SDL_image and Create the game window */
void System_Stop(SDL_Window* window); /* Function to Stop the game (Stops SDL and SDL_image) */
SDL_Texture* System_Image_LoadBMP(char* path,SDL_Renderer* renderer); /* Function to Load a image in BMP Format */
SDL_Texture* System_Image_LoadPNG(char* path,SDL_Renderer* renderer); /* Function to Load a image in PNG Format */
SystemFile System_File_Open(char* path); /* This function opens a file and return a SystemFile struct */
void System_File_Close(SystemFile file); /* This function closes a file and free the content */
/*stptg*/

#endif