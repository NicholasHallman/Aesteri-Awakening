#pragma once
#include "Scene.h"
#include "Player.h"
class DungeonScene :
	public Scene
{
public:
	DungeonScene();
	void Load(int posx, int posy);
	void Unload();
	~DungeonScene();
private:
	SAMPLE * mainTheme;
	SAMPLE * caveAmb;
	Player * player;
};

