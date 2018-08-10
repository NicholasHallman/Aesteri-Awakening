#pragma once
#include <vector>
#include "Display.h"
#include "TileMap.h"
#include "Player.h"
#include "DungeonScene.h"
#include "OverworldScene.h"
#include "TitleScene.h"
#include "Instructions.h"

class Stage 
{
public:
	Stage(int width, int height);
	void addChild(Display * child);
	void removeChild(Display * child);
	void removeChildByName(const char *);
	void addLogicChild(Display * child);
	void removeLogicChild(Display * child);
	void update();
	void setFPS(int fps);
	double getFPSinMS();
	void resortChildren();
	void runEventLoop();
	void addEventListener(const char* type, void (*EventFunction)());
	void setWorld(Display * tm);
	void runLogic();
	void runStart();
	void LoadOverWorld(int, int);
	void UnloadOverWorld();
	void LoadDungeon(int, int);
	void UnloadDungeon();
	void LoadIntro();
	void UnloadIntro();
	const char * scene;
	Display * findObjectByName(const char *);
	~Stage();
	float deltaTime = 0;
	Instructions * instruction;
protected:
	Player * player;
	Display* world;
	int w;
	int h;
	clock_t pastTime;
	bool flip = true;
	BITMAP * buffer1;
	BITMAP * buffer2;
	std::vector<Display*> children;
	std::vector<Display*> logicChildren;
	double fpsInMS = 16;
	void(*KeyEvent)();
	void(*FrameEvent)();
	DungeonScene * ds;
	OverworldScene * os;
	TitleScene * is;
	bool updateLock = false;
	bool releasedCtrl = true;
};

