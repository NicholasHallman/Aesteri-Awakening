#include "Sword.h"
#include "eNgiNe.h"


Sword::Sword(SpriteSheet * sprites, const char * n, int attk)
{
	frames = sprites;
	currentFrame = frames->getFrame(0);
	pastTime = clock();
	name = n;
	released = true;
	animating[0] = false;
	animating[1] = false;
	animating[2] = false;
	animating[3] = false;
	attack = attk;
}

void Sword::Logic()
{
	if (moving && frameLock == 0) {
		x = 0;
		y = 0;
		if (key[KEY_W]) {
			direction = 0;
			if (!animating[0]) {
				animating[0] = true;
				gotoAndPlay("back");
			}
		}
		if (key[KEY_D]) {
			direction = 1;
			if (!animating[1]) {
				animating[1] = true;
				gotoAndPlay("right");
			}
		}
		if (key[KEY_S]) {
			direction = 2;
			if (!animating[2]) {
				animating[2] = true;
				gotoAndPlay("forward");
			}
		}
		if (key[KEY_A]) {
			direction = 3;
			if (!animating[3]) {
				animating[3] = true;
				gotoAndPlay("left");
			}
		}
	}
	if (key[KEY_SPACE]){
		moving = false;
		released = false;
		switch (direction) {
		case 0:
			gotoAndPlay("stabback");
			y = -32;
			break;
		case 1:
			gotoAndPlay("stabright");
			x = 33;
			break;
		case 2:
			gotoAndPlay("stabforward");
			y = 32;
			break;
		case 3:
			gotoAndPlay("stableft");
			x = -29;
			break;
		} 
		if (frameLock == 0) {
			frameLock = 60;
		}
	}
	if (!key[KEY_SPACE] && !released && frameLock == 0) {
		moving = true;
		released = true;
		switch (direction) {
		case 0:
			gotoAndPlay("back");
			break;
		case 1:

			gotoAndPlay("right");
			break;
		case 2:
			gotoAndPlay("forward");
			break;
		case 3:
			gotoAndPlay("left");
			break;
		}
		gotoFirstAnimFrame();
	}

	if (!key[KEY_W] && animating[0]) {
		animating[0] = false;
		if (animating[1]) gotoAndPlay("right");
		if (animating[2]) gotoAndPlay("forward");
		if (animating[3]) gotoAndPlay("left");
	}
	if (!key[KEY_D] && animating[1]) {
		animating[1] = false;
		if (animating[0]) gotoAndPlay("back");
		if (animating[2]) gotoAndPlay("forward");
		if (animating[3]) gotoAndPlay("left");
	}
	if (!key[KEY_S] && animating[2]) {
		animating[2] = false;
		if (animating[0]) gotoAndPlay("back");
		if (animating[1]) gotoAndPlay("right");
		if (animating[3]) gotoAndPlay("left");
	}
	if (!key[KEY_A] && animating[3]) {
		animating[3] = false;
		if (animating[0]) gotoAndPlay("back");
		if (animating[1]) gotoAndPlay("right");
		if (animating[2]) gotoAndPlay("forward");
	}
	if (!animating[0] && !animating[1] && !animating[2] && !animating[3]) {
		gotoFirstAnimFrame();
	}
	if(frameLock != 0) frameLock--;
}

void Sword::Start()
{
}


Sword::~Sword()
{
	frames->~SpriteSheet();
	destroy_bitmap(currentFrame);
}
