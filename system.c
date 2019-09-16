#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "config.h"
#include "structs.h"

SDL_Window* System_Start(char* window_name,int window_width,int window_height)
{
    /*Starting SDL and SDL_image*/
    SDL_Window* window;
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    /*Creating the Game Window*/
    window = SDL_CreateWindow( window_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);
    return window;
}

void System_Stop(SDL_Window* window)
{
    /*Destroing the Game Window and Stopping the SDL and SDL_image*/
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* System_Image_LoadBMP(char* image_path,SDL_Renderer* renderer)
{
    /*Creating the textures and loading the image*/
    SDL_Texture* texture;
    SDL_Surface* surface;
    surface = SDL_LoadBMP(image_path);
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    return texture;

}

SDL_Texture* System_Image_LoadPNG(char* image_path,SDL_Renderer* renderer)
{
    /*Creating the textures and loading the image*/
    SDL_Texture* texture;
    SDL_Surface* surface;
    surface = IMG_Load(image_path);
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    return texture;
}

SystemFile System_File_Open(char* path)
{
    /*Creating files and loop controlers*/
    FILE* archive;
    SystemFile file;

    int i = 0;
    int j = 0;
    int k = 0;
    int loop_count = 0;
    file.ch_amount = 0;
    file.line_amount = 1;

    /*Opening the archive*/
    archive = fopen(path,"r");

    /*Getting the archive´s line amount, char amount(bigest line) and size*/
    while((i = fgetc(archive)) != EOF)
    {
        loop_count++;

        if (i == '\n')
        {
            file.line_amount++;
            loop_count = 0;
        }else if(file.ch_amount<loop_count)
        {
            file.ch_amount = loop_count;
        }

    }

    fseek(archive, 0L, SEEK_END);
    file.size = ftell(archive);
    fseek(archive, 0L, SEEK_SET);

    /*Aloccaing the memory to store the file*/
    file.line = malloc(sizeof(char*) * file.line_amount);
    for (loop_count = 0; loop_count < file.line_amount; loop_count++)
    {
        file.line[loop_count] = malloc(sizeof(char) * file.ch_amount);
    }

    /*Getting file lines and chars and saving in the memory*/
    while((i = fgetc(archive)) != EOF)
    {
        if (i == '\n')
        {
            j++;
            k=0;
        }else
        {
            file.line[j][k] = i;
            k++;
        }
    }

    fclose(archive);
    return file;
}

void System_File_Close(SystemFile file)
{
    int loop_count = 0;
    /*Releasing the Memory used to open the file*/   
    for (loop_count = 0; loop_count < file.line_amount; loop_count++)
    {
        free(file.line[loop_count]);
    }
    free(file.line);
}