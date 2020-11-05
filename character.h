#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//character header
struct Character{
    char* name;
    struct Room *location;
    struct Character *next;
};
//character initializer
struct Character *character(char* name, struct Room *location, struct Character *next);
//move_character header
void move_character(struct Character *character, struct Room *location);


