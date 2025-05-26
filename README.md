# Dungeon Crawler - C Project

## 🕹️ Overzicht
Dit project is een tekstgebaseerde **Dungeon Crawler game** geschreven in **C**, als onderdeel van een programmeeropdracht. De speler navigeert door een willekeurig gegenereerde dungeon, vecht tegen vijanden, verzamelt items en kan het spel opslaan bij checkpoints.

## 🚀 Functionaliteiten
- 🔁 Willekeurig gegenereerde dungeon (grafenstructuur)
- ⚔️ Gevechten via bitwise-logica
- 🧭 Beweging tussen kamers (N, O, Z, W)
- 🧪 Items met effecten (bijv. health, attack boost)
- 🧩 Moeilijkheidsgraden: gemakkelijk, normaal, moeilijk
- 💾 Opslaan/laden van game state (alleen bij checkpoints)
- 🔄 Dungeon reset mogelijk met behoud van spelerstatus

## 💡 Structuur
- `main.c` – startpunt van het spel
- `dungeon.c/h` – logica voor dungeon generatie en kamers
- `combat.c/h` – gevechtssysteem en vijandlogica
- `player.c/h` – spelerstatus, inventory en inputverwerking
- `save.c/h` – opslag en laden van game state naar bestand
- `utils.c/h` – hulpfuncties voor logging, UI en randomness

## 📂 Opslagstructuur
Game wordt opgeslagen in `savegame.txt` (of JSON indien ingeschakeld).

- Bestandsvoorbeeld:
    - HP=80
    - Level=2
    - RoomID=5
    -  Inventory=Potion,Key

## Voorbeeld van het spel

- You are in room 4 at (1,1).
- Doors lead to rooms: 2 5 6
- Enter room id to move to (doors only), or -1, q or quit to exit: 6
- You are in room 6 at (2,1).
- Doors lead to rooms: 4 7 8
- Enter room id to move to (doors only), or -1, q or quit to exit: 8
- You are in room 8 at (2,2).
- Doors lead to rooms: 6 9 10
- Enter room id to move to (doors only), or -1, q or quit to exit: 9
- A monster blocks your path!
- The Goblin attacks you! (5 dmg) => 75 HP left.
- The Goblin attacks you! (5 dmg) => 70 HP left.
- The Goblin attacks you! (5 dmg) => 65 HP left.
- The Goblin attacks you! (5 dmg) => 60 HP left.
- The Goblin attacks you! (5 dmg) => 55 HP left.
- The Goblin attacks you! (5 dmg) => 50 HP left.
- You attack the Goblin! (10 dmg) => 10 HP left.
- The Goblin attacks you! (5 dmg) => 45 HP left.
- You attack the Goblin! (10 dmg) => 0 HP left.

## ✅ Build-instructies
### ⚙️ Vereisten
- GCC Compiler (Linux/Windows)
- Make (optioneel)

### 🔧 Compileren
#### Linux:
```bash
gcc -o dungeon main.c dungeon.c combat.c player.c save.c utils.c
./dungeon
