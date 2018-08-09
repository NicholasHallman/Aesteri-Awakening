#include "TitleScene.h"
#include "eNgiNe.h"


TitleScene::TitleScene()
{
}

void TitleScene::Load()
{
	i = new Intro("Assets/Intro");
	i->x = 0;
	i->y = 0;
	stage->addChild(i);
}

void TitleScene::Unload()
{
	stage->removeChild(i);
	i->~Intro();
}


TitleScene::~TitleScene()
{
}
