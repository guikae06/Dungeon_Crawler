#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> // Include this header for strcpy

#define MaxDeuren 4 // max aantal deuren in een kamer.

typedef struct Room{
	int room_id;
	int x, y; // x en y coördinaten van de kamer.
	int visited; // of de kamer al bezocht is.
	int distance; // afstand van de kamer tot de start kamer.
	int doorCount; // aantal deuren in de kamer.
    Monster *monster;
	Items *Item;
	struct Room *doors[MaxDeuren]; //deuren naar andere kamers.
} Room;

typedef struct Items{ // structuur voor alle items in de Dungeon spel.
    char naam[20];
    int HealtPotion;
	int StaminaPotion;
} Items;

typedef struct Monster{ //sturctuur voor de monster.
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
int roomIdTeller = 0; // teller voor de kamer id's.

int main(){ //de main.

}

Room *maakRooms(int x_as,int y_as){

	Room *room = (Room*)malloc(sizeof(Room)); // maak een nieuwe kamer aan.
	room -> room_id = roomIdTeller++; // geef de kamer een id.
	room -> x = x_as; // geef de kamer een x coördinaat.
	room -> y = y_as; // geef de kamer een y coördinaat.
	room -> visited = 0; // de kamer is nog niet bezocht.
	room -> distance = -1; // de afstand is nog niet bekend.
	room -> doorCount = 0; // er zijn nog geen deuren in de kamer.

	for (int i = 0; i < 4; i++){
		room -> doors[i] = NULL; // maak de deuren leeg.
	}
	room -> monster = NULL; // er is nog geen monster in de kamer.
	room -> Item = NULL; // er is nog geen item in de kamer.

	return room; // geef de kamer terug.
}

void Connecteren_Van_Rooms(Room *r_nu, Room *r_volgende){ //de functie die de kamers met elkaar verbind.
	// maak een verbinding tussen de kamers.
	for(int i = 0; i < r_nu->doorCount; i++){
		if(r_nu -> doors[i] == r_volgende){
			return;
		}
		if(r_nu -> doorCount < MaxDeuren && r_volgende -> doorCount<MaxDeuren){
			r_nu->doors[r_nu->doorCount++] = r_volgende; 
			r_volgende->doors[r_volgende->doorCount++] = r_nu; 
			return;
		}
	}
}






