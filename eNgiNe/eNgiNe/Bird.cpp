#include "Bird.h"
#include "eNgiNe.h"


Bird::Bird(SpriteSheet * sprites, const char * n)
{
	frames = sprites;
	currentFrame = frames->getFrame(0);
	pastTime = clock();
	name = n;
}

void Bird::Start() {
	player = stage->findObjectByName("Player");
}

void Bird::Logic() {
	double distance = sqrt(pow(player->x - x, 2) + pow(player->y - y, 2));
	if (distance < 2 * 64) {
		flying = true;
		gotoAndPlay("Flying");
		setFPS(11);
	}
	if (flying) {
		x += 2;
		y -= 2;
	}
}

Bird::~Bird()
{
}
