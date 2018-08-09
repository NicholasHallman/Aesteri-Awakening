#include "eNgiNe.h"
#include "Player.h"
#include "Bird.h"
#include "Sword.h"
#include "OldMan.h"
#include "Dungeon.h"
#include <cmath>

Stage * stage;

int t = 0;
double j = 0;
bool drop = false;

int main() {
	// given the assumption the game is coded for 30 fps speeds
	// vary movement based on the real framerate
	double fps = 240;
	double target = 30;
	stage = eNgiNe_init(1366, 768, fps);

	font = load_font("Assets/font.pcx", NULL, NULL);
	
	stage->scene = "Intro";

	if (stage->scene == "Overworld") {
		stage->LoadOverWorld(429,59);
		stage->runEventLoop();
	}
	if (stage->scene == "Dungeon") {
		stage->LoadDungeon(10,9);
		stage->runEventLoop();
	}
	if (stage->scene == "Intro") {
		stage->LoadIntro();
		stage->runEventLoop();
	}
	return 0;
}
END_OF_MAIN();
