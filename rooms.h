#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//room header
struct Room{
    char* name;
    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;
    struct Item *items;
    char* description;
    struct Character *characters;
};
//room initializer
struct Room * room(char* name, struct Item * items, char* description, struct Room *north, struct Room *south, struct Room *east, struct Room *west, struct Character *characters);
