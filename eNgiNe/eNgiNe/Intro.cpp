#include "Intro.h"
#include "eNgiNe.h"


Intro::Intro(const char * folder)
{
	blink = false;
	currFrame = 0;
	for (int i = 0; i < 30; i++) {
		const char * toSay = "Assets/Intro/%d.tga";
		char buffer[20];
		sprintf_s(buffer, 20, toSay, i + 1);
		frames[i] = load_bitmap(buffer, NULL);
	}
}

void Intro::draw(BITMAP * buffer)
{
	int limiter = 8;
	stretch_blit(frames[(int)currFrame/limiter], buffer, 0, 0, frames[(int)currFrame/limiter]->w, frames[(int)currFrame/limiter]->h, 0, 0, SCREEN_W, SCREEN_H);
	currFrame++;
	if (currFrame > 29 * limiter) {
		currFrame = 29 * limiter;
		float * mod = (float*)2;
		if ( blinkFrame > 60) {
			blinkFrame = 0;
			blink = !blink;
		}
		if (blink) {
			textout_centre_ex(buffer, font, "PRESS ENTER", SCREEN_W / 2 + 20, SCREEN_H / 5 * 4, makecol(255, 255, 255), -1);
		}
		textout_centre_ex(buffer, font, "HELP CTRL - H", SCREEN_W / 2 + 20, (SCREEN_H / 5 * 4) + 45, makecol(255, 255, 255), -1);
		blinkFrame+=1;
	}
}

void Intro::Logic() {
	if (key[KEY_ENTER]) {
		stage->LoadOverWorld(429, 59);
		stage->UnloadIntro();
		stage->scene = "Overworld";
		stage->runEventLoop();
	}
}


Intro::~Intro()
{
	for (int i = 0; i < 30; i++) {
		destroy_bitmap(frames[i]);
	}
}
