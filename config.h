#ifndef CONFIG_H
#define CONFIG_H
#include <stdio.h>

typedef unsigned char uint8;
typedef unsigned int uint32;

/*Island Size Configurations*/
#define ISLAND_WIDTH 40
#define ISLAND_HEIGHT 22
#define TILE_SIZE 32

/*Island Generation Configurations*/
#define TREE_PERCENTAGE 60

extern int renderWidth;
extern int renderHeight;

extern int PLATFORM_MAX_WIDTH;
extern int PLATFORM_MAX_HEIGHT;
extern int PLATFORM_MIN_WIDTH;
extern int PLATFORM_MIN_HEIGHT;


/*Island Map Configurations*/
#define AIR '.'
#define DIRT '#'
#define GRASS 'G'
#define RIGHT_CORNER 'C'
#define LEFT_CORNER 'c'
#define RIGHT_SIDE 'S'
#define LEFT_SIDE 's'
#define LADDER 'L'


#endif