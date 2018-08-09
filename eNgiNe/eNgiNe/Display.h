#pragma once
#include <map>
#include <ctime>
#include <vector>
#include "SpriteSheet.h"
#include "int2.h"

class Display
{
public:
	Display();
	Display(SpriteSheet * spritesheet, const char * name);
	void transform(int x, int y, int timedelta, int fps);
	void virtual draw(BITMAP * buffer, int camX, int camY);
	void Play();
	void Stop();
	void gotoAndPlay(int index);
	void gotoAndPlay(const char * animation);
	void addAnimation(const char * key, int * animationSequence, int2 * moveSequence);
	void gotoFirstAnimFrame();
	void addChild(Display * child);
	void removeChild(Display * child);
	void setFPS(double f);
	void virtual Logic();
	void virtual Start();
	double x = 0;
	double y = 0;
	bool hide = false;
	const char * name;
	int z = 0;
	int playCount = 0;
	bool loop = true;
	double dx = 0;
	double dy = 0;
	~Display();
protected:
	double fps = 0;
	const char * currentAnimation;
	int * frameSequence;
	int2 * moveSequence;
	bool play = false;
	SpriteSheet * frames;
	BITMAP * currentFrame;
	int currentIndex = 0;
	std::map<const char*, int*> animations;
	std::map<const char*, int2*> positions;
	clock_t pastTime;
	std::vector<Display*> children;
};

