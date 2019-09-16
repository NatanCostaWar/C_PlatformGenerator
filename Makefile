OBJS =  main.c system.c config.c
CC = gcc
INCLUDE_PATHS = -IC:\Users\natan\Desktop\Drive\C_IslandGenerator\libs\SDL2\include
LIBRARY_PATHS = -LC:\Users\natan\Desktop\Drive\C_IslandGenerator\libs\SDL2\lib
COMPILER_FLAGS = -mconsole -std=c89 -pedantic
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
OBJ_NAME = main

all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -g -o $(OBJ_NAME)