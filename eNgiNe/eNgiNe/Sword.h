#pragma once
#include "Display.h"
class Sword :
	public Display
{
public:
	Sword(SpriteSheet * spritesheet, const char * name, int attk);
	void Logic();
	void Start();
	~Sword();
protected:
	int frameLock = 0;
	int attack = 0;
	bool animating[4];
	bool moving = true;
	bool released;
	int direction = 2;
};

