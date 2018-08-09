#include "OverworldScene.h"
#include "eNgiNe.h"
#include "Bird.h"

OverworldScene::OverworldScene()
{
}

void OverworldScene::Load(int posx, int posy)
{
	Display * oldMan;
	Display * bird;
	Display * bird2;
	Display * boat;

	SpriteSheet * mapTiles = new SpriteSheet("Assets/tiles.tga", 64, 64);
	TileMap * tm = new TileMap("Assets/map.txt", 480, 88, "World", 3);
	tm->x = 157 * 64;
	tm->y = 67 * 64;
	tm->setSolidTiles(new int[62]{ 1,6,8,9,10,11,14,19,20,21,22,27,28,29,30,35,36,37,38,40,41,42,43,44,45,46,47,74,92,93,95,96,97,98,99,100,101,102,103,104,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127 }, 62);
	tm->SetTileSprites(mapTiles);
	tm->initDraw();
	tm->warp = false;
	tm->wholeScrolling();

	stage->addChild(tm);

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
	player->setFPS(10);
	player->setTileMap(tm);
	stage->setWorld(player);

	oldMan = new OldMan(new SpriteSheet("Assets/oldman.tga", 64, 64), "OldMan");
	oldMan->x = 421 * 64;
	oldMan->y = 66 * 64;
	oldMan->addAnimation("Standing", new int[3]{ 0, 1, -1 }, NULL);
	oldMan->addAnimation("Right", new int[4]{ 3,4,5,-1 }, NULL);
	oldMan->addAnimation("Back", new int[4]{ 6,7,8,-1 }, NULL);
	oldMan->setFPS(.5);
	oldMan->gotoAndPlay("Standing");

	SpriteSheet * birdss = new SpriteSheet("Assets/BIRD.tga", 32, 32);
	bird = new Bird(birdss, "Bird1");
	bird->x = 153 * 64;
	bird->y = 64 * 64;
	bird->addAnimation("Standing", new int[11]{ 0,0,0,0,0,1,0,1,0,1,-1 }, NULL);
	bird->addAnimation("Flying", new int[3]{ 2,3,-1 }, NULL);
	bird->setFPS(5);
	bird->gotoAndPlay("Standing");

	SpriteSheet * birdss2 = new SpriteSheet("Assets/BIRD2.tga", 32, 32);
	bird2 = new Display(birdss2, "Bird2");
	bird2->x = 161 * 64;
	bird2->y = 63 * 64;
	bird2->addAnimation("Standing", new int[15]{ 0,0,0,0,0,0,1,0,1,0,1,1,0,1,-1 }, NULL);
	bird2->setFPS(5);
	bird2->gotoAndPlay("Standing");

	boat = new Display(new SpriteSheet("Assets/Boat.tga", 128, 128), "Boat");
	boat->x = 315 * 64;
	boat->y = 54 * 64;
	boat->addAnimation("Float", new int[3]{ 0,1,-1 }, NULL);
	boat->setFPS(2);
	boat->gotoAndPlay("Float");
	boat->hide = false;

	stage->addChild(oldMan);
	stage->addChild(bird);
	stage->addChild(bird2);
	stage->addChild(boat);
	stage->addChild(player);

	mainTheme = load_wav("Assets/overworld.wav");
	play_sample(mainTheme, 255, 128, 1000, 1);
}

void OverworldScene::Unload()
{
	Display * oldman = stage->findObjectByName("OldMan");
	Display * b1 = stage->findObjectByName("Bird1");
	Display * b2 = stage->findObjectByName("Bird2");
	Display * tm = stage->findObjectByName("World");
	stage->removeChild(oldman);
	stage->removeChild(b1);
	stage->removeChild(b2);
	stage->removeChild(tm);
	stage->removeChild(player);
	oldman->~Display();
	b1->~Display();
	b2->~Display();
	TileMap * tilemap = (TileMap*)tm;
	tilemap->~TileMap();
	player->~Player();
}

OverworldScene::~OverworldScene()
{
}
