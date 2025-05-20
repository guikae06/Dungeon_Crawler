#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> // Include this header for strcpy

typedef struct Room{
    	int room_id;
    	
} Room;

typedef struct Items{ // structuur voor alle items in de Dungeon spel.
    	char naam[20];
    	int HealtPotion;
	int StaminaPotion;
	
} Items;

typedef struct Monsters{
    	char naam[15];
	int healt;
	int damage;
	int stamina;
} Monster;

typedef struct Speeler{ // structuur voor de speler 
	int healt;
	int damage;
	int stamina;
} Player;

int main(){ //de main.

}



