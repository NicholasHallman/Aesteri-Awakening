#include "Scene.h"
#include "Player.h"
#pragma once
class OverworldScene:
	public Scene
{
public:
	OverworldScene();
	void Load(int posx, int posy);
	void Unload();
	~OverworldScene();
private:
	Player * player;
	SAMPLE * mainTheme;
};

