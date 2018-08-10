#pragma once
#include "Display.h"
class Instructions :
	public Display
{
public:
	Instructions();
	void draw(BITMAP * buffer);
	void Logic();
	~Instructions();
private:
	BITMAP * * pages;
	int currentPage = 0;
	int numPages;
	bool releasedA = true;
	bool releasedD = true;
};

