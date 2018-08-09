#include "OldMan.h"

OldMan::OldMan(SpriteSheet * sprites, const char * n)
{
	frames = sprites;
	currentFrame = frames->getFrame(0);
	pastTime = clock();
	name = n;
}

const char ** OldMan::getConversation(int which)
{
	switch (which) {
	case HELLO_THERE:
		return new const char *[7] { conversations[0], conversations[1], conversations[2], conversations[3], conversations[4], conversations[5], NULL};
		break;
	case WELCOME_BACK:
		return new const char *[3]{ conversations[6], conversations[7], NULL };
		break;
	case YOURE_BACK:
		return new const char *[4]{ conversations[8], conversations[9], conversations[10], NULL };
		break;
	case MANY_DANGERS:
		return new const char *[5]{ conversations[11], conversations[12], conversations[13], conversations[14], NULL };
		break;
	}
}

void OldMan::Logic(){
	if (walk) {
		setFPS(11);
		if (x != go[whichWalk] * 64) {
			if (x - go[whichWalk] * 64 > 0) {
				x -= 2;
			}
			if (x - go[whichWalk] * 64 < 0) {
				x += 2;
				animating[0] = false;
				if (!animating[1]) {
					animating[1] = true;
					gotoAndPlay("Right");
				}
			}
		}
		if (y != go[whichWalk + 1] * 64) {
			if (y - go[whichWalk + 1] * 64 > 0) {
				y -= 2;
				animating[1] = false;
				if (!animating[0]) {
					animating[0] = true;
					gotoAndPlay("Back");
				}
			}
			if (y - go[whichWalk + 1] * 64 < 0) {
				y += 2;
			}
			
		}
		if (go[whichWalk] * 64 == x && go[whichWalk + 1] * 64 == y) {
			whichWalk+=2;
			if (whichWalk == 6) {
				walk = false;
				x = go[whichWalk] * 64;
				y = go[whichWalk + 1] * 64;
				gotoAndPlay("Standing");
				setFPS(.5);
			}
		}
	}
}

OldMan::~OldMan()
{
}
