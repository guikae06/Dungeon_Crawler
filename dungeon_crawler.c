#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> // Include this header for strcpy


#define MaxDeuren 4 // max aantal deuren in een kamer.
#define MAX_QUEUE   1000
#define MIN_DISTANCE_FOR_END 8 // minimale afstand voor de eind kamer.

typedef struct Item{ // structuur voor alle items in de Dungeon spel.
    char naam[20];
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

typedef struct Room{
	int room_id;
	int x, y; // x en y coördinaten van de kamer.
	int visited; // of de kamer al bezocht is.
	int distance; // afstand van de kamer tot de start kamer.
	int doorCount; // aantal deuren in de kamer.
    Monster *monster;
	Item *Item;
	struct Room *doors[MaxDeuren]; //deuren naar andere kamers.
    int CheckPoint;
} Room;

typedef struct Speeler{ // structuur voor de speler.
	Room *currentRoom; // de kamer waar de speler zich in bevindt.
	int hp;
	int damage;
	int stamina;
} Player;

int GRID_HEIGHT = 5;
int GRID_WIDTH = 5;

Room* grid[100][100];
int roomIdTeller = 0; // teller voor de kamer id's.
Room* startRoom = NULL;
Room* endRoom = NULL;

int neighbors[4][2] = {
    {0, 1},   // down
    {1, 0},   // right
    {0, -1},  // up
    {-1, 0}   // left
};

// Functieprototypes
void choosedificulty(char *difficulty, int *h, int *w);
Room *maakRooms(int x_as,int y_as); //de functie die de kamers maakt.
void Roomconnection(Room *r_nu, Room *r_volgende); //de functie die de kamers met elkaar verbind.
void generateConnectedDungeon();
void findLongestPathFromStart();
void combat(Player* player, Monster* monster);
void printRoomInfo(Room* room); //de functie die de informatie van de kamer print.
void printDungeon(); //de functie die de Dungeon print.
void saveGame(Player* player);
void loadGame(Player* player);

int main(){ //de main.

    srand(time(NULL));

    char difficulty[15];
    choosedificulty(difficulty, &GRID_HEIGHT, &GRID_WIDTH);

    generateConnectedDungeon();
    findLongestPathFromStart();

    Player player;
    player.currentRoom = startRoom;
    player.hp = 100;
    player.damage = 10;
    player.stamina = 100;

    const char* monsterNames[] = {"Goblin", "Orc", "Skeleton"};
    const int monsterHPs[] = {20, 40, 30};
    const int monsterDamages[] = {5, 10, 7};
    const int monsterStamina[] = {20, 30, 25};

    const char* itemNames[] = {"Healing Potion", "Stamina Drink", "Sword"};
    Item* items[] = {
        &(Item){"Healing Potion", 20, 0, 0},
        &(Item){"Stamina Drink", 0, 20, 0},
        &(Item){"Sword", 0, 0, 5},
    };

    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            Room* var_grid = grid[y][x];
            if (var_grid && var_grid != startRoom && var_grid != endRoom) {
                int spawnMonster = rand() % 4; // 25%
                int spawnItem = rand() % 5;    // 20%

                if (spawnMonster == 0) {
                    int m = rand() % 3;
                    Monster* monster = malloc(sizeof(Monster));
                    strcpy(monster -> naam, monsterNames[m]);
                    monster -> hp = monsterHPs[m];
                    monster -> damage = monsterDamages[m];
                    monster -> stamina = monsterStamina[m];
                    var_grid -> monster = monster;
                }
                if (spawnItem == 0) {
                    int i = rand() % 3;
                    var_grid -> Item = items[i];
                }
                if (rand() % 10 == 0) { // 10% kans
                    var_grid->CheckPoint = 1;
                }
            }
        }
    }

    printf("Welcome to the Dungeon Crawler!\n");
    printf("S = Start room\nX = End room\nO = Other room\n\n\n");
    char InputSave[5];
    printf("Do you want to load the previous game? (y/n): ");
    scanf("%s", InputSave);
    if (InputSave[0] == 'y' || InputSave[0] == 'Y') {
        loadGame(&player);
    }
    printDungeon();// Uncomment to print the dungeon layout

    char input[10];
    while (1) {
        printRoomInfo(player.currentRoom);
        if (player.currentRoom -> CheckPoint) {
            printf("You found a checkpoint! Do you want to save your game? (y/n): ");
            scanf("%s", input);
            if (input[0] == 'y' || input[0] == 'Y') {
                saveGame(&player);
            }
        }
        
        if (player.currentRoom == endRoom) {
            printf("You reached the final room! You win!\n");
            break;
        }

        if (player.currentRoom -> monster) {
            printf("A monster blocks your path!\n");
            combat(&player, player.currentRoom -> monster);
            if (player.hp <= 0) {
                printf("Game Over.\n");
                break;
            }
            free(player.currentRoom -> monster);
            player.currentRoom -> monster = NULL;
        }

        if (player.currentRoom -> Item) {
            printf("You found a %s! Use it? (y/n): ", player.currentRoom -> Item -> naam);
            //fgets(input, sizeof(input), stdin);
            scanf("%s", input);
            if (input[0] == 'y' || input[0] == 'Y') {
                player.hp += player.currentRoom -> Item -> hpRestore;
                player.stamina += player.currentRoom -> Item -> staminaRestore;
                player.damage += player.currentRoom -> Item -> damageBoost;
                printf("You used the %s.\n", player.currentRoom -> Item -> naam);
                player.currentRoom -> Item = NULL;
            }
        }

        printf("Enter room id to move to (doors only), or -1, q or quit to exit: ");
        scanf("%s", input);
        //fgets(input, sizeof(input), stdin);
        if (input[0] == 'q' || input[0] == 'Q'|| strcmp(input, "-1") == 0 || strcmp(input, "quit") == 0) {
            printf("Goodbye!\n");
            break;
        }

        int nextId = atoi(input);
        Room* nextRoom = NULL;
        for (int i = 0; i < player.currentRoom->doorCount; i++) {
            if (player.currentRoom -> doors[i] -> room_id == nextId) {
                nextRoom = player.currentRoom -> doors[i];
                break;
            }
        }

        if (nextRoom) {
            player.currentRoom = nextRoom;
        }
        else {
            printf("Invalid room.\n");
        }
    }

    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            Room* var_grid = grid[y][x];
            if (var_grid) {
                if (var_grid -> monster) free(var_grid -> monster);
                free(var_grid);
            }
        }
    }

    return 0;
}

void choosedificulty(char *difficulty, int *h, int *w) {
    printf("Choose difficulty:\n");
    printf("1. Easy\n2. Medium\n3. Hard\n4. Hardcore\n ");
    scanf("%s", difficulty);
    getchar(); // consume newline
    if (strcmp(difficulty, "1") == 0|| strcmp(difficulty, "Easy") == 0|| strcmp(difficulty, "easy") == 0) {
        printf("You chose Easy difficulty.\n");
        *h = 5;
		*w = 5;
    } else if (strcmp(difficulty, "2") == 0|| strcmp(difficulty, "Medium") == 0|| strcmp(difficulty, "medium") == 0) {
        printf("You chose Medium difficulty.\n");
        *h = 10;
		*w = 10;
    } else if (strcmp(difficulty, "3") == 0|| strcmp(difficulty, "hard") == 0|| strcmp(difficulty, "Hard") == 0) {
        printf("You chose Hard difficulty.\n");
        *h = 15;
		*w = 15;
    } else if (strcmp(difficulty, "4") == 0|| strcmp(difficulty, "Hardcore") == 0|| strcmp(difficulty, "hardcore") == 0) {
        printf("You chose Hardcore difficulty.\n");
        *h = 30;
		*w = 30;
    } else {
        printf("Invalid choice. Defaulting to Easy.\n");
        
    }
}

Room *maakRooms(int x_as,int y_as){

	Room *room = malloc(sizeof(Room)); // maak een nieuwe kamer aan.
	room -> room_id = roomIdTeller++; // geef de kamer een id.
	room -> x = x_as; // geef de kamer een x coördinaat.
	room -> y = y_as; // geef de kamer een y coördinaat.
	room -> visited = 0; // de kamer is nog niet bezocht.
	room -> distance = -1; // de afstand is nog niet bekend.
	room -> doorCount = 0; // er zijn nog geen deuren in de kamer.
    room -> CheckPoint = 0; // de kamer is geen checkpoint.

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
		r_nu -> doors[r_nu -> doorCount++] = r_volgende; 
		r_volgende -> doors[r_volgende -> doorCount++] = r_nu; 
		return;
	}
}

void generateConnectedDungeon() {
    for (int y = 0; y < GRID_HEIGHT; y++)
        for (int x = 0; x < GRID_WIDTH; x++)
            grid[y][x] = NULL;

    startRoom = maakRooms(0, 0);
    grid[0][0] = startRoom;

    Room* stack[GRID_WIDTH*GRID_HEIGHT];
    int stackSize = 0;
    stack[stackSize++] = startRoom;

    while (stackSize > 0) {
        Room* current = stack[--stackSize];

        int potentialNeighbors[4][2];
        int pnCount = 0;
        for (int i = 0; i < 4; i++) {
            int nx = current -> x + neighbors[i][0];
            int ny = current -> y + neighbors[i][1];
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
            Room* newRoom = maakRooms(nx, ny);
            grid[ny][nx] = newRoom;
            Connecteren_Van_Rooms(current, newRoom);
            stack[stackSize++] = newRoom;
        }
    }
}

void printRoomInfo(Room* room) {
    printf("You are in room %d at (%d,%d).\n", room->room_id, room->x, room->y);
    if (room->monster){
        printf("There is a %s in the room!\n", room->monster->naam);
    }
    if (room->Item){
        printf("You see a %s.\n", room->Item->naam);
    }
    if (room->CheckPoint) {
        printf("This room is a checkpoint!\n");
    }
    
    printf("Doors lead to rooms: ");
    for (int i = 0; i < room->doorCount; i++)
        printf("%d ", room->doors[i]->room_id);
    printf("\n");
}

void findLongestPathFromStart() {
    Room* queue[MAX_QUEUE];
    int front = 0, rear = 0;

    for (int y = 0; y < GRID_HEIGHT; y++)
        for (int x = 0; x < GRID_WIDTH; x++)
            if (grid[y][x]) {
                grid[y][x]->visited = 0;
                grid[y][x]->distance = -1;
            }

    startRoom -> visited = 1;
    startRoom -> distance = 0;
    queue[rear++] = startRoom;
    endRoom = startRoom;

    while (front < rear) {
        Room* current = queue[front++];
        for (int i = 0; i < current->doorCount; i++) {
            Room* neighbor = current->doors[i];
            if (!neighbor -> visited) {
                neighbor -> visited = 1;
                neighbor -> distance = current->distance + 1;
                queue[rear++] = neighbor;
                if (neighbor -> distance > endRoom -> distance && neighbor -> distance >= MIN_DISTANCE_FOR_END)
                    endRoom = neighbor;
            }
        }
    }
}

void combat(Player* player, Monster* monster) {
    while (player -> hp > 0 && monster -> hp > 0) {
        int attackOrder = rand() % 2;
        if (attackOrder == 0) {
            monster -> hp -= player -> damage;
            player -> stamina -= 3;
            printf("You attack the %s! (%d dmg) => %d HP left.\n", monster -> naam, player -> damage, monster -> hp);
        } else {
            player -> hp -= monster -> damage;
            monster -> stamina -= 3;
            printf("The %s attacks you! (%d dmg) => %d HP left.\n", monster -> naam, monster -> damage, player -> hp);
        }

        if (player -> stamina <= 0) player -> stamina = 0;
        if (monster -> stamina <= 0) monster -> stamina = 0;
    }
}

void printDungeon() {
    for (int y = 0; y < GRID_HEIGHT; y++) {
        // Print kamers en horizontale deuren
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (grid[y][x]) {
                if (grid[y][x] == startRoom)
                    printf("S");
                else if (grid[y][x] == endRoom)
                    printf("X");
                else
                    printf("O");

                // Print horizontale verbinding (deur) als deze bestaat met kamer rechts
                if (x < GRID_WIDTH - 1 && grid[y][x + 1]) {
                    int connected = 0;
                    for (int i = 0; i < grid[y][x]->doorCount; i++) {
                        if (grid[y][x] -> doors[i] == grid[y][x + 1]) connected = 1;
                    }
                    printf(connected ? " - " : "   ");
                } else {
                    printf("   ");
                }
            } else {
                // Geen kamer, print lege ruimte
                printf("    ");
            }
        }
        printf("\n");

        // Print verticale deuren onder kamers
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (grid[y][x]) {
                if (y < GRID_HEIGHT - 1 && grid[y + 1][x]) {
                    int connected = 0;
                    for (int i = 0; i < grid[y][x] -> doorCount; i++) {
                        if (grid[y][x] -> doors[i] == grid[y + 1][x]) connected = 1;
                    }
                    printf(connected ? "|   " : "    ");
                } else {
                    printf("    ");
                }
            } else {
                printf("    ");
            }
        }
        printf("\n");
    }
}

void saveGame(Player* player) {
    FILE* file = fopen("savegame.txt", "w");
    if (!file) {
        printf("Error saving game.\n");
        return;
    }
    fprintf(file, "%d %d %d %d\n", player->hp, player->damage, player->stamina, player->currentRoom->room_id);
    fclose(file);
    printf("Game saved!\n");
}

void loadGame(Player* player) {
    FILE* file = fopen("savegame.txt", "r");
    if (!file) {
        printf("No save file found.\n");
        return;
    }
    int room_id;
    fscanf(file, "%d %d %d %d", &player->hp, &player->damage, &player->stamina, &room_id);
    fclose(file);

    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (grid[y][x] && grid[y][x]->room_id == room_id) {
                player->currentRoom = grid[y][x];
                printf("Game loaded! You're back in room %d.\n", room_id);
                return;
            }
        }
    }
    printf("Room ID not found. Load failed.\n");
}



