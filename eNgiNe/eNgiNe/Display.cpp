#include "Display.h"
#include <allegro.h>
#include "eNgiNe.h"

Display::Display() {}

Display::Display(SpriteSheet * sprites, const char * n)
{
	frames = sprites;
	currentFrame = frames->getFrame(0);
	pastTime = clock();
	name = n;
}

void Display::transform(int newx, int newy, int timeinMs, int fps)
{
	//16 = 1000 / 60
	//result = timeinMS / (fps / 1000)
	int steps = timeinMs / (fps / 1000);
	dx = (newx - x) / steps;
	dy = (newy - y) / steps;
}

void Display::draw(BITMAP * buffer, int camX, int camY)
{
	set_alpha_blender();
	clock_t presentTime = clock();
	if (!hide) {
		if (fps == 0 || presentTime - pastTime > fps) {
			if (play && frameSequence != NULL) {
				if (frameSequence[currentIndex] == -1 && loop) {
					currentIndex = 0;
					playCount++;
				}
				else if (frameSequence[currentIndex] == -1 && !loop) {
					currentIndex -= 1;
					Stop();
				}
				currentFrame = frames->getFrame(frameSequence[currentIndex]);
				currentIndex++;
				
				if (moveSequence != NULL && moveSequence[currentIndex].x != -1 && moveSequence[currentIndex].y != -1) {
					x = moveSequence[currentIndex].x;
					y = moveSequence[currentIndex].y;
				}
			}
			else if (play && frameSequence == NULL) {
				BITMAP * temp = frames->getFrame(currentIndex);
				if (temp != NULL) {
					currentFrame = temp;
				}
				else {
					currentIndex = 0;
				}
			}
			pastTime = clock();
		}
		if (this->name == "Player") {
			int t = 0;
		}
		draw_trans_sprite(buffer, currentFrame, x - (camX - SCREEN_W / 2) + dx, y - (camY - SCREEN_H / 2) + dy);
		for (int i = 0; i < children.size(); i++) {
			children.at(i)->draw(buffer, x - camX + dx, y - camY + dy);
		}
	}
}

void Display::Play()
{
	play = true;
}

void Display::Stop()
{
	play = false;
}

void Display::gotoAndPlay(int index)
{
	playCount = 0;
	if (frames->getFrame(index) != NULL) {
		currentFrame = frames->getFrame(index);
	}
	moveSequence = NULL;
	frameSequence = NULL;
	play = true;
	return;
}

void Display::gotoAndPlay(const char * animation)
{
	playCount = 0;
	frameSequence = animations.at(animation);
	moveSequence = positions.at(animation);
	play = true;
	currentIndex = 0;
}

void Display::addAnimation(const char * key, int * animationSequence, int2 * moveSequence)
{
	animations.insert(std::pair<const char*, int*>(key,animationSequence));
	positions.insert(std::pair<const char*, int2*>(key, moveSequence));
}

void Display::gotoFirstAnimFrame()
{
	if (frameSequence != NULL) {
		currentFrame = frames->getFrame(frameSequence[0]);
		Stop();
	}
}

void Display::setFPS(double f)
{
	fps = 1000 / f;
}

void Display::addChild(Display * child)
{
	children.push_back(child);
}

void Display::removeChild(Display * child)
{
	for (int i = 0; i < children.size(); i++) {
		if (children.at(i) == child) {
			children.erase(children.begin() + i);
		}
	}
}

void Display::Start() {

}

void Display::Logic()
{
}


Display::~Display()
{
}
END_OF_FUNCTION(update);
