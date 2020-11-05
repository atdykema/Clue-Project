This program is a variation of the board game Clue. I firstly initialize all the rooms, characters, and items. Following this, the game board is randomized. Then, the main game loop
runs continuously until the player wins by getting the right guesses or not guessing correctly in 10 guesses.

How this project fulfills the requirements:
1. The gameboard contains 9 rooms, as intialized in the main method
2. the names of all the rooms are randomized in an array, then assigned as to have a different gameboard everytime
3. the gameboard contains 5 characters, as intialized in the main method. The characters are randomized in an array and then randomly assigned a room to start in.
4. the gameboard contains 6 item, as initialized in the main method. The item names are randomized and then assigned to the items already located in the rooms.
5. A random answer is picked in the main method after randomization of all rooms, characters, and items
6. Each room is initialized with an linked list of items, starting with a dummy item in each room
7. The avatar is initialized with an inventory which is a linked list of items, starting with a dummy item in each room
8. the help, list, look, go_direction, take_item, drop_item, inventory, and clue methods exist as they are described in the Project 2 instructions in the main method
9.
    a. move_character is a method that is used to move the accused character to the location of the player
    b. the clue method prints whether the player has guessed the correct room, character, and item or not.
    c. the game is won and ended when all three guesses are correct in one command, the game is lost and ended when the player
        could not guess the proper mixture of room, character, and item.

Video: https://youtu.be/Lw13TS5RCoM
