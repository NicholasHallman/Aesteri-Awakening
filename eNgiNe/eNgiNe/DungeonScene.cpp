#include "DungeonScene.h"
#include "eNgiNe.h"
#include "Dungeon.h"

DungeonScene::DungeonScene()
{
}

void DungeonScene::Load(int posx, int posy)
{
	caveAmb = load_sample("Assets/caveloop.wav");
	play_sample(caveAmb, 256, 128, 1000, 1);
	player = new Player(new SpriteSheet("Assets/swordman.tga", 64, 64), "Player");
	player->addAnimation("forward", new int[5]{ 0,1,0,2,-1 }, NULL);
	player->addAnimation("right", new int[5]{ 4,5,4,6,-1 }, NULL);
	player->addAnimation("left", new int[5]{ 8,9,8,10,-1 }, NULL);
	player->addAnimation("back", new int[5]{ 12,13,12,14,-1 }, NULL);
	player->addAnimation("stabforward", new int[2]{ 3,-1 }, NULL);
	player->addAnimation("stabright", new int[2]{ 7,-1 }, NULL);
	player->addAnimation("stableft", new int[2]{ 11,-1 }, NULL);
	player->addAnimation("stabback", new int[2]{ 15,-1 }, NULL);
	player->addAnimation("spin", new int[6]{ 0, 4, 12, 8, 0, -1 }, NULL);
	player->x = posx * 64;
	player->y = posy * 64;
	player->introAnim = true;
	player->setFPS(10);

	TileMap ** rooms = new TileMap*[5];

	rooms[0] = new TileMap("Assets/DungeonMaps/Room0.txt", 21, 13, "World0", 3);
	rooms[0]->x = player->x;
	rooms[0]->y = player->y;
	rooms[0]->setSolidTiles(new int[21]{ 1,2,5,6,7,8,9,10,11,12,13,14,15,26,28,29,30,31,32,33,34 }, 21);
	rooms[0]->SetTileSprites(new SpriteSheet("Assets/dungeonTiles.tga", 64, 64));
	rooms[0]->wholeScrolling();

	rooms[1] = new TileMap("Assets/DungeonMaps/Room1.txt", 21, 13, "World1", 3);
	rooms[1]->x = player->x;
	rooms[1]->y = player->y;
	rooms[1]->setSolidTiles(new int[21]{ 1,2,5,6,7,8,9,10,11,12,13,14,15,26,28,29,30,31,32,33,34 }, 21);
	rooms[1]->SetTileSprites(new SpriteSheet("Assets/dungeonTiles.tga", 64, 64));
	rooms[1]->wholeScrolling();

	rooms[2] = new TileMap("Assets/DungeonMaps/Room2.txt", 21, 13, "World2", 3);
	rooms[2]->x = player->x;
	rooms[2]->y = player->y;
	rooms[2]->setSolidTiles(new int[21]{ 1,2,5,6,7,8,9,10,11,12,13,14,15,26,28,29,30,31,32,33,34 }, 21);
	rooms[2]->SetTileSprites(new SpriteSheet("Assets/dungeonTiles.tga", 64, 64));
	rooms[2]->wholeScrolling();

	rooms[3] = new TileMap("Assets/DungeonMaps/Room3.txt", 21, 13, "World3", 3);
	rooms[3]->x = player->x;
	rooms[3]->y = player->y;
	rooms[3]->setSolidTiles(new int[22]{ 1,2,5,6,7,8,9,10,11,12,13,14,15,26,28,29,30,31,32,33,34 }, 21);
	rooms[3]->SetTileSprites(new SpriteSheet("Assets/dungeonTiles.tga", 64, 64));
	rooms[3]->wholeScrolling();

	rooms[4] = new TileMap("Assets/DungeonMaps/Room4.txt", 21, 13, "World4", 3);
	rooms[4]->x = player->x;
	rooms[4]->y = player->y;
	rooms[4]->setSolidTiles(new int[22]{ 1,2,5,6,7,8,9,10,11,12,13,14,15,26,28,29,30,31,32,33,34 }, 21);
	rooms[4]->SetTileSprites(new SpriteSheet("Assets/dungeonTiles.tga", 64, 64));
	rooms[4]->wholeScrolling();

	rooms[5] = new TileMap("Assets/DungeonMaps/Grove.csv", 29, 29, "World5", 3);
	rooms[5]->x = player->x;
	rooms[5]->y = player->y;
	rooms[5]->setSolidTiles(new int[62]{ 1,6,8,9,10,11,14,19,20,21,22,27,28,29,30,35,36,37,38,40,41,42,43,44,45,46,47,74,92,93,95,96,97,98,99,100,101,102,103,104,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127 }, 62);
	rooms[5]->SetTileSprites(new SpriteSheet("Assets/tiles.tga", 64, 64));
	rooms[5]->wholeScrolling();

	Dungeon * d = new Dungeon(rooms, 6, "Dungeon");
	player->mainTheme = mainTheme;
	stage->setWorld(rooms[0]);
	player->entering = true;
	stage->addChild(d);
	stage->addChild(player);
}

void DungeonScene::Unload()
{
	stop_sample(caveAmb);
	destroy_sample(caveAmb);
	Dungeon * d = (Dungeon*)stage->findObjectByName("Dungeon");
	stage->removeChild(d);
	stage->removeChild(player);
	d->~Dungeon();
	player->~Player();
}

DungeonScene::~DungeonScene()
{
}
