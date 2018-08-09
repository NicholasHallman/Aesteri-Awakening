#include "Dungeon.h"
#include "eNgiNe.h"

void rotateRoomsRight(Dungeon * d) {
	int i = 1;
	DoorArray * doors = d->getDoors();
	Door * toFind = doors->doors[0]->connect;
	Door * door = doors->doors[i];
	while (toFind != door) {
		i++;
		door = doors->doors[i];
	}
	i++;
	if (i > 4) {
		i = 1;
	}
	doors->doors[0]->connect = doors->doors[i];
	Door * connect = doors->doors[0]->connect;
	if (connect->closed) {
		d->getRooms()[0]->SetTile(10, 1, 38);
		d->getRooms()[0]->SetTile(10, 2, 37);
		d->getRooms()[0]->wholeScrolling();
	}
	else {
		d->getRooms()[0]->SetTile(10, 1, 5);
		d->getRooms()[0]->SetTile(10, 2, 4);
		d->getRooms()[0]->wholeScrolling();
	}
	d->shake = true;
	d->pastTime = clock();
	play_sample(d->rumble, 256, 128, 1000, 0);
	return;
}

void rotateRoomsLeft(Dungeon * d) {
	int i = 1;
	DoorArray * doors = d->getDoors();
	Door * toFind = doors->doors[0]->connect;
	Door * door = doors->doors[i];
	while (toFind != door) {
		i++;
		door = doors->doors[i];
	}
	i--;
	if (i < 1) {
		i = 4;
	}
	doors->doors[0]->connect = doors->doors[i];
	Door * connect = doors->doors[0]->connect;
	if (connect->closed) {
		d->getRooms()[0]->SetTile(10, 1, 38);
		d->getRooms()[0]->SetTile(10, 2, 37);
		d->getRooms()[0]->wholeScrolling();
	}
	else {
		d->getRooms()[0]->SetTile(10, 1, 5);
		d->getRooms()[0]->SetTile(10, 2, 4);
		d->getRooms()[0]->wholeScrolling();
	}
	d->pastTime = clock();
	play_sample(d->rumble, 256, 128, 1000, 0);
	d->shake = true;
	return;
}

void openDoor(Dungeon *d) {
	d->getDoors()->doors[2]->closed = false;
}

Dungeon::Dungeon(TileMap ** roomArray, int nR, const char * n)
{
	rooms = roomArray;
	numRooms = nR;
	name = n;
	tileSize = rooms[0]->tileSize[0];
}

int Dungeon::getRoom()
{
	return currentRoom;
}

int Dungeon::getNumberofRooms() {
	return numRooms;
}

TileMap ** Dungeon::getRooms() {
	return rooms;
}

DoorArray * Dungeon::getDoors() {
	return doors;
}

void Dungeon::Start() {
	player = (Player *)stage->findObjectByName("Player");
	player->setTileMap(rooms[0]);
	Door *door6 = new Door{ NULL, NULL, 5, NULL, false, false, 2 };
	Door *door0 = new Door;
	Door *door1 = new Door{ 10 * tileSize,12 * tileSize,1,door0,false,false,2 };
	*door0 = Door{ 10 * tileSize, 1 * tileSize, 0 ,door1,false,false,0 };
	Door *door2 = new Door{ 10 * tileSize,12 * tileSize,2,door0,false,true,2 };
	Door *door3 = new Door{ 10 * tileSize,12 * tileSize,3,door0,false,false,2 };
	Door *door4 = new Door{ 10 * tileSize,12 * tileSize,4,door0,false,false,2 };
	Door *door5 = new Door{ 10 * tileSize, 2 * tileSize, 1, door6, true, false, 0 };
	Key *key = new Key{ 10 * tileSize,6 * tileSize, 2 };
	Button *b1 = new Button{ 7 * tileSize,6 * tileSize,0,rotateRoomsRight };
	Button *b2 = new Button{ 13 * tileSize,6 * tileSize,0,rotateRoomsLeft };
	Button *b3 = new Button{ 10 * tileSize,6 * tileSize,3,openDoor };
	doors = new DoorArray{ new Door*[7]{ door0,door1,door2,door3,door4,door5,door6 }, 7};
	keys = new KeyArray{ new Key*[1]{key},1 };
	buttons = new ButtonArray{new Button*[3]{ b1,b2,b3 }, 3};
	rooms[0]->hide = false;
	rooms[1]->hide = true;
	rooms[2]->hide = true;
	rooms[3]->hide = true;
	rooms[4]->hide = true;
	rooms[5]->hide = true;
	stage->addLogicChild(rooms[0]);
	stage->addLogicChild(rooms[1]);
	stage->addLogicChild(rooms[2]);
	stage->addLogicChild(rooms[3]);
	stage->addLogicChild(rooms[4]);
	currentRoom = 0;

	rumble = load_sample("Assets/rumble.wav");
}

void Dungeon::Logic() {
	// check Doors
	int distance;
	for (int i = 0; i < doors->numDoors; i++) {
		if (doors->doors[i]->inRoom == currentRoom && doors->doors[i]->x != NULL && doors->doors[i]->y != NULL) {
			distance = sqrt(pow((doors->doors[i]->x + 32) - (player->x + 32), 2) + pow(doors->doors[i]->y - (player->y + 64), 2));
			if (distance < 1 * tileSize && !doors->doors[i]->closed && !doors->doors[i]->needKey) {
				if (doors->doors[i]->connect != NULL && !doors->doors[i]->needKey && !doors->doors[i]->connect->closed && !transition) {
					pastRoom = currentRoom;
					currentRoom = doors->doors[i]->connect->inRoom;
					rooms[currentRoom]->hide = false;
					player->setTileMap(rooms[currentRoom]);
					player->hide = true;
					rooms[pastRoom]->followType = 0;
					rooms[currentRoom]->followType = 0;
					transition = true;
					through = doors->doors[i];
					switch (doors->doors[i]->direction) {
					case 0:
						rooms[currentRoom]->y = rooms[pastRoom]->y + (rooms[currentRoom]->getMapSize()[1] * tileSize);
						rooms[currentRoom]->x = player->x;
						break;
					case 1:
						rooms[currentRoom]->x = rooms[pastRoom]->x + rooms[currentRoom]->getMapSize()[1] * tileSize;
						rooms[currentRoom]->y = player->y;
						break;
					case 2:
						rooms[currentRoom]->y = rooms[pastRoom]->y - rooms[currentRoom]->getMapSize()[1] * tileSize;
						rooms[currentRoom]->x = player->x;
						break;
					case 3:
						rooms[currentRoom]->x = rooms[pastRoom]->x - (rooms[currentRoom]->getMapSize()[1] * tileSize);
						rooms[currentRoom]->y = player->y;
						break;
					}

				}
				else if (doors->doors[i]->connect == NULL) {
					//load in grove
				}
			}
			else if (doors->doors[i]->needKey && player->keys > 0 && distance < 2 * 64 && !transition) {
				Door * door = doors->doors[i];
				player->keys--;
				doors->doors[i]->needKey = false;
				switch (doors->doors[i]->direction) {
				case 0: // top
					rooms[doors->doors[i]->inRoom]->SetTile(door->x / tileSize, door->y / tileSize, 4);
					rooms[doors->doors[i]->inRoom]->SetTile(door->x / tileSize, (door->y / tileSize) - 1,5);
					rooms[door->inRoom]->wholeScrolling();
					break;
				case 1: // right
					rooms[doors->doors[i]->inRoom]->SetTile(door->x / tileSize, door->y / tileSize, 19);
					rooms[doors->doors[i]->inRoom]->SetTile((door->x / tileSize) + 1, door->y / tileSize, 20);
					rooms[door->inRoom]->wholeScrolling();
					break;
				case 2: // down
					rooms[doors->doors[i]->inRoom]->SetTile(door->x / tileSize, door->y / tileSize, 21);
					rooms[doors->doors[i]->inRoom]->SetTile(door->x / tileSize, (door->y / tileSize) + 1, 22);
					rooms[door->inRoom]->wholeScrolling();
					break;
				case 3: // left
					rooms[doors->doors[i]->inRoom]->SetTile(door->x / tileSize, door->y / tileSize, 23);
					rooms[doors->doors[i]->inRoom]->SetTile((door->x / tileSize) - 1, door->y / tileSize, 24);
					rooms[door->inRoom]->wholeScrolling();
					break;
				}
			}
		}
	}
	for (int i = 0; i < keys->numKeys; i++) {
		Key * key = keys->keys[i];
		if (key->x != NULL && key->inRoom == currentRoom) {
			distance = (pow(key->x - player->x, 2) + pow(key->y - player->y, 2));
			if (distance < 1 * 64) {
				player->keys++;
				rooms[key->inRoom]->SetTile(key->x / tileSize, key->y / tileSize, 28);
				rooms[key->inRoom]->wholeScrolling();
				key->x = NULL;
			}
		}
	}	
	for (int i = 0; i < buttons->numButtons; i++) {
		Button * b = buttons->buttons[i];
		distance = (pow((b->x + 32) - (player->x + 32), 2) + pow((b->y + 32) - (player->y + 64), 2));
		if (b->inRoom == currentRoom) {
			if (rooms[b->inRoom]->GetTile(b->x / 64, b->y / 64) == 25 || rooms[b->inRoom]->GetTile(b->x / 64, b->y / 64) == 26) {
				if (distance < (3 * tileSize) && b->released) {
					b->function(this);
					b->released = false;
					rooms[currentRoom]->SetTile(b->x / tileSize, b->y / tileSize, 26);
					rooms[currentRoom]->wholeScrolling();
				}
				else if (distance > (3 * tileSize) && !b->released) {
					b->released = true;
					rooms[currentRoom]->SetTile(b->x / tileSize, b->y / tileSize, 25);
					rooms[currentRoom]->wholeScrolling();
				}
			}
		}
	}

	if (transition) {
		player->stopMovement = true;
		switch (through->direction) {
		case 0: // up
			if (rooms[currentRoom]->y > 600) {
				rooms[currentRoom]->y -= 2;
				rooms[pastRoom]->y -= 2;
			}
			else {
				transition = false;
				stage->setWorld(rooms[currentRoom]);
				rooms[pastRoom]->hide = true;
				rooms[currentRoom]->followType = 3;
				player->x = rooms[currentRoom]->x;
				player->y = rooms[currentRoom]->y;
				player->hide = false;
				player->setTileMap(rooms[currentRoom]);
				player->stopMovement = false;
			}

			break;
		case 1: // right
			if (rooms[currentRoom]->x != 0) {
				rooms[currentRoom]->x--;
				rooms[pastRoom]->x--;
			}
			else transition = false;
			break;
		case 2: // down
			if (rooms[currentRoom]->y < 164) {
				rooms[currentRoom]->y+=2;
				rooms[pastRoom]->y+=2;
			}
			else {
				transition = false;
				transition = false;
				stage->setWorld(rooms[currentRoom]);
				rooms[pastRoom]->hide = true;
				rooms[currentRoom]->followType = 3;
				player->x = rooms[currentRoom]->x;
				player->y = rooms[currentRoom]->y;
				player->hide = false;
				player->setTileMap(rooms[currentRoom]);
				player->stopMovement = false;
			}
			break;
		case 3: // left
			if (rooms[currentRoom]->x != 0) {
				rooms[currentRoom]->x++;
				rooms[pastRoom]->x++;
			}
			else transition = false;
			break;
		}
	}
	if (shake) {
		if (clock() - pastTime > 1000) {
			shake = false;
			rooms[currentRoom]->dx = 0;
			rooms[currentRoom]->dy = 0;
			player->dx = 0;
			player->dy = 0;
		}
		else {
			double xrand = rand() % 5;
			double yrand = rand() % 5;
			rooms[currentRoom]->dx = xrand;
			rooms[currentRoom]->dy = yrand;
			player->dx = xrand;
			player->dy = yrand;
		}
	}
}

void Dungeon::draw(BITMAP * buffer) {
	for(int i = 0; i < numRooms; i++) {
		rooms[i]->draw(buffer);
	}
}


Dungeon::~Dungeon()
{
	for (int i = 0; i < numRooms; i++) {
		rooms[i]->~TileMap();
	}
	for (int i = 0; i < doors->numDoors; i++) {
		delete(doors->doors[i]);
	}
	delete(doors);
}
