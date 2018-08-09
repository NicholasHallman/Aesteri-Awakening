#include "TileMap.h"
#include <iostream>
#include <string>
#include "eNgiNe.h"
#pragma warning(disable:4996)

TileMap::TileMap(const char * filePath, const int mW, const int mH, const char * n, int follow)
{
	
	tiles = new int*[mW];
	for (int i = 0; i < mW; i++) {
		tiles[i] = new int[mH];
	}
	width = SCREEN_W;
	height = SCREEN_H;
	mapWidth = mW;
	mapHeight = mH;
	loadMap(filePath);
	currentScreen = create_bitmap(width, height);
	name = n;
	followType = follow;
}

void TileMap::loadMap(const char * filePath) {
	char buffer[200];
	FILE * fp;
	fp = fopen(filePath, "r");
	if (fp == NULL) {
		return;
	}
	int w = 0;
	int h = 0;
	int i = 0;
	while (fgets(buffer, 200, fp)) {
		char * token = strtok(buffer,",");
		i = 0;
		while (token) {
			if (token[0] != '\n') {
				tiles[w][h] = atoi(token);
				w++;
				if (w >= mapWidth) {
					w = 0;
					h++;
				}
				i++;
			}
			token = strtok(NULL, " ");
		}
	}
	return;
}

void TileMap::SetTileSprites(SpriteSheet * ss) {
	sprites = ss;
	tileSize = sprites->getSpriteSize();
	buffers = new BITMAP *[4];
	buffers[0] = create_bitmap(width, tileSize[1]);
	buffers[1] = create_bitmap(tileSize[0],height);
	buffers[2] = create_bitmap(width, tileSize[1]);
	buffers[3] = create_bitmap(tileSize[0], height);

	int wholeW = mapWidth * tileSize[0];
	int wholeH = mapHeight * tileSize[0];
	wholeMap = create_bitmap(wholeW, wholeH);

}



int TileMap::GetTile(int x, int y)
{
	return(tiles[x][y]);
}

int TileMap::SetTile(int x, int y, int type)
{
	tiles[x][y] = type;
	return 1;
}

void TileMap::draw(BITMAP * buffer)
{
	if (!hide) {
		if (wholeScroll && !warp) {
			blit(wholeMap, buffer, x - (SCREEN_W / 2) + dx, y - (SCREEN_H / 2) + dy, 0, 0, SCREEN_W, SCREEN_H);
		}
		else if (wholeScroll && warp) {
			BITMAP * buffer2 = create_bitmap(SCREEN_W, SCREEN_H);
			for (double iy = 0; iy < SCREEN_H; iy++) {
				double ry = (pow((iy) - (SCREEN_H / 2),4) / -50000000) + 64 * 3.3;
				double f = ry;
				if (iy > SCREEN_H / 2 + 64 * 3.5) f = (ry - 64 * 12) * -1;
				else if (iy > SCREEN_H /2 - 64 * 3.5) f = iy;
				
				int ypos = (y) - (SCREEN_H / 2) + dy + f ;
				if (ypos < wholeMap->h && ypos > 0) {
					blit(wholeMap, buffer2, x - (SCREEN_W / 2) + dx, ypos, 0, iy, SCREEN_W, 1);
				}
			}
			blit(buffer2, buffer, 0, 0, 0, 0, SCREEN_W,SCREEN_H);
			destroy_bitmap(buffer2);
		}
		else {
			if (prevx != x || prevy != y) {
				if (prevx != x) {
					int diffx = x - prevx;
					if (diffx < 0) { // buffer left side
						int ulcx = floor((x - (SCREEN_W / 2)) / tileSize[0]);
						int ulcy = floor((y - (SCREEN_H / 2)) / tileSize[0]);
						for (int i = 0; i < SCREEN_H / tileSize[0]; i++) {
							int tx = ulcx;
							int ty = (ulcy + (1 * i)) - 2;
							if (tx >= 0 && ty >= 0 && tx < mapWidth && ty < mapHeight) {
								blit(sprites->getFrame(tiles[ty][tx] - 1), buffers[3], 0, 0, 0, tileSize[0] * i, tileSize[0], tileSize[0]);
							}
						}

						// shift bitmap over to the right
						BITMAP * temp;
						temp = create_bitmap(SCREEN_W, SCREEN_H);
						blit(currentScreen, temp, -1, 0, 0, 0, SCREEN_W, SCREEN_H);
						clear_bitmap(currentScreen);
						blit(temp, currentScreen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
						destroy_bitmap(temp);
						int relX = x - (floor(x / tileSize[0]) * tileSize[0]);
						int relY = y - (floor(y / tileSize[0]) * tileSize[0]);
						blit(buffers[3], currentScreen, tileSize[0] - (31 - relX) - 1, 0, 0, 0, 1, SCREEN_H);
					}

					if (diffx > 0) { //Buffer in right side
						int urcx = floor((x + (SCREEN_W / 2)) / tileSize[0]);
						int urcy = floor((y - (SCREEN_H / 2)) / tileSize[0]);
						for (int i = 0; i < SCREEN_H / tileSize[0]; i++) {
							int tx = urcx;
							int ty = (urcy + (1 * i)) - 2;
							if (tx >= 0 && ty >= 0 && tx < mapWidth && ty < mapHeight) {
								blit(sprites->getFrame(tiles[ty][tx] - 1), buffers[1], 0, 0, 0, tileSize[0] * i, tileSize[0], tileSize[0]);
							}
						}

						// shift bitmap over to the left
						BITMAP * temp;
						temp = create_bitmap(SCREEN_W, SCREEN_H);
						blit(currentScreen, temp, 1, 0, 0, 0, SCREEN_W, SCREEN_H);
						clear_bitmap(currentScreen);
						blit(temp, currentScreen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
						destroy_bitmap(temp);
						int relX = x - (floor(x / tileSize[0]) * tileSize[0]);
						int relY = y - (floor(y / tileSize[0]) * tileSize[0]);
						blit(buffers[1], currentScreen, tileSize[0] - (31 - relX) - 1, 0, SCREEN_W - 1, 0, SCREEN_W, SCREEN_H);
					}
				}
				if (prevy != y) {
					int diffy = y - prevy;
					if (diffy < 0) { // buffer up
						int ulcx = floor((x - (SCREEN_W / 2)) / tileSize[0]);
						int ulcy = floor((y - (SCREEN_H / 2)) / tileSize[0]);
						for (int i = 0; i < SCREEN_W / tileSize[0]; i++) {
							int tx = (ulcx + (1 * i));
							int ty = (ulcy - 1) - 2;
							if (tx >= 0 && ty >= 0 && tx < mapWidth && ty < mapHeight) {
								blit(sprites->getFrame(tiles[ty][tx] - 1), buffers[0], 0, 0, tileSize[0] * i, 0, tileSize[0], tileSize[0]);
							}
						}

						// shift bitmap over to the bottom
						BITMAP * temp;
						temp = create_bitmap(SCREEN_W, SCREEN_H);
						blit(currentScreen, temp, 0, -1, 0, 0, SCREEN_W, SCREEN_H);
						clear_bitmap(currentScreen);
						blit(temp, currentScreen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
						destroy_bitmap(temp);
						int relX = x - (floor(x / tileSize[0]) * tileSize[0]);
						int relY = y - (floor(y / tileSize[0]) * tileSize[0]);
						blit(buffers[0], currentScreen, 0, relY, 0, 0, SCREEN_W, 1);
					}
					if (diffy > 0) { // buffer down
						int llcx = floor((x - (SCREEN_W / 2)) / tileSize[0]);
						int llcy = floor((y + (SCREEN_H / 2)) / tileSize[0]);
						for (int i = 0; i < SCREEN_W / tileSize[0]; i++) {
							int tx = (llcx + (1 * i));
							int ty = (llcy - 1) - 1;
							if (tx >= 0 && ty >= 0 && tx < mapWidth && ty < mapHeight) {
								blit(sprites->getFrame(tiles[ty][tx] - 1), buffers[2], 0, 0, tileSize[0] * i, 0, tileSize[0], tileSize[0]);
							}
						}

						// shift bitmap over to the bottom
						BITMAP * temp;
						temp = create_bitmap(SCREEN_W, SCREEN_H);
						blit(currentScreen, temp, 0, 1, 0, 0, SCREEN_W, SCREEN_H);
						clear_bitmap(currentScreen);
						blit(temp, currentScreen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
						destroy_bitmap(temp);
						int relX = x - (floor(x / tileSize[0]) * tileSize[0]);
						int relY = y - (floor(y / tileSize[0]) * tileSize[0]);
						blit(buffers[2], currentScreen, 0, relY, 0, SCREEN_H - 1, SCREEN_W, 1);
					}
				}
				prevx = x;
				prevy = y;
			}
			blit(currentScreen, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		}
	}
}

void TileMap::initDraw()
{
	int tileSize = sprites->getSpriteSize()[0];
	int ulx = (x - (SCREEN_W / 2)) / tileSize;
	int uly = (y - (SCREEN_W / 2)) / tileSize;
	for (int i = 0; i < SCREEN_W / tileSize; i++) {
		for (int j = 0; j < SCREEN_H / tileSize; j++) {
			int reli = i + ulx; 
			int relj = j + uly;
			if (reli > 0 && reli < mapWidth && relj > 0 && relj < mapHeight) {
				BITMAP * tile = sprites->getFrame(tiles[reli][relj] - 1);
				blit(tile, currentScreen, 0, 0, i * tileSize, j * tileSize, tileSize, tileSize);
			}
		}
	}
}

void TileMap::testDraw() {
	blit(currentScreen, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}

void TileMap::wholeScrolling()
{
	wholeScroll = true;
	int wholeW = mapWidth * sprites->getFrame(0)->w;
	int wholeH = mapHeight * sprites->getFrame(0)->h;
	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			blit(sprites->getFrame(tiles[x][y] - 1), wholeMap, 0, 0, x * sprites->getFrame(0)->w, y * sprites->getFrame(0)->w, wholeW, wholeH);
		}
	}
	return;
}

void TileMap::setSolidTiles(int * solid, int numS)
{
	solids = solid;
	numSolids = numS;

}

bool TileMap::isSolid(int checkx, int checky)
{
	checkx = round((checkx + 16) / sprites->getFrame(0)->w);
	checky = round((checky + 48) / sprites->getFrame(0)->w);
	for (int i = 0; i < numSolids; i++) {
		if ((tiles[checkx][checky] - 1) == solids[i]) {
			return true;
		}
	}
	return false;
}

void TileMap::Logic() {
	switch (followType) {
	case 1:
		x = player->x;
		break;
	case 2:
		y = player->y;
		break;
	case 3:
		x = player->x;
		y = player->y;
	}
}

void TileMap::Start() {
	player = stage->findObjectByName("Player");
	x = player->x;
	y = player->y;
}


int * TileMap::getMapSize()
{
	int * values = new int[2]{mapWidth, mapHeight};
	return values;
}

TileMap::~TileMap()
{
	destroy_bitmap(wholeMap);
}
