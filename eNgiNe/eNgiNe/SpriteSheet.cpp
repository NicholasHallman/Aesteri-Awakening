#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(const char * filePath, int w, int h)
{
	BITMAP * source = load_bitmap(filePath, NULL);
	//let's say I have a 128 x 128 sprite sheet with 32 x 32 sprites.
	// the total number of sprites here is 128/32 * 128/32 = 16 frames
	totalFrames = (source->w / w) * (source->h / h);
	sprites = new BITMAP*[totalFrames]();
	int subx = 0;
	int suby = 0;
	for (int i = 0; i < totalFrames; i++) {
		sprites[i] = create_sub_bitmap(source, subx, suby, w, h);
		subx += w;
		if (subx >= source->w) {
			subx = 0;
			suby += h;
		}
	}
}

BITMAP* SpriteSheet::getFrame(int index) {
	if (index < totalFrames && index >= 0) return sprites[index];
	return NULL;
}

int * SpriteSheet::getSpriteSize()
{
	int * sizes = new int[2]{ sprites[0]->w, sprites[0]->h };
	return sizes;
}

SpriteSheet::~SpriteSheet()
{
}
