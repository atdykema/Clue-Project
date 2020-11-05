#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "character.h"
#include "rooms.h"
#include "item.h"
//room initializer
struct Room * room(char* name, struct Item * items, char* description, struct Room *north, struct Room *south, struct Room *east, struct Room *west, struct Character *characters){
    struct Room *newRoom = (struct Room *) malloc(sizeof(struct Room));
    if(newRoom == NULL){
        return NULL;
    }
    else{
        newRoom->name = name;
        newRoom->items = items;
        newRoom->description = description;
        newRoom->characters = characters;
        newRoom->north = north;
        newRoom->south = south;
        newRoom->east = east;
        newRoom->west = west;
    }

    return newRoom;
}