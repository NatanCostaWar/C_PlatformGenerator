#include <stdio.h>
#include "config.h"

int renderWidth = ISLAND_WIDTH*TILE_SIZE;
int renderHeight = ISLAND_HEIGHT*TILE_SIZE;

int PLATFORM_MAX_WIDTH = 10;
int PLATFORM_MAX_HEIGHT = ((int)(ISLAND_HEIGHT/1.5));
int PLATFORM_MIN_WIDTH = 3;
int PLATFORM_MIN_HEIGHT = ((int)(ISLAND_HEIGHT/4));