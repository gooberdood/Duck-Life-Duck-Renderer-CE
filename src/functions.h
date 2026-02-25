#include <graphx.h>
#include <math.h>
#include "gfx/ducks.h"
#include "loadSprites.h"
#ifndef GET_INPUT_H
#define GET_INPUT_H

extern int running;
extern int debugMode;
extern int headRotation;
extern int faceRotation;
extern int footRotation;
extern int ankleRotation;
extern int duckX;
extern int duckY;
extern int flyFrame;
extern int headTurned;
extern int gameQuality;
extern int frameTimer;
extern int framerateTimer;
extern int showCoords;
extern int stressTest;

void getInput(void);
void renderWindow(void);
void initGfx(void);
void timerStuff(void);

#endif