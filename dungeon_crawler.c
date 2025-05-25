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
	Item *Item;
	struct Room *doors[MaxDeuren]; //deuren naar andere kamers.
} Room;

typedef struct Item{ // structuur voor alle items in de Dungeon spel.
    char name[20];
    int hpRestore;
    int staminaRestore;
    int damageBoost;
} Item;

typedef struct Monster{ //sturctuur voor de monster.
    char naam[15];
	int hp;
	int damage;
	int stamina;
} Monster;

typedef struct Speeler{ // structuur voor de speler.
	Room *currentRoom; // de kamer waar de speler zich in bevindt.
	int hp;
	int damage;
	int stamina;
} Player;

int roomIdTeller = 0; // teller voor de kamer id's.



// Functieprototypes
Room *maakRooms(int x_as,int y_as); //de functie die de kamers maakt.
void Roomconnection(Room *r_nu, Room *r_volgende); //de functie die de kamers met elkaar verbind.
void MaakDungeon(Room** rooms, int numRooms); //de functie die de dungeon maakt.
void generateConnectedDungeon();


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
	}
	if(r_nu -> doorCount < MaxDeuren && r_volgende -> doorCount<MaxDeuren){
		r_nu->doors[r_nu->doorCount++] = r_volgende; 
		r_volgende->doors[r_volgende->doorCount++] = r_nu; 
		return;
	}
}

void generateConnectedDungeon() {
    for (int y = 0; y < GRID_HEIGHT; y++)
        for (int x = 0; x < GRID_WIDTH; x++)
            grid[y][x] = NULL;

    startRoom = createRoom(0, 0);
    grid[0][0] = startRoom;

    Room* stack[GRID_WIDTH*GRID_HEIGHT];
    int stackSize = 0;
    stack[stackSize++] = startRoom;

    while (stackSize > 0) {
        Room* current = stack[--stackSize];

        int potentialNeighbors[4][2];
        int pnCount = 0;
        for (int i = 0; i < 4; i++) {
            int nx = current->x + neighbors[i][0];
            int ny = current->y + neighbors[i][1];
            if (nx >= 0 && nx < GRID_WIDTH && ny >= 0 && ny < GRID_HEIGHT) {
                if (grid[ny][nx] == NULL) {
                    potentialNeighbors[pnCount][0] = nx;
                    potentialNeighbors[pnCount][1] = ny;
                    pnCount++;
                }
            }
        }

        for (int i = pnCount - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            int tx = potentialNeighbors[i][0];
            int ty = potentialNeighbors[i][1];
            potentialNeighbors[i][0] = potentialNeighbors[j][0];
            potentialNeighbors[i][1] = potentialNeighbors[j][1];
            potentialNeighbors[j][0] = tx;
            potentialNeighbors[j][1] = ty;
        }

        for (int i = 0; i < pnCount; i++) {
            int nx = potentialNeighbors[i][0];
            int ny = potentialNeighbors[i][1];
            Room* newRoom = createRoom(nx, ny);
            grid[ny][nx] = newRoom;
            connectRooms(current, newRoom);
            stack[stackSize++] = newRoom;
        }
    }
}







void print_Dungeon(){
	
}





