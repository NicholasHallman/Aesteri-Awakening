#include "Player.h"
#include "Sword.h"
#include "eNgiNe.h"
#include "Dungeon.h"

Dungeon * d;

Player::Player(SpriteSheet * sprites, const char * n)
{
	frames = sprites;
	currentFrame = frames->getFrame(0);
	pastTime = clock();
	name = n;
}

void Player::Start() {

	running = load_sample("Assets/running.wav");
	swing = load_sample("Assets/swing.wav");
	SpriteSheet * indicatorss = new SpriteSheet("Assets/Indicator.tga", 32, 32);
	indicator = new Display(indicatorss, "Indicator");
	indicator->x = 64;
	indicator->y = -32;
	indicator->setFPS(5);
	indicator->hide = true;
	indicator->addAnimation("Blink", new int[3]{ 0,1,-1 }, NULL);
	indicator->gotoAndPlay("Blink");
	addChild(indicator);

	SpriteSheet * ironSword = new SpriteSheet("Assets/IronSword.tga", 64, 64);
	SpriteSheet * swordwood = new SpriteSheet("Assets/WoodenSword.tga", 64, 64);
	sword = new Sword(swordwood, "Sword", 1);
	sword->addAnimation("forward", new int[5]{ 0,1,0,2,-1 }, NULL);
	sword->addAnimation("right", new int[5]{ 5,6,5,7,-1 }, NULL);
	sword->addAnimation("left", new int[5]{ 10,11,10,12,-1 }, NULL);
	sword->addAnimation("back", new int[5]{ 15,16,15,17,-1 }, NULL);
	sword->addAnimation("stabforward", new int[2]{ 4,-1 }, NULL);
	sword->addAnimation("stabright", new int[2]{ 9,-1 }, NULL);
	sword->addAnimation("stableft", new int[2]{ 14,-1 }, NULL);
	sword->addAnimation("stabback", new int[2]{ 19,-1 }, NULL);
	sword->x = 0;
	sword->y = 0;
	sword->setFPS(10);
	this->addChild(sword);
	stage->addLogicChild(sword);

	explosion = new Display(new SpriteSheet("Assets/explosion.tga", 320, 320), "explosion");
	explosion->x = -130;
	explosion->y = -100;
	explosion->setFPS(11);
	explosion->addAnimation("Boom", new int[15]{ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,-1 }, NULL);
	explosion->loop = false;
	addChild(explosion);

	swoosh = load_wav("Assets/swoosh.wav");

	if (stage->scene == "Overworld") {
		oldman = (OldMan *)stage->findObjectByName("OldMan");

		textContainer = new TextBox(new SpriteSheet("Assets/textBox.tga", 1280, 267), "textCon");
		textContainer->x = -(SCREEN_W / 2) + (86 / 2);
		textContainer->y = 100;
		textContainer->hide = true;
		addChild(textContainer);
	}
	else if (stage->scene = "Dungeon") {
		d = (Dungeon*)stage->findObjectByName("Dungeon");
	}

}

void Player::setTileMap(TileMap * tm)
{
	tilemap = tm;
}

int facing = 2;
bool released = true;
bool animating[4];

void Player::Logic()
{	
	//Keyboard and Animation Logic
	int speed = 10;
	if (key[KEY_LSHIFT]) {
		speed = 20;
		setFPS(20);
	}
	else {
		speed = 10;
		setFPS(10);
	}
	if (!stopMovement && !entering && frameLock == 0) {
		if (key[KEY_A]) {
			facing = 3;
			if (!tilemap->isSolid(x - speed * stage->deltaTime, y)) {
				x -= speed * stage->deltaTime;
			}
			if (!animating[3]) {
				gotoAndPlay("left");
				animating[3] = true;
				stop_sample(running);
				play_sample(running, 128, 128, 1000, 1);
			}
		}
		if (key[KEY_D]) {
			facing = 1;
			if (!tilemap->isSolid(x + speed * stage->deltaTime, y)) {
				x += speed * stage->deltaTime;
			}
			if (!animating[1]) {
				gotoAndPlay("right");
				animating[1] = true;
				stop_sample(running);
				play_sample(running, 128, 128, 1000, 1);
			}
		}
		if (key[KEY_W]) {
			facing = 0;
			if (!tilemap->isSolid(x, y - speed * stage->deltaTime)) {
				y -= speed * stage->deltaTime;
			}
			if (!animating[0]) {
				gotoAndPlay("back");
				animating[0] = true;
				stop_sample(running);
				play_sample(running, 128, 128, 1000, 1);
			}
		}
		if (key[KEY_S]) {
			facing = 2;
			if (!tilemap->isSolid(x, y + speed * stage->deltaTime)) {
				y += speed * stage->deltaTime;
			}
			if (!animating[2]) {
				gotoAndPlay("forward");
				animating[2] = true;
				stop_sample(running);
				play_sample(running, 128, 128, 1000, 1);
			}
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
			stop_sample(running);
		}
	}
	if (key[KEY_SPACE] && released) {
		play_sample(swing, 256, 128, 1000, 0);
		stop_sample(running);
		switch (facing) {
		case 0:
			gotoAndPlay("stabback");
			break;
		case 1:
			gotoAndPlay("stabright");
			break;
		case 2:
			gotoAndPlay("stabforward");
			break;
		case 3:
			gotoAndPlay("stableft");
			break;
		}
		if (frameLock == 0) {
			frameLock = 60;
		}
		released = false;
		stopMovement = true;
	}
	else if (!key[KEY_SPACE] && !released && frameLock == 0) {
		switch (facing) {
		case 0:
			gotoAndPlay("back");
			if (!animating[0]) {
				gotoFirstAnimFrame();
			}
			break;
		case 1:
			gotoAndPlay("right");
			if (!animating[1]) {
				gotoFirstAnimFrame();
			}
			break;
		case 2:
			gotoAndPlay("forward");
			if (!animating[2]) {
				gotoFirstAnimFrame();
			}
			break;
		case 3:
			gotoAndPlay("left");
			if (!animating[3]) {
				gotoFirstAnimFrame();
			}
			break;
		}

		released = true;
		stopMovement = false;
	}
	if (frameLock != 0) frameLock--;

	//Overworld Code
	
	if (stage->scene == "Overworld") {
		//Interaction Logic

		//Old Man
		double distance = sqrt(pow(oldman->x - x, 2) + pow(oldman->y - y, 2));
		if (distance < 2 * frames->getSpriteSize()[0]) {
			if (key[KEY_E] && releasedE) {
				releasedE = false;
				interacting = true;
				indicator->hide = true;
				textContainer->hide = false;
				if (oldman->times == 0 && monolith != 9) {

					const char ** toSay = oldman->getConversation(HELLO_THERE);
					char * buffer = new char[64];
					sprintf_s(buffer, 64, toSay[5], 9 - monolith);
					toSay[5] = buffer;
					textContainer->setText(toSay);
					oldman->times++;
				}
				else if (monolith < 9) {
					const char ** toSay = oldman->getConversation(WELCOME_BACK);
					char * buffer = new char[64];
					sprintf_s(buffer, 64, toSay[1], 9 - monolith);
					toSay[1] = buffer;
					textContainer->setText(toSay);
				}
				else if (monolith == 9 && oldman->x != 405 * 64) {
					textContainer->setText(oldman->getConversation(YOURE_BACK));
					oldwalk = true;
					tilemap->SetTile(403, 25, 88);
					tilemap->wholeScrolling();
				}
				else if (monolith == 9 && oldman->x == 405 * 64) {
					textContainer->setText(oldman->getConversation(MANY_DANGERS));
					Display * boat = stage->findObjectByName("Boat");
					boat->hide = false;
				}
			}
			else if (!interacting) {
				indicator->hide = false;
			}
		}
		else {
			if (oldwalk) {
				oldman->walk = true;
				oldwalk = false;
			}
			interacting = false;
			indicator->hide = true;
			textContainer->hide = true;
		}

		//monolith code
		bool foundone = false;
		int position[2];
		for (int i = 0; i < 40; i += 2) {
			if (monolithPos[i] != NULL && monolithPos[i + 1] != NULL) {
				distance = sqrt(pow(monolithPos[i] * frames->getSpriteSize()[0] - x, 2) + pow(monolithPos[i + 1] * frames->getSpriteSize()[0] - y, 2));
				if (distance < 1.5 * frames->getSpriteSize()[0]) {
					foundone = true;
					position[0] = monolithPos[i];
					position[1] = monolithPos[i + 1];
				}
			}
		}
		if (foundone) {
			indicator->hide = false;
			if (key[KEY_E] && releasedE) {
				releasedE = false;
				explosion->gotoAndPlay("Boom");
				int tile = tilemap->GetTile(position[0], position[1]);
				switch (tile) {
				case 101:
					tilemap->SetTile(position[0], position[1], 1);
					break;
				case 105:
					tilemap->SetTile(position[0], position[1], 95);
					break;
				case 102:
					tilemap->SetTile(position[0], position[1], 26);
					break;
				}
				play_sample(swoosh, 255, 128, 1000, 0);
				tilemap->wholeScrolling();
				monolith += 1;
				int k = 0;
				while (position[0] != monolithPos[k]) {
					k++;
				}
				monolithPos[k] = NULL;
				monolithPos[k + 1] = NULL;
			}
		}

		//Iron Sword 
		if (ironSwordPos[0] != NULL) {
			distance = sqrt(pow(x - ironSwordPos[0] * 64, 2) + pow(y - ironSwordPos[1] * 64, 2));
			if (distance < 1.5 * 64) {
				indicator->hide = false;
				if (key[KEY_E]) {
					tilemap->SetTile(403, 19, 99);
					tilemap->wholeScrolling();
					initIronSword(sword);
					stopMovement = true;
					gotoAndPlay("spin");
					rest = true;
					ironSwordPos[0] = NULL;
				}
			}
		}
		// Dungeon Door Code
		for (int i = 0; i < 2; i++) {
			distance = sqrt(pow((x + 32) - dDoorPos[i] * 64, 2) + pow((y + 64) - dDoorPos[i+1] * 64, 2));
			if (distance < 2 * 64) {
				//Load Dungeon
				stage->scene = "Dungeon";
				stage->UnloadOverWorld();
				stage->LoadDungeon(10,10);
				stop_sample(running);
				stage->runEventLoop();
			}
		}

		//Boat code
		distance = sqrt(pow((x + 32) - boatPos[0] * 64, 2) + pow((y + 64) -boatPos[1] * 64, 2));
		if (distance < 1 * 64) {
			Display * boat = stage->findObjectByName("Boat");
			if (!boat->hide) {
				indicator->hide = false;
				if (key[KEY_E]) {
					stopMovement = true;
					x = boat->x + 32;
					y = boat->y + 32;
					boating = true;
					//do boat stuff
				}
			}
		}

		if (boating) {
			Display * boat = stage->findObjectByName("Boat");
			if (x > 242 * 64) {
				x-=5;
				boat->x-=5;
			}
			else {
				stopMovement = false;
				boating = false;
				x = 239 * 64;
				y = 56 * 64;
				boatPos[0] = 240;
				boatPos[0] = 56;
			}
		}

		//Wait animation Code
		if (rest && playCount >= 1) {
			stopMovement = false;
			rest = false;
		}

		// E code
		if (!key[KEY_E] && !releasedE) {
			releasedE = true;
		}
	}
	//Dungeon Code
	if (stage->scene == "Dungeon") {
		//Dungeon walk in animtaion
		if (entering && introAnim) {
			play_sample(running, 128, 128, 1000, 0);
			stopMovement = true;
			entering = false;
			gotoAndPlay("back");
		}
		else if (stopMovement && introAnim) {
			if (mainTheme != NULL) {
				adjust_sample(mainTheme, (y - (6 * 64)) * 256 / ((10 * 64) - (6 * 64)), 128, 1000, 1); // fade out main theme
			}
			y--;
			if (y < 6 * 64) {
				if (mainTheme != NULL) {
					stop_sample(mainTheme);
					destroy_sample(mainTheme);
				}
				stopMovement = false;
				stop_sample(running);
				introAnim = false;
			}
		}

		if (d->getRoom() == dExit[2] && !d->transition) {
			int distance = sqrt(pow(x - dExit[0] * 64, 2) + pow(y - dExit[1] * 64, 2));
			if (distance < 1 * 64) {
				//Load Overworld
				stage->scene = "Overworld";
				stage->UnloadDungeon();
				stage->LoadOverWorld(59, 19);
				stop_sample(running);
				stage->runEventLoop();
			}
		}

		// Dungeon Monolith 
		if (dMonolith[0] != NULL) {
			if (d->getRoom() == dMonolith[2]) {
				int distance = sqrt(pow(x - dMonolith[0] * 64, 2) + pow(y - dMonolith[1] * 64, 2));
				if (distance < 2 * 64) {
					indicator->hide = false;
					if (key[KEY_E]) {
						monolith++;
						explosion->gotoAndPlay("Boom");
						play_sample(swoosh,256,128,1000,0);
						TileMap * room = d->getRooms()[dMonolith[2]];
						room->SetTile(dMonolith[0], dMonolith[1], 25);
						room->wholeScrolling();
						dMonolith[0] = NULL;
						dMonolith[1] = NULL;

					}
				}
				else {
					indicator->hide = true;
				}
			}
		} else indicator->hide = true;
	}
}


Player::~Player()
{
}

void Player::initIronSword(Sword * sword) {
	stage->removeLogicChild(sword);
	removeChild(sword);
	sword->~Sword();
	sword = new Sword(new SpriteSheet("Assets/IronSword.tga", 64, 64), "sword", 2);
	sword->addAnimation("forward", new int[5]{ 0,1,0,2,-1 }, NULL);
	sword->addAnimation("right", new int[5]{ 5,6,5,7,-1 }, NULL);
	sword->addAnimation("left", new int[5]{ 10,11,10,12,-1 }, NULL);
	sword->addAnimation("back", new int[5]{ 15,16,15,17,-1 }, NULL);
	sword->addAnimation("stabforward", new int[2]{ 4,-1 }, NULL);
	sword->addAnimation("stabright", new int[2]{ 9,-1 }, NULL);
	sword->addAnimation("stableft", new int[2]{ 14,-1 }, NULL);
	sword->addAnimation("stabback", new int[2]{ 19,-1 }, NULL);
	sword->x = 0;
	sword->y = 0;
	stage->addLogicChild(sword);
	addChild(sword);
}

void Player::initGoldSword(Sword * sword) {
	stage->removeLogicChild(sword);
	removeChild(sword);
	sword->~Sword();
	sword = new Sword(new SpriteSheet("Assets/GoldSword.tga", 64, 64), "sword", 4);
	sword->addAnimation("forward", new int[5]{ 0,1,0,2,-1 }, NULL);
	sword->addAnimation("right", new int[5]{ 5,6,5,7,-1 }, NULL);
	sword->addAnimation("left", new int[5]{ 10,11,10,12,-1 }, NULL);
	sword->addAnimation("back", new int[5]{ 15,16,15,17,-1 }, NULL);
	sword->addAnimation("stabforward", new int[2]{ 4,-1 }, NULL);
	sword->addAnimation("stabright", new int[2]{ 9,-1 }, NULL);
	sword->addAnimation("stableft", new int[2]{ 14,-1 }, NULL);
	sword->addAnimation("stabback", new int[2]{ 19,-1 }, NULL);
	sword->x = 0;
	sword->y = 0;
	stage->addLogicChild(sword);
	addChild(sword);
}
