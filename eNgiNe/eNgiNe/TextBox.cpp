#include "TextBox.h"
#pragma warning(disable:4996)

TextBox::TextBox(SpriteSheet * sprites, const char * n)
{
	frames = sprites;
	currentFrame = frames->getFrame(0);
	pastTime = clock();
	name = n;
}
void TextBox::setText(const char ** set)
{
	text = set;
}

void TextBox::draw(BITMAP * buffer, int camX, int camY)
{
	set_alpha_blender();
	clock_t presentTime = clock();
	if (!hide) {
		if (fps == 0 || presentTime - pastTime > fps) {
			if (play && frameSequence != NULL) {
				if (frameSequence[currentIndex] == -1) currentIndex = 0;
				currentFrame = frames->getFrame(frameSequence[currentIndex]);
				currentIndex++;
				if (moveSequence != NULL && moveSequence[currentIndex].x != -1 && moveSequence[currentIndex].y != -1) {
					x = moveSequence[currentIndex].x;
					y = moveSequence[currentIndex].y;
				}
			}
			else if (play && frameSequence == NULL) {
				BITMAP * temp = frames->getFrame(currentIndex);
				if (temp != NULL) {
					currentFrame = temp;
				}
				else {
					currentIndex = 0;
				}
			}
			pastTime = clock();
		}
		draw_trans_sprite(buffer, currentFrame, x - (camX - SCREEN_W / 2), y - (camY - SCREEN_H / 2));
		if (text != NULL) {
			for (int i = 0; i <= currSection; i++) {
				if (text[i] != NULL) {
					if (currWidth < text_length(font,text[i]) && i == currSection) currWidth+=8;
					else if(i == currSection){
						currSection++;
						currWidth = 0;
					}
					if(i != currSection) textout(buffer, font, text[i], x - (camX - SCREEN_W / 2) + 120, y - (camY - SCREEN_H / 2) + 50 + (25 * i), makecol(255, 255, 255));
					else {
						BITMAP * temp = create_bitmap(text_length(font, text[i]), 20);
						textout(temp, font, text[i], 0, 0, makecol(255, 255, 255));
						blit(temp, buffer, 0, 0, x - (camX - SCREEN_W / 2) + 120, y - (camY - SCREEN_H / 2) + 50 + (25 * i), currWidth, temp->h);
						destroy_bitmap(temp);
					}
				}
				else {
					break;
				}
				
			}
		}
		for (int i = 0; i < children.size(); i++) {
			children.at(i)->draw(buffer, x - camX, y - camY);
		}
	}
}

bool TextBox::cycleText()
{
	if (text != NULL) {
		int j = 0;
		int t = 4;
		const char * temp;
		for (int i = 0; i < 4; i++) {
			if (*text[i] == NULL) return false;
		}
		while (*text[t] != NULL) {
			text[j] = text[t];
			j++; t++;
		}
	}
}

TextBox::~TextBox()
{
}

