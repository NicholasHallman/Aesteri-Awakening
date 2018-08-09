#pragma once
#include "Display.h"
#include "TileMap.h"
#include "OldMan.h"
#include "TextBox.h"
#include "Sword.h"
class Player :
	public Display
{
public:
	Player(SpriteSheet * ss, const char * n);
	void Logic();
	void Start();
	void setTileMap(TileMap * tm);
	int keys = 0;
	bool stopMovement = false;
	bool entering = false;
	bool introAnim = false;
	SAMPLE * mainTheme;
	~Player();
protected:
	int frameLock = 0;
	SAMPLE * running;
	SAMPLE * swing;
	bool oldwalk = false;
	bool interacting = false;
	Display * indicator;
	Display * explosion;
	TileMap * tilemap;
	OldMan * oldman;
	TextBox * textContainer;
	void initIronSword(Sword * sword);
	void initGoldSword(Sword * sword);
	Sword * sword;
	bool releasedE = true;
	bool boating = false;
	int monolith = 0;
	SAMPLE * swoosh;
	bool rest = false;
	int * monolithPos = new int[40]{ 22,11,24,43,56,49,79,54,93,56,131,75,157,65,182,75,173,24,181,34,238,42,360,23,371,31,367,41,346,51,401,58,412,35,423,63,435,27,450,44 };
	int * ironSwordPos = new int[2]{ 403,19 };
	int * goldSwordPos = new int[2]{ 59,18 };
	int * dDoorPos = new int[4]{ 59,16,60,16 };
	int * dExit = new int[3]{ 10,11,0 };
	int * dMonolith = new int[3]{10,6,3};
	int * boatPos = new int[2]{ 317,54 };
	
};

