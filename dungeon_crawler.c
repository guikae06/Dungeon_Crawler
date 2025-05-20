#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> // Include this header for strcpy

#define MaxDeuren 4 // max aantal deuren in een kamer.

typedef struct Room{
	int room_id;
    Monster *monster;
	Items *Item;
	struct Room *doors[MaxDeuren]; //deuren naar andere kamers.
} Room;

typedef struct Items{ // structuur voor alle items in de Dungeon spel.
    char naam[20];
    int HealtPotion;
	int StaminaPotion;
} Items;

typedef struct Monsters{ //sturctuur voor de monster.
    char naam[15];
	int healt;
	int damage;
	int stamina;
} Monster;

typedef struct Speeler{ // structuur voor de speler.
	int healt;
	int damage;
	int stamina;
} Player;

Room *maakRooms(int room_id); //de functie die de kamers maakt.
void Roomconnection(Room *r_nu, Room *r_volgende); //de functie die de kamers met elkaar verbind.
void MaakDungeon(Room** rooms, int numRooms); //de functie die de dungeon maakt.

int main(){ //de main.

}

Room *maakRooms(int room_id){
	Room *room = (Room*)malloc(sizeof(Room)); // maak een nieuwe kamer aan.
	room -> room_id = room_id; // geef de kamer een id.
	room -> monster = NULL; // er is nog geen monster in de kamer.
	room -> Item = NULL; // er is nog geen item in de kamer.
	for (int i = 0; i < 4; i++){
		room -> doors[i] = NULL; // maak de deuren leeg.
	}
	return room; // geef de kamer terug.
}

void Roomconnection(Room *r_nu, Room *r_volgende){ //de functie die de kamers met elkaar verbind.
	// maak een verbinding tussen de kamers.
	for(int i = 0; i < MaxDeuren; i++){
		if(r_nu -> doors[i] == NULL){
			r_nu -> doors[i] = r_volgende;
			break;
		}
	}
}

void MaakDungeon(Room** rooms, int numRooms) {
	srand(time(NULL)); // Initialiseer de random number generator
	int numRooms = rand() % 25; // aantal kamers in de dungeon.
	if (numRooms < 8) {
		numRooms = 8; // Zorg ervoor dat er altijd minimaal 2 kamers zijn.
	}
	
	for (int i = 0; i < numRooms; i++) {
		rooms[i] = createRoom(i);
	}
	for (int i = 0; i < numRooms - 1; i++) {
		connectRooms(rooms[i], rooms[i + 1]);
	}
}






