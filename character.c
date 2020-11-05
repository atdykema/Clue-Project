#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "character.h"
#include "rooms.h"
#include "item.h"
//character initializer
struct Character *character(char* name, struct Room *location, struct Character *next){
   struct Character *newCharacter = (struct Character *) malloc(sizeof(struct Room));
    if(newCharacter == NULL){
        return NULL;
    }
    else{
        newCharacter->name = name;
        newCharacter->location = location;
        newCharacter->next = next;
    }

    return newCharacter;
}

//moves the suspect character to the room the avatar is in
void move_character(struct Character *character, struct Room *new_location){
    struct Character *curr_node = character->location->characters;
    struct Character *prev_node = NULL;
if(strcmp(character->location->name, new_location->name) != 0){

   
    while(strcmp(curr_node->name, character->name) != 0){
        prev_node = curr_node;
        curr_node = curr_node->next;
        if(curr_node == NULL){
            printf("error performing move_character");
            break;
        }
    }
    if(strcmp(curr_node->name, character->name) == 0){
        struct Character *room_character_list = new_location->characters;
        while(room_character_list->next != NULL){
            room_character_list = room_character_list->next;
        }
        prev_node->next = curr_node->next;
        curr_node->next = NULL;
        room_character_list->next = curr_node;
        character->location = new_location;
    }
}
}


