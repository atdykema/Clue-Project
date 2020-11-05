#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//item header
struct Item{
    char* name;
    struct Item *next;
};
//item initializer
struct Item *item(char* name, struct Item *next);
//take_item header
void take_item(char* item, struct Item *inventory, struct Item *items);
//drop_item header
void drop_item(char* item, struct Item *inventory, struct Item *items);
