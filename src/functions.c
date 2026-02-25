#include <keypadc.h>
#include <compression.h>
#include <graphx.h>
#include <math.h>
#include "gfx/ducks.h"
#include "functions.h"
#include "loadSprites.h"
#include "drawduck.h"

int running = true;
int debugMode = true;
int headRotation = 10;
int faceRotation = 90;
int legRotation = 180;
int footRotation = 90;
int duckX = 160;
int duckY = 120;
int flyFrame = 0;
int gameQuality = 4;
int frameTimer = 0;
int framerateTimer = 0;
int showCoords = false;
int stressTest = false;

//initialize gfx / set up
void initGfx(void) {
    gfx_Begin();
	gfx_SetDrawBuffer();
	//sets palette and transparent color
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
	gfx_SetTransparentColor(0);
	gfx_SetTextTransparentColor(0);
	gfx_SetTextBGColor(3);
	gfx_SetTextFGColor(1);
	gfx_SetTextConfig(gfx_text_clip);
}


void getInput(void) {
	//scans the keypad then checks inputs
	kb_Scan();
	
	if (debugMode) {
		if (kb_Data[6] & kb_Clear) {running = false;}
		
		if (kb_Data[7] & kb_Down) {headRotation--;}
		if (kb_Data[7] & kb_Up) {headRotation++;}
		if (kb_Data[7] & kb_Left) {faceRotation = faceRotation - 1;}
		if (kb_Data[7] & kb_Right) {faceRotation = faceRotation + 1;}
		if (kb_Data[6] & kb_Sub) {legRotation = legRotation - 1;}
		if (kb_Data[6] & kb_Add) {legRotation = legRotation + 1;}
		if (kb_Data[6] & kb_Div) {footRotation = footRotation - 1;}
		if (kb_Data[6] & kb_Mul) {footRotation = footRotation + 1;}
		if (kb_Data[3] & kb_4) {duckX--;}
		if (kb_Data[5] & kb_6) {duckX++;}
		if (kb_Data[4] & kb_8) {duckY--;}
		if (kb_Data[4] & kb_2) {duckY++;}
		if (kb_Data[2] & kb_Math) {gameQuality = 1;}
		if (kb_Data[2] & kb_Recip) {gameQuality = 4;}
		
		if (kb_Data[1] & kb_2nd) {
			headRotation = 10;
			faceRotation = 90;
			legRotation = 180;
			footRotation = 90;
			duckX = 160;
			duckY = 120;
		}
		if (kb_Data[2] & kb_Alpha) {showCoords = true;}
		else {showCoords = false;}
		if (kb_Data[1] & kb_Mode) {stressTest = true;}
		else {stressTest = false;}
		
		if (kb_Data[6] & kb_Enter) {
			flyFrame += 1;
		}
		else {
			flyFrame = 0;
		}
		
		if (flyFrame > 8) {flyFrame = 1;}
		if (faceRotation < 0) {faceRotation = 359;}
		if (faceRotation > 359) {faceRotation = 0;}
		if (headRotation < 0) {headRotation = 359;}
		if (headRotation > 359) {headRotation = 0;}
		if (legRotation < 0) {legRotation = 359;}
		if (legRotation > 359) {legRotation = 0;}
		if (footRotation < 0) {footRotation = 359;}
		if (footRotation > 359) {footRotation = 0;}
		if (duckX < 10) {duckX = 10;}
		if (duckX > 310) {duckX = 310;}
		if (duckY < 20) {duckY = 20;}
		if (duckY > 220) {duckY = 220;}
	}
}

//renders graphics to screen
void renderWindow(void) {
	if (debugMode) {
		gfx_FillScreen(3);
		drawDuck(gameQuality, duckX, duckY, 4, headRotation, faceRotation, legRotation, footRotation, flyFrame);
		if (stressTest) {
			drawDuck(gameQuality, 30, 60, 7, headRotation, faceRotation, legRotation, footRotation, flyFrame);
			drawDuck(gameQuality, 60, 60, 8, headRotation, faceRotation, legRotation, footRotation, flyFrame);
			drawDuck(gameQuality, 90, 60, 9, headRotation, faceRotation, legRotation, footRotation, flyFrame);
		}
		
		if (showCoords) {
			gfx_SetTextXY(1,1);
			gfx_PrintString("Head rotation: ");
			gfx_PrintInt(headRotation, 3);
			gfx_SetTextXY(1,11);
			gfx_PrintString("Face rotation: ");
			gfx_PrintInt(faceRotation, 3);
			gfx_SetTextXY(1,21);
			gfx_PrintString("Leg rotation: ");
			gfx_PrintInt(legRotation, 3);
			gfx_SetTextXY(1,31);
			gfx_PrintString("Foot rotation: ");
			gfx_PrintInt(footRotation, 3);
			gfx_SetTextXY(1,41);
			gfx_PrintString("Duck X position: ");
			gfx_PrintInt(duckX, 3);
			gfx_SetTextXY(1,51);
			gfx_PrintString("Duck Y position: ");
			gfx_PrintInt(duckY, 3);
			gfx_SetTextXY(1,61);
			gfx_PrintString("Flying: ");
			gfx_PrintInt((kb_Data[6] & kb_Enter), 1);
			gfx_SetTextXY(1,71);
			gfx_PrintString("Fly frame: ");
			gfx_PrintInt(flyFrame, 1);
			gfx_SetTextXY(1,81);
			gfx_PrintString("Quality: ");
			gfx_PrintString(qualityStrings[gameQuality]);
		}
		
		
		frameTimer += 1;
		if (frameTimer == 30) {
			frameTimer = 1;
			framerateTimer += 1;
		}
		gfx_SetTextXY(1,220);
		gfx_PrintInt(frameTimer, 2);
		gfx_PrintString(" | ");
		gfx_PrintInt(framerateTimer, 1);
		
		gfx_SwapDraw();
	}
}