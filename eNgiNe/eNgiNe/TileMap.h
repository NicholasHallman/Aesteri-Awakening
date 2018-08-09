#pragma once
#include "Display.h"
class TileMap :
	public Display
{
public:
	TileMap(const char *, const int mW, const int mH, const char * n, int follow);
	void SetTileSprites(SpriteSheet * ss);
	int GetTile(int x, int y);
	int SetTile(int x, int y, int tile);
	void draw(BITMAP * buffer);
	void initDraw();
	double dx = 0;
	double dy = 0;
	void testDraw();
	void wholeScrolling();
	void Logic();
	void Start();
	void setSolidTiles(int * solid, int numSolids);
	bool isSolid(int x, int y);
	bool hide = false;
	bool warp = false;
	int * tileSize;
	int * getMapSize();
	int followType; // 0 do not, 1 x follow, 2 y follow, 3 both
	~TileMap();
protected:
	void loadMap(const char *);
	int width;
	int height;
	int mapWidth;
	int mapHeight;
	int prevx = 0;
	int prevy = 0;
	bool wholeScroll = false;
	BITMAP * wholeMap;
	SpriteSheet * sprites;
	BITMAP * currentScreen;
	BITMAP ** buffers;
	int ** tiles;
	
	int * solids;
	int numSolids;
	Display * player;
	
};

