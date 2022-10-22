/* ---------------------------------------------
Course: UIC CS 211, Fall 2022.
Author: Faaizuddin Farooqui 
------------------------------------------------
*/
#include <ctype.h>    // for tolower()
#include <stdbool.h>  // for booleans
#include <stdlib.h>   // for srand and for malloc()
#include <stdio.h>

// global constants
#define NUMBER_OF_ROOMS 20

// To pass game information of each object through functions
struct GameInfo{
  int stepNumber; // Counts up from 1, incrementing for each move
  int playerRoom; // Room 1..20 the person currently is in
  int wumpusRoom; // Room 1..20 the Wumpus is in
  int pitRoom1;   // Room 1..20 the first pit is in
  int pitRoom2;   // Room 1..20 the second pit is in
  int batsRoom1;  // Room 1..20 the first bats are in
  int batsRoom2;  // Room 1..20 the second bats are in
  int arrowRoom;  // Room 1..20 the person's arrow is in
};
//--------------------------------------------------------------------------------
/* Generates our dynamically allocated rooms and returns a pointer to the first 1D 
   array of our 2D array. */
int **generateRooms(){
  
  int row = NUMBER_OF_ROOMS + 1; // created an extra room to avoid index errors
  int col = 3;                   // the number of adjacent rooms to each room.

  int **rooms = malloc(          // allocated memory for a double-pointer of type pointer to int
      sizeof(int *) *
      row);                      

  for (int i = 0; i < row; i++)  // allocated memory for 3 integers to each pointer to int
    rooms[i] = malloc(
        col *
        sizeof(int)); 

  rooms[0][0] = 0;
  rooms[0][0] = 0;
  rooms[0][0] = 0;

  // Room 1
  rooms[1][0] = 2; rooms[1][1] = 5; rooms[1][2] = 8;
  // Room 2
  rooms[2][0] = 1; rooms[2][1] = 3; rooms[2][2] = 10;
  // Room 3
  rooms[3][0] = 2; rooms[3][1] = 4; rooms[3][2] = 12;
  // Room 4
  rooms[4][0] = 3; rooms[4][1] = 5; rooms[4][2] = 14;
  // Room 5
  rooms[5][0] = 1; rooms[5][1] = 4; rooms[5][2] = 6;
  // Room 6
  rooms[6][0] = 5; rooms[6][1] = 7; rooms[6][2] = 15;
  // Room 7
  rooms[7][0] = 6; rooms[7][1] = 8; rooms[7][2] = 17;
  // Room 8
  rooms[8][0] = 1; rooms[8][1] = 7; rooms[8][2] = 9;
  // Room 9
  rooms[9][0] = 8; rooms[9][1] = 10; rooms[9][2] = 18;
  // Room 10
  rooms[10][0] = 2; rooms[10][1] = 9; rooms[10][2] = 11;
  // Room 11
  rooms[11][0] = 10; rooms[11][1] = 12; rooms[11][2] = 19;
  // Room 12
  rooms[12][0] = 3; rooms[12][1] = 11; rooms[12][2] = 13;
  // Room 13
  rooms[13][0] = 12; rooms[13][1] = 14; rooms[13][2] = 20;
  // Room 14
  rooms[14][0] = 4; rooms[14][1] = 13; rooms[14][2] = 15;
  // Room 15
  rooms[15][0] = 6; rooms[15][1] = 14; rooms[15][2] = 16;
  // Room 16
  rooms[16][0] = 15; rooms[16][1] = 17; rooms[16][2] = 20;
  // Room 17
  rooms[17][0] = 7; rooms[17][1] = 16; rooms[17][2] = 18;
  // Room 18
  rooms[18][0] = 9; rooms[18][1] = 17; rooms[18][2] = 19;
  // Room 19
  rooms[19][0] = 11; rooms[19][1] = 18; rooms[19][2] = 20;
  // Room 20
  rooms[20][0] = 13; rooms[20][1] = 16; rooms[20][2] = 19;

  return rooms;
}
//--------------------------------------------------------------------------------
// Return true if randomValue is already in array
int alreadyFound(int randomValue, int randomNumbers[], int limit){
    int returnValue = false;
    
    // compare random value against all previously found values
    for( int i = 0; i<limit; i++) {
        if( randomValue == randomNumbers[i]) {
            returnValue = true;   // It is already there
            break;
        }
    }
    
    return returnValue;
} 
//--------------------------------------------------------------------------------
// Fill this array with unique random integers 1..20 
void setUniqueValues(int randomNumbers[], int size){
    int randomValue = -1;
    
    for( int i = 0; i<size; i++) {
        do {
            randomValue = (rand() % NUMBER_OF_ROOMS) + 1;   // random number 1..20
        } while (alreadyFound(randomValue, randomNumbers, i));
        randomNumbers[i] = randomValue;
    }
} 
//--------------------------------------------------------------------------------
// Set the Wumpus, player, bats, pits, and the arrow in distinct random rooms
void initializeGameObjects(struct GameInfo *gameInfo){
  int currentPositions[7];

  setUniqueValues(currentPositions, 7);

  gameInfo->playerRoom = currentPositions[0];
  gameInfo->wumpusRoom = currentPositions[1];
  gameInfo->pitRoom1 = currentPositions[2];
  gameInfo->pitRoom2 = currentPositions[3];
  gameInfo->batsRoom1 = currentPositions[4];
  gameInfo->batsRoom2 = currentPositions[5];
  gameInfo->arrowRoom = currentPositions[6];

  gameInfo->stepNumber = 1;
}
//--------------------------------------------------------------------------------
void displayCave(){
  printf("\n"
         "       ______18______             \n"
         "      /      |       \\           \n"
         "     /      _9__      \\          \n"
         "    /      /    \\      \\        \n"
         "   /      /      \\      \\       \n"
         "  17     8        10     19       \n"
         "  | \\   / \\      /  \\   / |    \n"
         "  |  \\ /   \\    /    \\ /  |    \n"
         "  |   7     1---2     11  |       \n"
         "  |   |    /     \\    |   |      \n"
         "  |   6----5     3---12   |       \n"
         "  |   |     \\   /     |   |      \n"
         "  |   \\       4      /    |      \n"
         "  |    \\      |     /     |      \n"
         "  \\     15---14---13     /       \n"
         "   \\   /            \\   /       \n"
         "    \\ /              \\ /        \n"
         "    16---------------20           \n"
         "\n");
}
//--------------------------------------------------------------------------------
void displayInstructions(){
  printf("Hunt the Wumpus:                                             \n"
         "The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
         "room has 3 tunnels leading to other rooms.                   \n"
         "                                                             \n"
         "Hazards:                                                     \n"
         "1. Two rooms have bottomless pits in them.  If you go there you fall "
         "and die.   \n"
         "2. Two other rooms have super-bats.  If you go there, the bats grab "
         "you and     \n"
         "   fly you to some random room, which could be troublesome.  Then "
         "those bats go \n"
         "   to a new room different from where they came from and from the "
         "other bats.   \n"
         "3. The Wumpus is not bothered by the pits or bats, as he has sucker "
         "feet and    \n"
         "   is too heavy for bats to lift.  Usually he is asleep.  Two things "
         "wake       \n"
         "    him up: Anytime you shoot an arrow, or you entering his room.  "
         "The Wumpus   \n"
         "    will move into the lowest-numbered adjacent room anytime you "
         "shoot an arrow.\n"
         "    When you move into the Wumpus' room, then he wakes and moves if "
         "he is in an \n"
         "    odd-numbered room, but stays still otherwise.  After that, if he "
         "is in your \n"
         "    room, he snaps your neck and you die!                            "
         "           \n"
         "                                                                     "
         "           \n"
         "Moves:                                                               "
         "           \n"
         "On each move you can do the following, where input can be upper or "
         "lower-case:  \n"
         "1. Move into an adjacent room.  To move enter 'M' followed by a "
         "space and       \n"
         "   then a room number.                                               "
         "           \n"
         "2. Shoot your guided arrow through a list of up to three adjacent "
         "rooms, which  \n"
         "   you specify.  Your arrow ends up in the final room.               "
         "           \n"
         "   To shoot enter 'S' followed by the number of rooms (1..3), and "
         "then the      \n"
         "   list of the desired number (up to 3) of adjacent room numbers, "
         "separated     \n"
         "   by spaces. If an arrow can't go a direction because there is no "
         "connecting   \n"
         "   tunnel, it ricochets and moves to the lowest-numbered adjacent "
         "room and      \n"
         "   continues doing this until it has traveled the designated number "
         "of rooms.   \n"
         "   If the arrow hits the Wumpus, you win! If the arrow hits you, you "
         "lose. You  \n"
         "   automatically pick up the arrow if you go through a room with the "
         "arrow in   \n"
         "   it.                                                               "
         "           \n"
         "3. Enter 'R' to reset the person and hazard locations, useful for "
         "testing.      \n"
         "4. Enter 'C' to cheat and display current board positions.           "
         "           \n"
         "5. Enter 'D' to display this set of instructions.                    "
         "           \n"
         "6. Enter 'P' to print the maze room layout.                          "
         "           \n"
         "7. Enter 'X' to exit the game.                                       "
         "           \n"
         "                                                                     "
         "           \n"
         "Good luck!                                                           "
         "           \n"
         " \n\n");
}
//--------------------------------------------------------------------------------
void displayCheating(struct GameInfo gameInfo){
  // Message for menu option C (cheating). Note that the printf() statement
  // below always prints 1, 2, 3, 4, 5, 6, 7
  printf("Cheating! Game elements are in the following rooms: \n"
         "Player Wumpus Pit1 Pit2 Bats1 Bats2 Arrow  \n"
         "%4d %5d %6d %5d %5d %5d %5d \n\n",
         gameInfo.playerRoom, gameInfo.wumpusRoom, gameInfo.pitRoom1,
         gameInfo.pitRoom2, gameInfo.batsRoom1, gameInfo.batsRoom2,
         gameInfo.arrowRoom);
}
//--------------------------------------------------------------------------------
// Returns true if nextRoom is adjacent to current room, else returns false.
bool isAdjacent(int desiredRoom, int currentRoom[]){
  for (int i = 0; i < 3; i++) {
    if (currentRoom[i] == desiredRoom)
      return true;
  }
  return false;
}
//--------------------------------------------------------------------------------
/* Checks the nearby adjacent rooms if there are any hazards, and responds accordingly.
  Acquires positions from the struct and compares it with the currrent the player is 
  iroom that is passed. */
void checkForNearbyHazards(struct GameInfo gameInfo, int currentRoom[]){

  // player's adjacent room numbers
  int adjRoom1 = currentRoom[0];
  int adjRoom2 = currentRoom[1];
  int adjRoom3 = currentRoom[2];

  // hazard's room numbers
  int wumpusRoom = gameInfo.wumpusRoom;
  int pitRoom1 = gameInfo.pitRoom1;
  int pitRoom2 = gameInfo.pitRoom2;
  int batsRoom1 = gameInfo.batsRoom1;
  int batsRoom2 = gameInfo.batsRoom2;

  // message displayed for each hazard
  if (wumpusRoom == adjRoom1 || wumpusRoom == adjRoom2 ||
      wumpusRoom == adjRoom3) {
    printf("You smell a stench. ");
  }
  if (pitRoom1 == adjRoom1 || pitRoom1 == adjRoom2 || pitRoom1 == adjRoom3 ||
      pitRoom2 == adjRoom1 || pitRoom2 == adjRoom2 || pitRoom2 == adjRoom3) {
    printf("You feel a draft. ");
  }
  if (batsRoom1 == adjRoom1 || batsRoom1 == adjRoom2 || batsRoom1 == adjRoom3 ||
      batsRoom2 == adjRoom1 || batsRoom2 == adjRoom2 || batsRoom2 == adjRoom3) {
    printf("You hear rustling of bat wings. ");
  }
}
//--------------------------------------------------------------------------------
/* Checks the current room if our player has run into any of our hazards.
   Takes a GameInfo pointer so we can modify our game information. Wumpus 
   has a special case because it moves to a room adjacent to its own. On
   the other hand, bats can move to any other unique room. */
void checkForHazards(struct GameInfo *gameInfo, int currentWumpusRoom[]){
  
  int player = gameInfo->playerRoom;
  int wumpus = gameInfo->wumpusRoom;
  int pit1 = gameInfo->pitRoom1;
  int pit2 = gameInfo->pitRoom2;
  int bat1 = gameInfo->batsRoom1;
  int bat2 = gameInfo->batsRoom2;

  if (player == wumpus) {
    if (wumpus % 2 == 0) {
      // Message when the player dies from Wumpus (Even Room)
      printf(
          "You briefly feel a slimy tentacled arm as your neck is snapped. \n"
          "It is over.\n");
      // Message that prints at the end of the program
      printf("\nExiting Program ...\n");
      exit(0);
    } else {
      // Message when Wumpus escapes (Odd Room)
      gameInfo->wumpusRoom = currentWumpusRoom[0];
      printf("You hear a slithering sound, as the Wumpus slips away. \n"
             "Whew, that was close! \n");
      return;
    }
  }

  if (player == pit1 || player == pit2) {
    // Message when the player dies by falling into a pit
    printf("Aaaaaaaaahhhhhh....   \n");
    printf("    You fall into a pit and die. \n");
    // Message that prints at the end of the program
    printf("\nExiting Program ...\n");
    exit(0);
  }
  
  if (player == bat1 || player == bat2) {  

      int oldPlayerPosition = player;
      int num = 0;
      // Re assign player's room
    
      do{
        num = (rand() % NUMBER_OF_ROOMS) + 1;
      } while(num == bat1 || num == bat2);
      
      gameInfo->playerRoom = num;
      // Message when bats transport player
      printf("Woah... you're flying! \n");
      printf("You've just been transported by bats to room %d.\n", num); 
      
    
      player = gameInfo->playerRoom; // Re assign player variable to new room number
      // Re assign bats' room
      do{
        num = rand() % NUMBER_OF_ROOMS + 1;
      }
      while (num == bat1 || num == bat2 || num == player); //Bats don't move into same, other bats, or new player's room (could cause an infinite cycle)
      if (bat1 == oldPlayerPosition){
        gameInfo->batsRoom1 = num; //Move bat1 if player met bat1
      }
      else
        gameInfo->batsRoom2 = num; //Move bat2 if player met bat2
  }
}
//--------------------------------------------------------------------------------
// Prompt for and reset the positions of the game objects' positions.
void resetPositions(struct GameInfo *gameInfo){
  // Prompt for user when they choose to reset
  printf("Enter the room locations (1..20) for player, wumpus, pit1, pit2, "
         "bats1, bats2, and arrow: \n");
  scanf(" %d %d %d %d %d %d %d", &gameInfo->playerRoom, &gameInfo->wumpusRoom,
        &gameInfo->pitRoom1, &gameInfo->pitRoom2, &gameInfo->batsRoom1,
        &gameInfo->batsRoom2, &gameInfo->arrowRoom);
  printf("\n");
}
//--------------------------------------------------------------------------------
// Initializes our game and runs the game playing loop.
int main(void) {

  // INITIALIZING GAME SETTINGS
  // --------------------------------------------------------------------------------
  
  int **Rooms = generateRooms();    // Creating the array of rooms used throughout the game.
  struct GameInfo gameInfo;        
  srand(1);
  initializeGameObjects(&gameInfo); // Initializing the objects of the game with room values.

  // --------------------------------------------------------------------------------
  // GAME LOOP (Main playing loop) Will keep running till the game exits due to victory or death.
  
  while (true) {

    // Information that displays after every command
    // ------------------------------------------------------------------------------
    printf("You are in room %d. ", gameInfo.playerRoom);
    checkForNearbyHazards(gameInfo, Rooms[gameInfo.playerRoom]);   
    printf("\n\n");
    printf("%d. Enter your move (or 'D' for directions): ", gameInfo.stepNumber);
    // ------------------------------------------------------------------------------

    // Get's the user's command
    char input;                      
    scanf(" %c", &input);
    input = tolower(input);

    // All the different types of commands possible
    // ------------------------------------------------------------------------------
    // DIRECTIONS
    if (input == 'd') {
      displayCave();
      displayInstructions();
    }
    // ------------------------------------------------------------------------------
    // MOVING INTO ROOM
    else if (input == 'm') {

      
      int room;
      scanf(" %d", &room);

      if (isAdjacent(room, Rooms[gameInfo.playerRoom])) {
  
        gameInfo.playerRoom = room;
        checkForHazards(&gameInfo, Rooms[gameInfo.wumpusRoom]);

        // Checks if, when moving into a room, there is a arrow to be picked up.
        if (gameInfo.playerRoom == gameInfo.arrowRoom){
          printf("Congratulations, you found the arrow and can once again shoot.\n");
          gameInfo.arrowRoom = -1;
        }
          
        // Increases Move Number
        gameInfo.stepNumber++;
      
      } 
      else
        printf("Invalid move.  Please retry. \n");
    } 
    // ------------------------------------------------------------------------------
    // RESETTING POSITIONS
    else if (input == 'r') {
      resetPositions(&gameInfo);
    } 
    // ------------------------------------------------------------------------------
    // CHEATING DISPLAY
    else if (input == 'c') {
      displayCheating(gameInfo);
    }
    // ------------------------------------------------------------------------------
    // MAP DISPLAY
    else if (input == 'p') {
      displayCave();
    } 
    // ------------------------------------------------------------------------------
    // EXIT GAME
    else if (input == 'x') {
      // Message that prints at the end of the program
      printf("\nExiting Program ...\n");
      free(Rooms);
      exit(0);
    } 
    // ------------------------------------------------------------------------------
    // GUESS WUMPUS' ROOM
    else if (input == 'g') {
      // Prompt for room number guess and see if user has found the Wumpus
      int guess = 0;
      printf("Enter room (1..20) you think Wumpus is in: ");
      scanf(" %d", &guess);
      // See if userguess was correct, for a win or loss.
      if (gameInfo.wumpusRoom == guess) {
        printf("You won!\n");
        // Message that prints at the end of the program
        printf("\nExiting Program ...\n");
        free(Rooms);
        exit(0);
      } else {
        printf("You lost.\n");
        // Message that prints at the end of the program
        printf("\nExiting Program ...\n");
        free(Rooms);
        exit(0);
      }
    } 
    // ------------------------------------------------------------------------------
    // SHOOTING ARROW
    else if (input == 's') {

      int arrowRoom = gameInfo.arrowRoom;

      // The player doesn't have an arrow
      if (arrowRoom != -1){  
        printf("Sorry, you can't shoot an arrow you don't have.  Go find it.\n");
      } 
      // The player has an arrow
      else {  
        
        // Prompt user to enter input
        printf("Enter the number of rooms (1..3) into which you want to shoot, "
         "followed by the rooms themselves: ");
        int numberOfRoomsChosen = 0;
        scanf(" %d", &numberOfRoomsChosen);

        // User enters more than 3 rooms to shoot arrow through.
        if (numberOfRoomsChosen > 3){
          printf("Sorry, the max number of rooms is 3.  Setting that value to 3.");
          numberOfRoomsChosen = 3;
        }

        // Used to store the rooms that were entered by the user.
        int possibleRooms[numberOfRoomsChosen];
        
        for (int i = 0; i < numberOfRoomsChosen; i++){
          int room = -1;
          scanf("%d", &room);
          possibleRooms[i] = room;
        }
        
        gameInfo.arrowRoom = gameInfo.playerRoom; /* The arrow needs to be set to an actual room
                                                     because it must check its adjacent rooms.  */

        /* Will go through "adjacent rooms" that the user entered and check weather or not they 
           are rooms that are actually adjacent so that the arrow can travel through them. Other
           wise our arrow will rickochet. */
        
        for (int adjacentRoom = 0; adjacentRoom < numberOfRoomsChosen; adjacentRoom++){
          // ------------------------------------------------------------------------
          // CASE 1: The room entered is currently adjacent to our arrow
          if (isAdjacent(possibleRooms[adjacentRoom], Rooms[gameInfo.arrowRoom])){

            gameInfo.arrowRoom = possibleRooms[adjacentRoom];

            // Checks if we shot and killed wumpus
            if (gameInfo.arrowRoom == gameInfo.wumpusRoom){
            printf("Wumpus has just been pierced by your deadly arrow! \n"
               "Congratulations on your victory, you awesome hunter you.\n");
            
            // Message that prints at the end of the program
            printf("\nExiting Program ...\n");
            free(Rooms);
            exit(0);
            }

            // Checks if we shot and killed ourself
            if (gameInfo.arrowRoom == gameInfo.playerRoom){
              printf("You just shot yourself.  \n"
                   "Maybe Darwin was right.  You're dead.\n");
              
              // Message that prints at the end of the program
              printf("\nExiting Program ...\n");
              free(Rooms);
              exit(0);
            }
          }
          // ------------------------------------------------------------------------
          /* CASE 2: The room entered isn't adjacent to the arrow. This causes the arrow
             to rickochet */
          else{ 
            
            // The arrow will rickochet to the lowest-numbered adjacnet room
            printf("Room %d is not adjacent.  Arrow ricochets...\n", possibleRooms[adjacentRoom]);
            gameInfo.arrowRoom = Rooms[gameInfo.arrowRoom][0];

            // Checks if arrow accidentaly shoots our player
            if (gameInfo.arrowRoom == gameInfo.playerRoom){
              printf("You just shot yourself, and are dying.\n"
                "It didn't take long, you're dead.\n");
              
              // Message that prints at the end of the program
              printf("\nExiting Program ...\n");
              free(Rooms);
              exit(0);
            }

            // Checks if arrow accidentaly shoots wumpus
            if (gameInfo.arrowRoom == gameInfo.wumpusRoom){
              printf("Your arrow ricochet killed the Wumpus, you lucky dog!\n"
                "Accidental victory, but still you win!\n");
              
              // Message that prints at the end of the program
              printf("\nExiting Program ...\n");
              free(Rooms);
              exit(0);
            }
          }
        }

        /* If nothing happens as a result of shooting, Wumpus will always move to its 
        lowest-numbered ajcaent room. */
        gameInfo.wumpusRoom = Rooms[gameInfo.wumpusRoom][0];
        
      }
      // Increases Move Number
        gameInfo.stepNumber++;
    }
  }

  return 0;
}
