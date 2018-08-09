#pragma once
#include "Display.h"
class TextBox :
	public Display
{
public:
	TextBox(SpriteSheet * sprites, const char * n);
	void setText(const char **);
	void draw(BITMAP * buffer, int camX, int camY);
	bool cycleText();
	~TextBox();
protected:
	const char ** text;
	int currWidth = 0;
	int currSection = 0;
};

