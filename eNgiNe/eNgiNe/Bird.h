#pragma once
#include "Display.h"
class Bird :
	public Display
{
public:
	Bird(SpriteSheet * sprites, const char * n);
	~Bird();
	void Logic();
	void Start();
protected:
	Display * player;
	bool flying = false;
};

