#include "Instructions.h"



Instructions::Instructions()
{
	pages = new BITMAP*[6];
	numPages = 6;
	currentPage = 0;
	for (int i = 0; i < numPages; i++) {
		const char * toSay = "Assets/Instructions/%d.tga";
		char buffer[40];
		sprintf_s(buffer, 40, toSay, i + 1);
		pages[i] = load_bitmap(buffer, NULL);
	}
}

void Instructions::draw(BITMAP * buffer) {
	if (!hide) {
		if (currentPage == 0) {
			stretch_blit(pages[currentPage], buffer, 0, 0, pages[currentPage]->w, pages[currentPage]->h,
				683, 0, pages[currentPage]->w * 2, pages[currentPage]->h * 2);
		}
		else {
			stretch_blit(pages[currentPage - 1], buffer, 0, 0, pages[currentPage - 1]->w, pages[currentPage - 1]->h,
				1, 0, pages[currentPage - 1]->w * 2, pages[currentPage- 1]->h * 2);

			if (currentPage < numPages) {
				stretch_blit(pages[currentPage], buffer, 0, 0, pages[currentPage]->w, pages[currentPage]->h,
					683, 0, pages[currentPage]->w * 2, pages[currentPage]->h * 2);
			}
		}
		
	}
}

void Instructions::Logic() {
	if (!hide) {
		if (key[KEY_A] && releasedA) {
			currentPage-=2;
			releasedA = false;
		}
		if (key[KEY_D] && releasedD) {
			currentPage+=2;
			releasedD = false;
		}
		if (currentPage < 0) currentPage = 0;
		if(currentPage > numPages) currentPage = numPages;

		if (!key[KEY_A] && !releasedA) releasedA = true;
		if (!key[KEY_D] && !releasedD) releasedD = true;
	}
}


Instructions::~Instructions()
{
}
