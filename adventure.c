#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "character.h"
#include "item.h"
#include "rooms.h"
//avatar header-----------------------------------------------------------------------------------------------------
struct Avatar{
    struct Room *location;
    struct Item *inventory;
};
//avatar initializer
struct Avatar * avatar(struct Room *location, struct Item *inventory){
    struct Avatar *new_avatar = (struct Avatar *) malloc(sizeof(struct Avatar));
    if(new_avatar == NULL){
        return NULL;
    }
    else{
        new_avatar->location = location;
        new_avatar->inventory = inventory;
    }

    return new_avatar;
}
//help command-----------------------------------------------------------------------------------------------------
//prints all of the commands in the game
void help(){
    printf("'help' - list all commands\n");
    printf("'list' - list all items, rooms and characters\n");
    printf("'look' - reveals rooms in all directions and characters/items in current room\n");
    printf("'go DIRECTION' - move your character to room in DIRECTION");
    printf("'take ITEM' - pick up ITEM in room room\n");
    printf("'drop ITEM' - drop ITEM into current room\n");
    printf("'inventory' - list all items in character's inventory\n");
    printf("'clue CHARACTER' - make a guess at who was the killer\n");
}
//list command-----------------------------------------------------------------------------------------------------
//just prints out all of the items, rooms and characters present in the game
void list(){
    printf("items: chain, dagger, pipe, pickaxe, kolibri, cleaver\n");
    printf("rooms: living room, dining room, study room, forum room, theater room, mail room, arsenal room, kitchen room, garden room\n");
    printf("characters: drew, chris, doug, jane, jill\n");
}
//look command-----------------------------------------------------------------------------------------------------
//prints out all of the items and charactrs in current room, lists rooms in all directions
void look(struct Avatar *player){
    struct Room *location = player->location;
    printf("*Current room: %s\n", player->location->name);
    if(location->items->next != NULL){
            struct Item *curr_item = location->items->next;
            while(curr_item != NULL){
                printf("%s ", curr_item->name);
                curr_item = curr_item->next;
            }
            printf("\n");
        }else{
            printf("No items in this room\n");
        }
    if(location->characters->next != NULL){
            struct Character *curr_character = location->characters->next;
            while(curr_character != NULL){
                printf("%s", curr_character->name);
                curr_character = curr_character->next;
            }
            printf("\n");
        }else{
            printf("No characters in this room\n");
        }
    if(location->north != NULL){
        printf("**Northern room: %s\n", location->north->name);
    }else{
        printf("**No room to the north\n");
    }

    if(location->south != NULL){
        printf("***Southern room: %s\n", location->south->name);
    }else{
        printf("***No room to the south\n");
    }

    if(location->east != NULL){
        printf("****Eastern room: %s\n", location->east->name);
    }else{
        printf("****No room to the east\n");
    }

    if(location->west != NULL){
        printf("*****Western room: %s\n", location->west->name);
    }else{
        printf("*****No room to the west\n");
    }


}
//go direction command-----------------------------------------------------------------------------------------------------
//allows the avatar to move between rooms, doesnt allow for moving through walls
void go_direction(char* destination, struct Avatar *player){
    if(strcmp(destination, "north") == 0){
        if(player->location->north != NULL){
            player->location = player->location->north;
        }else{
            printf("BONK! thats a wall silly\n");
        }    
    }
    else if(strcmp(destination, "south") == 0){
        if(player->location->south != NULL){
            player->location = player->location->south;
        }else{
            printf("BONK! thats a wall silly\n");
        }   
    }
    else if(strcmp(destination, "east") == 0){
        if(player->location->east != NULL){
            player->location = player->location->east;
        }else{
            printf("BONK! thats a wall silly\n");
        }   
    }
    else if(strcmp(destination, "west") == 0){
        if(player->location->west != NULL){
            player->location = player->location->west;
        }else{
            printf("BONK! thats a wall silly\n");
        }
    }   
    else{
        printf("error in moving direction\n");
    }

}
//inventory command-----------------------------------------------------------------------------------------------------
//prints out all items in avatars inventory
void inventory(struct Avatar *player){
    struct Item *curr_item = player->inventory;
    if(curr_item->next != NULL){
        curr_item = curr_item->next;
        while(curr_item != NULL){
            printf("%s\n", curr_item->name);
            curr_item = curr_item->next;
        }
    }else{
        printf("Your inventory is empty\n");
    }
}
//clue command-----------------------------------------------------------------------------------------------------
//checks to make sure correct item, character and room exist around avatar
int clue(struct Character *killer, struct Room *killer_room, struct Item *inventory, char* answer_room, char* answer_item, char* answer_character){
    int room_correct = 0;
    int character_correct = 0;
    int item_correct = 0;  
    if(strcmp(killer->name, answer_character) == 0){
        printf("Character: CORRECT\n");
        character_correct++;
    }else{
        printf("Character: FALSE\n");
    }
    if(strcmp(killer_room->name, answer_room) == 0){
        printf("Room: CORRECT\n");
        room_correct++;
    }else{
        printf("Room: FALSE\n");
    }
    
    struct Item *curr_node = killer_room->items->next; 
    int notFound = 0;
    while(curr_node != NULL){
        if(strcmp(curr_node->name, answer_item) == 0){
            printf("Item: CORRECT\n");
            item_correct++;
            notFound++;
            break;
        }
        curr_node = curr_node->next;
    }
    if(notFound == 0){
        curr_node = inventory->next;
        while(curr_node != NULL){
            if(strcmp(curr_node->name, answer_item) == 0){
                printf("Item: CORRECT\n");
                item_correct++;
                notFound++;
                break;
            }
            curr_node = curr_node->next;
        }

    }
    if(notFound == 0){
        printf("Item: FALSE\n");
    }
    if(room_correct == 1 && item_correct == 1 && character_correct == 1){
        printf("YOU WIN!\n");
        return 1;
    }else{
        return 0;
    }

}

//********************************************************MAIN METHOD*************************************************************************************************************************

int main(){

//spawn items-----------------------------------------------------------------------------------------------------------------------------------------------
    struct Item* item1 = item(NULL, NULL);
    struct Item* item2 = item(NULL, NULL);
    struct Item* item3 = item(NULL, NULL);
    struct Item* item4 = item(NULL, NULL);
    struct Item* item5 = item(NULL, NULL);
    struct Item* item6 = item(NULL, NULL);

 //-----------------------------------------------------------------------------------------------------------------
 //spawn rooms

    struct Character* dummy1 = character("dummy", NULL, NULL);
    struct Character* dummy2 = character("dummy", NULL, NULL);
    struct Character* dummy3 = character("dummy", NULL, NULL);
    struct Character* dummy4 = character("dummy", NULL, NULL);
    struct Character* dummy5 = character("dummy", NULL, NULL);
    struct Character* dummy6 = character("dummy", NULL, NULL);
    struct Character* dummy7 = character("dummy", NULL, NULL);
    struct Character* dummy8 = character("dummy", NULL, NULL);
    struct Character* dummy9 = character("dummy", NULL, NULL);
    struct Room* room1 = room(NULL, item("dummy", item1), "the room in which people apparently aren't always living", NULL, NULL, NULL, NULL, dummy1);
    struct Room* room2 = room(NULL, item("dummy", item2), "this room is a little spooky because no one actually uses it", NULL, NULL, NULL, NULL, dummy2);
    struct Room* room3 = room(NULL, item("dummy", item3), "if I lived here, this room would be left completely unused", NULL, NULL, NULL, NULL, dummy3);
    struct Room* room4 = room(NULL, item("dummy", item4), "you can give speeches here", NULL, NULL, NULL, NULL, dummy4);
    struct Room* room5 = room(NULL, item("dummy", item5), "great plays were once performed here", NULL, NULL, NULL, NULL, dummy5);
    struct Room* room6 = room(NULL, item("dummy", item6), "packages and mail is received here", NULL, NULL, NULL, NULL, dummy6);
    struct Room* room7 = room(NULL, item("dummy", NULL), "EXPLOSIONS! MORE EXPLOSIONS!", NULL, NULL, NULL, NULL, dummy7);
    struct Room* room8 = room(NULL, item("dummy", NULL), "best room in the house, its bulk season baby", NULL, NULL, NULL, NULL, dummy8);
    struct Room* room9 = room(NULL, item("dummy", NULL), "you take a second to stop and smell the tulips", NULL, NULL, NULL, NULL, dummy9);

    
//------------------------------------------------------------------------------------------------------------------
 //spawn character and main character
    struct Character* drew = character("drew", NULL, NULL);
    struct Character* chris = character("chris", NULL, NULL);
    struct Character* doug = character("doug", NULL, NULL);
    struct Character* jane = character("jane", NULL, NULL);
    struct Character* jill = character("jill", NULL, NULL);

    struct Avatar* player = avatar(NULL, item("dummy", NULL));

//assign room directions------------------------------------------------------------------------------------------------------------------
    room1->north = room2;
    room1->south = room3;
    room1->east = room4;
    room1->west = room5;


    room2->north = NULL;
    room2->south = room1;
    room2->east = room7;
    room2->west = room6;

    room3->north = room1;
    room3->south = NULL;
    room3->east = room8;
    room3->west = room9;


    room4->north = room7;
    room4->south = room8;
    room4->east = NULL;
    room4->west = room1;
    room4->items->next = item6;


    room5->north = room6;
    room5->south = room9;
    room5->east = room1;
    room5->west = NULL;
    room5->items->next = item5;


    room6->north = NULL;
    room6->south = room5;
    room6->east = room2;
    room6->west = NULL;
    room6->items->next = item4;

    room7->north = NULL;
    room7->south = room4;
    room7->east = NULL;
    room7->west = room2;
    room7->items->next = item3;

    room8->north = room4;
    room8->south = NULL;
    room8->east = NULL;
    room8->west = room3;
    room8->items->next = item2;

    room9->north = room5;
    room9->south = NULL;
    room9->east = room3;
    room9->west = NULL;
    room9->items->next = item1;
//randomization----------------------------------------------------------------------------------------------------------------------------------------------------------
    srand(time(NULL));
    
//randomization of rooms----------------------------------------------------------------------------------------------------------------------------------------------------------
    char* roomArray[9];
    char* roomName1 = "kitchen";
    roomArray[0] = roomName1;
    char* roomName2 = "mailroom";
    roomArray[1] = roomName2;
    char* roomName3 = "bathroom";
    roomArray[2] = roomName3;
    char* roomName4 = "gym";
    roomArray[3] = roomName4;
    char* roomName5 = "garden";
    roomArray[4] = roomName5;
    char* roomName6 = "arsenal";
    roomArray[5] = roomName6;
    char* roomName7 = "basement";
    roomArray[6] = roomName7;
    char* roomName8 = "bunker";
    roomArray[7] = roomName8;
    char* roomName9 = "bedroom";
    roomArray[8] = roomName9;

    
    for(int i = 0; i < 100; i++){
        int randNum1 = rand() % 9;
        int randNum2 = rand() % 9;
        char* temp = roomArray[randNum1];
        roomArray[randNum1] = roomArray[randNum2];
        roomArray[randNum2] = temp;
    }
    room1->name = roomArray[0];
    room2->name = roomArray[1];
    room3->name = roomArray[2];
    room4->name = roomArray[3];
    room5->name = roomArray[4];
    room6->name = roomArray[5];
    room7->name = roomArray[6];
    room8->name = roomArray[7];
    room9->name = roomArray[8];
//randomization of characters----------------------------------------------------------------------------------------------------------------------------------------------------

    struct Character *characterArray[5];
    characterArray[0] = drew;
    characterArray[1] = chris;
    characterArray[2] = doug;
    characterArray[3] = jane;
    characterArray[4] = jill;


    for(int i = 0; i < 100; i++){
        int randNum1 = rand() % 4;
        int randNum2 = rand() % 4;
        struct Character* temp = characterArray[randNum1];
        characterArray[randNum1] = characterArray[randNum2];
        characterArray[randNum2] = temp;
    }

    characterArray[0]->location = room1;
    room1->characters->next = characterArray[0];
    characterArray[1]->location = room2;
    room2->characters->next = characterArray[1];
    characterArray[2]->location = room3;
    room3->characters->next = characterArray[2];
    characterArray[3]->location = room4;
    room4->characters->next = characterArray[3];
    characterArray[4]->location = room5;
    room5->characters->next = characterArray[4];

    int randomAvatar = rand() % 9;
    if(randomAvatar == 0){
        player->location = room1;
    }else if(randomAvatar == 1){
        player->location = room2;
    }else if(randomAvatar == 2){
        player->location = room3;
    }else if(randomAvatar == 3){
        player->location = room4;
    }else if(randomAvatar == 4){
        player->location = room5;
    }else if(randomAvatar == 5){
        player->location = room6;
    }else if(randomAvatar == 6){
        player->location = room7;
    }else if(randomAvatar == 7){
        player->location = room8;
    }else if(randomAvatar == 8){
        player->location = room9;
}
//randomization of items--------------------------------------------------------------------------------------------------------------------------------------------------------

    char* itemArray[6];
    char* itemName1 = "chain";
    itemArray[0] = itemName1;
    char* itemName2 = "dagger";
    itemArray[1] = itemName2;
    char* itemName3 = "pipe";
    itemArray[2] = itemName3;
    char* itemName4 = "pickaxe";
    itemArray[3] = itemName4;
    char* itemName5 = "kolibri";
    itemArray[4] = itemName5;
    char* itemName6 = "cleaver";
    itemArray[5] = itemName6;

    for(int i = 0; i < 100; i++){
        int randNum1 = rand() % 5;
        int randNum2 = rand() % 5;
        char* temp = itemArray[randNum1];
        itemArray[randNum1] = itemArray[randNum2];
        itemArray[randNum2] = temp;
    }

    item1->name = itemArray[0];
    item2->name = itemArray[1]; 
    item3->name = itemArray[2];
    item4->name = itemArray[3];
    item5->name = itemArray[4];
    item6->name = itemArray[5];
//random answer------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    char* answer_room;
    char* answer_item;
    char* answer_character;
    int randomNum;

    randomNum = rand() % 8;
    answer_room = roomArray[randomNum];
    randomNum = rand() % 4;
    answer_character = characterArray[randomNum]->name;
    randomNum = rand() % 5;
    answer_item = itemArray[randomNum];
//********************************************************************MAIN*GAME*LOOP****************************************************************************************
    printf("Welcome to Clue!\n");
    int guesses = 0;
    int gameWon = 0;
    while(guesses < 10 && gameWon != 1){
        //code for getting command-------------------------------------------------------------------------------------------------------------
        char *buffer;
        size_t bufsize = 100;
        size_t characters;
        buffer = (char *)malloc(bufsize * sizeof(char));
        printf("-->Enter command: ");
        characters = getline(&buffer, &bufsize, stdin);
        if(characters <= 0){
            printf("try again \n");
            continue;
        }
        char *strtok_command = strtok(buffer, " \n");
        //looking for commands------------------------------------------------------------------------------------------------------------------
        //tokenizing the command to check the first word against valid commands, then checks second if it exists, returns "invalid " if command is invalid
        if(strcmp(strtok_command, "help") == 0){
            help();
            continue;
        }else if(strcmp("list", strtok_command) == 0){
            list();
            continue;
        }else if(strcmp("look", strtok_command) == 0){
            look(player);
            continue;
        }else if(strcmp("inventory", strtok_command) == 0){
            inventory(player);
            continue;
        }else if(strcmp("clue", strtok_command) == 0){
            strtok_command = strtok(NULL, " \n");
            if(strcmp("drew", strtok_command) == 0){
                move_character(drew, player->location);
                guesses++;
                gameWon = clue(drew, player->location, player->inventory, answer_room, answer_item, answer_character);
                continue;
            }
            else if(strcmp("chris", strtok_command) == 0){    
                move_character(chris, player->location);
                guesses++;
                gameWon = clue(chris, player->location, player->inventory, answer_room, answer_item, answer_character);
                continue;
            }
            else if(strcmp("doug", strtok_command) == 0){    
                move_character(doug, player->location);
                guesses++;
                gameWon = clue(doug, player->location, player->inventory, answer_room, answer_item, answer_character);
                continue;
            }
            else if(strcmp("jane", strtok_command) == 0){    
                move_character(jane, player->location);
                guesses++;
                gameWon = clue(jane, player->location, player->inventory, answer_room, answer_item, answer_character);
                continue;
            }
            else if(strcmp("jill", strtok_command) == 0){    
                move_character(jill, player->location);
                guesses++;
                gameWon = clue(jill, player->location, player->inventory, answer_room, answer_item, answer_character);
                continue;
            }
            else{
                printf("invalid command\n");
                continue;
            }
        }else if(strcmp("go", strtok_command) == 0){
            strtok_command = strtok(NULL, " \n");
            if(strcmp("north", strtok_command) == 0){
                go_direction("north", player);
                continue;
            }
            else if(strcmp("south", strtok_command) == 0){
                go_direction("south", player);
                continue;
            }
            else if(strcmp("east", strtok_command) == 0){
                go_direction("east", player);
                continue;
            }
            else if(strcmp("west", strtok_command) == 0){
                go_direction("west", player);
                continue;
            }
            else{
                printf("invalid command\n");
                continue;
            }
    
        }else if(strcmp("take", strtok_command) == 0){
            strtok_command = strtok(NULL, " \n");
            if(strcmp("chain", strtok_command) == 0){
                take_item("chain", player->inventory, player->location->items);
                continue;
            }
            else if(strcmp("dagger", strtok_command) == 0){
                take_item("dagger", player->inventory, player->location->items);
                continue;
            }
            else if(strcmp("pipe", strtok_command) == 0){
                take_item("pipe", player->inventory, player->location->items);
                continue;
            }
            else if(strcmp("pickaxe", strtok_command) == 0){
                take_item("pickaxe", player->inventory, player->location->items);
                continue;
            }
            else if(strcmp("kolibri", strtok_command) == 0){
                take_item("kolibri", player->inventory, player->location->items);
                continue;
            }
            else if(strcmp("cleaver", strtok_command) == 0){
                take_item("cleaver", player->inventory, player->location->items);
                continue;
            }
            else{
                printf("invalid command\n");
                continue;
            }
        }else if(strcmp("drop", strtok_command) == 0){
            strtok_command = strtok(NULL, " \n");
            if(strcmp("chain", strtok_command) == 0){
                drop_item("chain", player->inventory, player->location->items);
                continue;
            }
            else if(strcmp("dagger", strtok_command) == 0){
                drop_item("dagger", player->inventory, player->location->items);
                continue;
            }
            else if(strcmp("pipe", strtok_command) == 0){
                drop_item("pipe", player->inventory, player->location->items);
                continue;
            }
            else if(strcmp("pickaxe", strtok_command) == 0){
                drop_item("pickaxe", player->inventory, player->location->items);
                continue;
            }
            else if(strcmp("kolibri", strtok_command) == 0){
                drop_item("kolibri", player->inventory, player->location->items);
                continue;
            }
            else if(strcmp("cleaver", strtok_command) == 0){
                drop_item("cleaver", player->inventory, player->location->items);
                continue;
            }
            else{
                printf("invalid command\n");
                continue;
            }
        }else{
            printf("invalid command, try again\n");
            continue;
        }
    }
    //when main game loop ends and you lose
    if(gameWon == 0){
        printf("you lose!\n");
    }

    //free all malloc instances
    free(room1);
    free(room2);
    free(room3);
    free(room4);
    free(room5);
    free(room6);
    free(room7);
    free(room8);
    free(room9);
    free(drew);
    free(chris);
    free(doug);
    free(jane);
    free(jill);
    free(item1);
    free(item2);
    free(item3);
    free(item4);
    free(item5);
    free(item6);

}