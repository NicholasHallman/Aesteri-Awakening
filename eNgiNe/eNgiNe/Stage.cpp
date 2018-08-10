#include <algorithm>
#include "Stage.h"
#include "TileMap.h"
#include "Player.h"
#include "Bird.h"
#include "Sword.h"
#include "OldMan.h"
#include "Dungeon.h"
#include "DungeonScene.h"

bool first = true;

bool sortHelper(Display * a, Display * b)
{
	return a->z < b->z;
}

Stage::Stage(int width, int height)
{
	w = width; 
	h = height;
	pastTime = clock();
	buffer1 = create_bitmap(w, h);
	buffer2 = create_bitmap(w, h);
	ds = new DungeonScene;
	os = new OverworldScene;
	is = new TitleScene;
	instruction = new Instructions();
	instruction->hide = true;
}

void Stage::addChild(Display * child)
{
	children.push_back(child);
}

void Stage::removeChild(Display * child)
{
	for (int i = 0; i < children.size(); i++) {
		if (children.at(i) == child) {
			children.erase(children.begin() + i);
		}
	}
}

void Stage::removeChildByName(const char * n)
{
	for (int i = 0; i < children.size(); i++) {
		if (children.at(i)->name == n) {
			children.erase(children.begin() + i);
		}
	}
}

void Stage::addLogicChild(Display * child)
{
	logicChildren.push_back(child);
}

void Stage::removeLogicChild(Display * child)
{
	for (int i = 0; i < logicChildren.size(); i++) {
		if (logicChildren.at(i) == child) {
			logicChildren.erase(logicChildren.begin() + i);
		}
	}
}

void Stage::update()
{
	BITMAP * buffer;
	
	if (flip) {
		buffer = buffer1;
		flip = !flip;
	}
	else {
		buffer = buffer2;
		flip = !flip;
	}
	clear_bitmap(buffer);
	
	for (int i = 0; i < children.size(); i++) {
		if (TileMap* v = dynamic_cast<TileMap*>(children.at(i))) {
			// old was safely casted to NewType
			v->draw(buffer);
		}
		else if (Dungeon* v = dynamic_cast<Dungeon*>(children.at(i))) {
			v->draw(buffer);
		}
		else if (Intro* v = dynamic_cast<Intro*>(children.at(i))) {
			v->draw(buffer);
		}
		else {
			Display * temp = children.at(i);
			temp->draw(buffer, world->x, world->y);
		}
	}
	instruction->draw(buffer);
	blit(buffer, screen, 0, 0, 0, 0, w, h);
	
}

void Stage::setFPS(int fps)
{
	fpsInMS = 1000 / fps;
	double target = 30;
	deltaTime = target / fps;
}

double Stage::getFPSinMS()
{
	return fpsInMS;
}

void Stage::resortChildren()
{
	std::sort(children.begin(), children.end(), sortHelper);
}

void Stage::runLogic() {
	for (int i = 0; i < children.size(); i++) {
		children.at(i)->Logic();
	}
	for (int i = 0; i < logicChildren.size(); i++) {
		logicChildren.at(i)->Logic();
	}
}

void Stage::runStart() {
	for (int i = 0; i < children.size(); i++) {
		children.at(i)->Start();
	}
	for (int i = 0; i < logicChildren.size(); i++) {
		logicChildren.at(i)->Start();
	}
}

void Stage::LoadOverWorld(int posx, int posy)
{
	setFPS(240);
	os->Load(posx, posy);
}

void Stage::UnloadOverWorld() {
	os->Unload();
}

void Stage::LoadDungeon(int posx, int posy)
{
	setFPS(120);
	ds->Load(posx, posy);
}

void Stage::UnloadDungeon() 
{
	ds->Unload();
}

void Stage::LoadIntro()
{
	setFPS(120);
	is->Load();
}

void Stage::UnloadIntro()
{
	is->Unload();
}

void Stage::runEventLoop()
{
	runStart();
	while (true) {
		if (key[KEY_ESC]) return;
		if (key[KEY_LCONTROL] && key[KEY_H] && instruction->hide && releasedCtrl) {
			instruction->hide = false;
			updateLock = true;
			releasedCtrl = false;
		}
		else if (key[KEY_LCONTROL] && key[KEY_H] && !instruction->hide && releasedCtrl) {
			instruction->hide = true;
			updateLock = false;
			releasedCtrl = false;
		}
		if (!key[KEY_LCONTROL] && !key[KEY_H] && !releasedCtrl) releasedCtrl = true;

		clock_t currentTime = clock();
		if (currentTime - pastTime > fpsInMS) {
			clock_t time = clock();
			if (KeyEvent != NULL) {
				KeyEvent();
			}
			if (FrameEvent != NULL) {
				FrameEvent();
			}
			if (!updateLock) runLogic();
			instruction->Logic();
			update();
			
			//pastTime = clock();
			//clock_t duration = clock() - time;
			//deltaTime = (30 / (double)1000 / (double)duration) * 10;
		}
	}
}

void Stage::addEventListener(const char * type, void(*EventFunction)())
{
	if (type == "Keyboard") KeyEvent = EventFunction;
	if (type == "Frame") FrameEvent = EventFunction;
}

void Stage::setWorld(Display * pl) {
	world = pl;
}

Display * Stage::findObjectByName(const char * toFind)
{
	for (std::vector<Display *>::iterator it = children.begin(); it != children.end(); ++it) {
		if ((*it)->name == toFind) {
			return *it;
		}
	}
	return NULL;
}

Stage::~Stage()
{
}
