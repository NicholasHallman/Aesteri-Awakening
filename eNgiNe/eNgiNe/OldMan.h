#pragma once
#include "Display.h"
#define HELLO_THERE 0
#define WELCOME_BACK 1
#define YOURE_BACK 2
#define MANY_DANGERS 3
class OldMan :
	public Display
{
public:
	OldMan(SpriteSheet * sprites, const char * n);
	void Logic();
	const char ** getConversation(int which);
	int times = 0;
	bool walk = false;
	int * go = new int[8]{424,61,424,57,446,57,405,19};
	int whichWalk = 0;
	bool animating[4]{false,false,false,false};
	~OldMan();
protected:
	const char ** conversations = new const char*[15] {
		"Ohohoho! Hello there youth. Welcome to my home! Or",
		"atleast what's left of it... Any who, you've probably",
		"seen all those black monolith around yes? Well if you",
		"could get rid of all of those on these fair islands",
		"I'll let you in on a little secret. Go on then!",
		"Only %d more to go!",
		"Welcome back! You still haven't gotten rid of all",
		"the monolith! still %d left!",
		"You're back! Thank you for helping me! I guess I'll",
		"return the favor huh? Meet me on the north island.",
		"I'll repair the bridge so you can get there.",
		"Many dangers await you on the coast of the Aesterian",
		"continent. This sword should protect you. Theres a",
		" boat on the beach anytime you're ready to go. ",
		"Good luck kid!"
	};
	
};

