#pragma once

#include "Stage.h"
#include "TileMap.h"
#include "SpriteSheet.h"
#include <allegro.h>


/* -------------------------------
 * ENgiNe is an allegro extension
 *
 * ENgiNe works as an event based wrapper supplying 
 * an event loop for programmers to use.
 * includes an extendable display and spritesheet class
 *
 * Created by Nicholas Hallman.
 * -------------------------------*/
extern Stage * stage;
extern Stage * eNgiNe_init(int width, int height, int fps);
