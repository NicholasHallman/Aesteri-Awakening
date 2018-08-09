#pragma once
#include "TileMap.h"
#include "Player.h"

class Dungeon;

struct Door {
	int x;
	int y;
	int inRoom;
	Door * connect;
	bool needKey;
	bool closed;
	int direction; //0 top, 1 right, 2 bottom, 3 left
};

struct Key {
	int x;
	int y;
	int inRoom;
};

struct Button {
	int x;
	int y;
	int inRoom;
	void(*function)(Dungeon*);
	bool released = true;
};

struct Monsters {
	int inRoom;
	int ** monsterTypes;
	int ** posX;
	int ** posY;
	int numMonsters;
};

struct DoorArray {
	Door ** doors;
	int numDoors;
};

struct KeyArray {
	Key ** keys;
	int numKeys;
};

struct ButtonArray {
	Button ** buttons;
	int numButtons;
};

class Dungeon :
	public Display
{
public:
	Dungeon(TileMap ** roomArray, int numRooms, const char * name);
	int getRoom();
	void Start();
	void Logic();
	void draw(BITMAP *);
	int getNumberofRooms();
	TileMap ** getRooms();
	DoorArray * getDoors();
	clock_t pastTime;
	bool shake = false;
	SAMPLE * rumble;
	bool transition;
	~Dungeon();
protected:
	
	int tileSize = 0;
	Player * player;
	int numRooms = 0;
	TileMap ** rooms;
	int currentRoom = 0;
	int pastRoom = 0;
	Door * through;
	DoorArray * doors;
	KeyArray * keys;
	ButtonArray * buttons;
	
};

