#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "character.h"
#include "rooms.h"
//item initializer
struct Item *item(char* name, struct Item *next){
    struct Item *newItem = (struct Item *) malloc(sizeof(struct Item));
    if(newItem == NULL){
        return NULL;
    }else{
        newItem->name = name;
        newItem->next = next;
    }
    return newItem;

}
//allows avatar to pick up items if they exist in the room by running thru item array in room
void take_item(char* item, struct Item *inventory, struct Item *items){
    struct Item *curr_node = items;
    struct Item *prev_node = NULL;
    while(strcmp(curr_node->name, item) != 0){
        prev_node = curr_node;
        curr_node = curr_node->next;
        if(curr_node == NULL){
            printf("this item does not exist in this room\n");
            break;
        }
    }
    if(curr_node != NULL && strcmp(curr_node->name, item) == 0){
        struct Item *player_inventory_node = inventory;
        while(player_inventory_node->next != NULL){
            player_inventory_node = player_inventory_node->next;
        }
        prev_node->next = curr_node->next;
        curr_node->next = NULL;
        player_inventory_node->next = curr_node;
    }
}
//allows avatar to drop items if they exist in their inventory by running thru item array in inventory
void drop_item(char* item, struct Item *inventory, struct Item *items){
    struct Item *curr_node = inventory;
    struct Item *prev_node = NULL;
    while(strcmp(curr_node->name, item) != 0){
        prev_node = curr_node;
        curr_node = curr_node->next;
        if(curr_node == NULL){
            printf("this item does not exist in your inventory\n");
            break;
        }
    }
    if(curr_node != NULL && strcmp(curr_node->name, item) == 0){
        struct Item *room_inventory = items;
        while(room_inventory->next != NULL){
            room_inventory = room_inventory->next;
        }
        prev_node->next = curr_node->next;
        curr_node->next = NULL;
        room_inventory->next = curr_node;
    }
}