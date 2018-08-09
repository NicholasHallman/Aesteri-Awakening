#pragma once
#include <allegro.h>
class SpriteSheet
{
public:
	SpriteSheet(const char *, int w, int h);
	BITMAP* getFrame(int i);
	int * getSpriteSize();
	~SpriteSheet();
protected:
	int totalFrames = 0;
	int currentFrame = 0;
	BITMAP ** sprites;
};

