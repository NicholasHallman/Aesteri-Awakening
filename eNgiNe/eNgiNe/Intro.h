#pragma once
#include "Display.h"
class Intro :
	public Display
{
public:
	Intro(const char * folder);
	void draw(BITMAP * buffer);
	void Logic();
	~Intro();
private:
	BITMAP * * frames = new BITMAP*[30];
	int currFrame = 0;
	float blinkFrame = 0;
	bool blink;
};

