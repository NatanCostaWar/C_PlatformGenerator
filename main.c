#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "system.h"
#include "config.h"
#include "structs.h"

int main(int argc,char** argv)
{

    /*Function Variables*/
    int quit = 0;
    int i = 0;
    int j = 0;
    int count = 0;
    int random = 0;
    SDL_Rect platform;

    /*System Variables*/
    SDL_Renderer* renderer = NULL;
    SDL_Event event;
    SDL_Window* window;

    /*Island Variables*/
    char islandMap[ISLAND_HEIGHT][ISLAND_WIDTH];
    SystemImage image;

    /*Creating the Preview Window*/
    window = System_Start("New Island", ISLAND_WIDTH*TILE_SIZE, ISLAND_HEIGHT*TILE_SIZE);
    /*Creating the Render*/
    renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);
    /*Just Some Configs*/
    srand(time(NULL));
    platform.x = 0;
    platform.y = 0;
    platform.w = 0;
    platform.h = 0;

    /*Creating The IslandMap:*/

    /*Filling With Air*/
    for (i = 0; i < ISLAND_HEIGHT; i++)
    {
        for (j = 0; j < ISLAND_WIDTH; j++)
        {
            islandMap[i][j] = AIR;
        }
    }
    /*Creating The Dirt:*/
    while(!quit)
    {
        /*Platfomr Type (Air or Dirty)*/
        random = rand() %2;
        /*Platform Largure*/
        platform.w = ((rand() % (PLATFORM_MAX_WIDTH - PLATFORM_MIN_WIDTH)) + PLATFORM_MIN_WIDTH);
        /*Platform Alture*/
        platform.h = ((rand() % (PLATFORM_MAX_HEIGHT - PLATFORM_MIN_HEIGHT)) + PLATFORM_MIN_HEIGHT);


        platform.y += platform.w;

        if (platform.y > ISLAND_WIDTH)
        {
            quit = 1;
            break;
        }
        

        /*If random = 0, will create a void space, if not will create a platform space*/
        if(random == 1)
        {
            for (i = 0; i < ISLAND_HEIGHT; i++)
            {
                for (j = 0; j < ISLAND_WIDTH; j++)
                {
                    if(i>platform.h)
                    {

                        if(j>=(platform.y - platform.w) && j<=platform.y)
                        {

                            islandMap[i][j] = DIRT;
                        }
                    }
                }
            }
        }

        platform.w = 0;
        platform.h = 0;
        
        
    }
    quit = 0;
    /*Putting The Grass*/
    for (i = 0; i < ISLAND_HEIGHT; i++)
    {
        for (j = 0; j < ISLAND_WIDTH; j++)
        {
            if(islandMap[i][j] == DIRT && islandMap[i-1][j] == AIR)
            {
                islandMap[i][j] = GRASS;
            }
        }
    }

    /*Putting The Grass Corners*/
    for (i = 0; i < ISLAND_HEIGHT; i++)
    {
        for (j = 0; j < ISLAND_WIDTH; j++)
        {
            if(islandMap[i][j] == GRASS && islandMap[i-1][j] == AIR && islandMap[i][j-1] == AIR)
            {
                islandMap[i][j] = LEFT_CORNER;
            }
            if(islandMap[i][j] == GRASS && islandMap[i-1][j] == AIR && islandMap[i][j+1] == AIR)
            {
                islandMap[i][j] = RIGHT_CORNER;
            }
        }
    }
    /*Putting The Dirt Side*/
    for (i = 0; i < ISLAND_HEIGHT; i++)
    {
        for (j = 0; j < ISLAND_WIDTH; j++)
        {
            if(islandMap[i][j] == DIRT && islandMap[i][j-1] == AIR)
            {
                islandMap[i][j] = LEFT_SIDE;
            }
            if(islandMap[i][j] == DIRT && islandMap[i][j+1] == AIR)
            {
                islandMap[i][j] = RIGHT_SIDE;
            }
        }
    }
    /*Creating The Platform over Platform*/
    for (i = 0; i < ISLAND_HEIGHT; i++)
    {
        for (j = 0; j < ISLAND_WIDTH; j++)
        {
            /*Left Side Ones*/
            if(islandMap[i][j]==GRASS && islandMap[i-1][j]==AIR && islandMap[i][j-1]==DIRT)
            {
                islandMap[i][j-1] = GRASS;
                islandMap[i][j-2] = LEFT_CORNER;
                for (count = i+1; count < ISLAND_HEIGHT; count++)
                {
                    islandMap[count][j-2] = LEFT_SIDE;
                }
            }
            /*Right Side Ones*/
            if(islandMap[i][j]==GRASS && islandMap[i-1][j]==AIR && islandMap[i][j+1]==DIRT)
            {
                islandMap[i][j+1] = GRASS;
                islandMap[i][j+2] = RIGHT_CORNER;
                for (count = i+1; count < ISLAND_HEIGHT; count++)
                {
                    islandMap[count][j+2] = RIGHT_SIDE;
                }
            }
                
        }
    }
    /*Putting The Ladders*/
    for (i = 0; i < ISLAND_HEIGHT; i++)
    {
        for (j = 0; j < ISLAND_WIDTH; j++)
        {
            /*Left Side Ones*/
            if(islandMap[i][j] == LEFT_CORNER && islandMap[i-1][j] != AIR)
            {
                count = i;
                while(islandMap[count-1][j]!=AIR)
                {
                    count--;
                    islandMap[count][j] = LADDER;
                }
                
            }
            /*Right Side Ones*/
            if(islandMap[i][j] == RIGHT_CORNER && islandMap[i-1][j] != AIR)
            {
                count = i;
                while(islandMap[count-1][j]!=AIR)
                {
                    count--;
                    islandMap[count][j] = LADDER;
                }
            }
                
        }
    }

    /*BETA TEST CODE DELETE THIS CRAP

    Trying to Make the Ligations
    for (i = 0; i < ISLAND_HEIGHT; i++)
    {
        for (j = 0; j < ISLAND_WIDTH; j++)
        {
            if (islandMap[i][j] == RIGHT_CORNER)
            {
                count = 1;
                while(islandMap[i][j+count] == AIR)
                {
                    islandMap[i][j+count] = DIRT;
                    printf("INSIDE");
                    count++;
                }
                
            }
            
        }
    }

    END OF CRAP*/

    /*Printing*/
    for (i = 0; i < ISLAND_HEIGHT; i++)
    {
        for (j = 0; j < ISLAND_WIDTH; j++)
        {
            printf("%c",islandMap[i][j]);
        }
        printf("\n");
    }


    /*Rendering The Map On The Preview Window:*/

    /*Clearing the Render*/
    SDL_RenderClear(renderer);
    /*Rendering Background*/
    image.image = System_Image_LoadPNG("layers\\0_background\\1.png",renderer);
    image.rect.w = TILE_SIZE*ISLAND_WIDTH;
    image.rect.h = TILE_SIZE*ISLAND_HEIGHT;
    image.rect.x = 0;
    image.rect.y = 0;
    SDL_RenderCopy(renderer,image.image,NULL,&image.rect);

    for (i = 0; i < ISLAND_HEIGHT; i++)
    {
        for (j = 0; j < ISLAND_WIDTH; j++)
        {
            /*Rendering the Clouds*/
            if (i<ISLAND_HEIGHT/2)
            {
                random = rand() %400;
                if(random==1)
                {
                    random = ((rand() %10) +1);
                    image.image = System_Image_LoadPNG("layers\\1_sky\\1.png",renderer);
                    SDL_SetTextureAlphaMod(image.image, (random*25));
                    image.rect.w = ((int)((90*random)/10));
                    image.rect.h = ((int)((21*random)/10));
                    image.rect.x = j*TILE_SIZE;
                    image.rect.y = i*TILE_SIZE;
                    SDL_RenderCopy(renderer,image.image,NULL,&image.rect);

                }else if(random==2)
                {
                    random = ((rand() %10) +1);
                    image.image = System_Image_LoadPNG("layers\\1_sky\\2.png",renderer);
                    SDL_SetTextureAlphaMod(image.image, (random*25));
                    image.rect.w = ((int)((58*random)/10));
                    image.rect.h = ((int)((20*random)/10));
                    image.rect.x = j*TILE_SIZE;
                    image.rect.y = i*TILE_SIZE;
                    SDL_RenderCopy(renderer,image.image,NULL,&image.rect);
                }else if(random==3)
                {
                    random = ((rand() %10) +1);
                    image.image = System_Image_LoadPNG("layers\\1_sky\\3.png",renderer);
                    SDL_SetTextureAlphaMod(image.image, (random*25));
                    image.rect.w = ((int)((90*random)/10));
                    image.rect.h = ((int)((24*random)/10));
                    image.rect.x = j*TILE_SIZE;
                    image.rect.y = i*TILE_SIZE;
                    SDL_RenderCopy(renderer,image.image,NULL,&image.rect);
                } 
            }
            /*Rendering the Dirt*/
            if(islandMap[i][j]==DIRT)
            {
                image.image = System_Image_LoadPNG("layers\\3_tiles\\dirt.png",renderer);
                image.rect.w = 32;
                image.rect.h = 32;
                image.rect.x = j*TILE_SIZE;
                image.rect.y = i*TILE_SIZE;
                SDL_RenderCopy(renderer,image.image,NULL,&image.rect);
            }
            /*Rendering the Grass*/
            if(islandMap[i][j]==GRASS)
            {
                image.image = System_Image_LoadPNG("layers\\3_tiles\\grass.png",renderer);
                image.rect.w = 32;
                image.rect.h = 32;
                image.rect.x = j*TILE_SIZE;
                image.rect.y = i*TILE_SIZE;
                SDL_RenderCopy(renderer,image.image,NULL,&image.rect);
            }
            /*Rendering the Conners*/
            if(islandMap[i][j]==RIGHT_CORNER)
            {
                image.image = System_Image_LoadPNG("layers\\3_tiles\\right_corner.png",renderer);
                image.rect.w = 32;
                image.rect.h = 32;
                image.rect.x = j*TILE_SIZE;
                image.rect.y = i*TILE_SIZE;
                SDL_RenderCopy(renderer,image.image,NULL,&image.rect);
            }
            if(islandMap[i][j]==LEFT_CORNER)
            {
                image.image = System_Image_LoadPNG("layers\\3_tiles\\left_corner.png",renderer);
                image.rect.w = 32;
                image.rect.h = 32;
                image.rect.x = j*TILE_SIZE;
                image.rect.y = i*TILE_SIZE;
                SDL_RenderCopy(renderer,image.image,NULL,&image.rect);
            }
            /*Rendering the Sides*/
            if(islandMap[i][j]==RIGHT_SIDE)
            {
                image.image = System_Image_LoadPNG("layers\\3_tiles\\right_side.png",renderer);
                image.rect.w = 32;
                image.rect.h = 32;
                image.rect.x = j*TILE_SIZE;
                image.rect.y = i*TILE_SIZE;
                SDL_RenderCopy(renderer,image.image,NULL,&image.rect);
            }
            if(islandMap[i][j]==LEFT_SIDE)
            {
                image.image = System_Image_LoadPNG("layers\\3_tiles\\left_side.png",renderer);
                image.rect.w = 32;
                image.rect.h = 32;
                image.rect.x = j*TILE_SIZE;
                image.rect.y = i*TILE_SIZE;
                SDL_RenderCopy(renderer,image.image,NULL,&image.rect);
            }
            /*Rendering the Ladders*/
            if(islandMap[i][j]==LADDER)
            {
                image.image = System_Image_LoadPNG("layers\\3_tiles\\dirt.png",renderer);
                image.rect.w = 32;
                image.rect.h = 32;
                image.rect.x = j*TILE_SIZE;
                image.rect.y = i*TILE_SIZE;
                SDL_RenderCopy(renderer,image.image,NULL,&image.rect);

                image.image = System_Image_LoadPNG("layers\\4_objects\\1.png",renderer);
                image.rect.w = 32;
                image.rect.h = 32;
                image.rect.x = j*TILE_SIZE;
                image.rect.y = i*TILE_SIZE;
                SDL_RenderCopy(renderer,image.image,NULL,&image.rect);
            }
            if(islandMap[i][j]==LADDER && islandMap[i-1][j]==AIR)
            {
                image.image = System_Image_LoadPNG("layers\\3_tiles\\grass.png",renderer);
                image.rect.w = 32;
                image.rect.h = 32;
                image.rect.x = j*TILE_SIZE;
                image.rect.y = i*TILE_SIZE;
                SDL_RenderCopy(renderer,image.image,NULL,&image.rect);

                image.image = System_Image_LoadPNG("layers\\4_objects\\1.png",renderer);
                image.rect.w = 32;
                image.rect.h = 32;
                image.rect.x = j*TILE_SIZE;
                image.rect.y = i*TILE_SIZE;
                SDL_RenderCopy(renderer,image.image,NULL,&image.rect);
            }
            /*Rendering The Trees*/
            if (islandMap[i][j]==GRASS && islandMap[i-1][j]==AIR)
            {
                random = rand() %(4 + (100-TREE_PERCENTAGE));

                if(random == 1)
                {
                    image.image = System_Image_LoadPNG("layers\\2_details\\1.png",renderer);
                    image.rect.w = 96;
                    image.rect.h = 96;
                    image.rect.x = j*TILE_SIZE;
                    image.rect.y = (i*TILE_SIZE)-image.rect.h;
                    SDL_RenderCopy(renderer,image.image,NULL,&image.rect);
                }else if(random == 2)
                {
                    image.image = System_Image_LoadPNG("layers\\2_details\\2.png",renderer);
                    image.rect.w = 64;
                    image.rect.h = 64;
                    image.rect.x = j*TILE_SIZE;
                    image.rect.y = (i*TILE_SIZE)-image.rect.h;
                    SDL_RenderCopy(renderer,image.image,NULL,&image.rect);
                }else if(random == 3)
                {
                    image.image = System_Image_LoadPNG("layers\\2_details\\3.png",renderer);
                    image.rect.w = 64;
                    image.rect.h = 64;
                    image.rect.x = j*TILE_SIZE;
                    image.rect.y = (i*TILE_SIZE)-image.rect.h;
                    SDL_RenderCopy(renderer,image.image,NULL,&image.rect);
                }else if(random == 4)
                {
                    image.image = System_Image_LoadPNG("layers\\2_details\\4.png",renderer);
                    image.rect.w = 128;
                    image.rect.h = 128;
                    image.rect.x = (j*TILE_SIZE)-TILE_SIZE;
                    image.rect.y = (i*TILE_SIZE)-image.rect.h;
                    SDL_RenderCopy(renderer,image.image,NULL,&image.rect);
                }
            }
            /*Rendering the Grass*/
            if(islandMap[i][j]==GRASS || (islandMap[i][j]==LADDER && islandMap[i-1][j]==AIR))
            {
                image.image = System_Image_LoadPNG("layers\\5_grass\\2.png",renderer);
                image.rect.w = 32;
                image.rect.h = 32;
                image.rect.x = j*TILE_SIZE;
                image.rect.y = (i*TILE_SIZE)-TILE_SIZE;
                SDL_RenderCopy(renderer,image.image,NULL,&image.rect);
            }
            if(islandMap[i][j]==RIGHT_CORNER || islandMap[i][j]==LEFT_CORNER)
            {
                image.image = System_Image_LoadPNG("layers\\5_grass\\corners.png",renderer);
                image.rect.w = 32;
                image.rect.h = 32;
                image.rect.x = j*TILE_SIZE;
                image.rect.y = (i*TILE_SIZE)-TILE_SIZE;
                SDL_RenderCopy(renderer,image.image,NULL,&image.rect);
            }
        }
    }

    
    /*Rendering the Render*/
    SDL_RenderPresent(renderer);

    

    /*Keeping the Preview Window Opened*/
    while(!quit)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                quit = 1;
                break;   
            }
        }
    }

    System_Stop(window);
    
    return 0;
}