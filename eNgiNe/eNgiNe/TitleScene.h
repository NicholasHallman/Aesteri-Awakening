#pragma once
#include "Scene.h"
#include "Intro.h"
class TitleScene :
	public Scene
{
public:
	TitleScene();
	void Load();
	void Unload();
	~TitleScene();
private:
	Intro * i;
};

