#include <graphx.h>
#include <math.h>
#include "drawduck.h"
#include "gfx/ducks.h"
#include "trig.h"

float headRadians;
float faceRadians;
float beakTriangle1Radians;
float beakTriangle2Radians;
float eyeRadians;
float legRadians;
float footRadians;
int headX;
int headY;
int beakTipX;
int beakTipY;
int beakTip2X;
int beakTip2Y;
int beakTriangle1X;
int beakTriangle1Y;
int beakTriangle2X;
int beakTriangle2Y;
int eyeX;
int eyeY;
int legX1;
int legY1;
int legX2;
int legY2;
int footX;
int footY;
int tempState;

float radianMult = M_PI/180;

const int flyPoints[9][6] = {
	{13, 0, 13, 0, 13, 0},
	{5, 0, 2, 4, -5, -2},
	{5, 0, 2, 2, -5, -2},
	{5, 0, -5, 0, 5, 0},
	{5, 0, 2, -2, -5, -2},
	{5, 0, 2, -4, -5, 2},
	{5, 0, 2, -2, -5, 2},
	{5, 0, -5, 0, 5, 0},
	{5, 0, 2, 2, -5, -2}
};
const int lowQualityHeadOffsets[8][2] = {
	{3, -13},
	{13, -3},
	{13, 3},
	{3, 13},
	{-3, 13},
	{-13, 3},
	{-13, -3},
	{-3, -13}
};
const int lowQualityLegOffsets[5][6] = {
	{14, 0, 19, 0, 0, -5},
	{-14, 0, -19, 0, -0, 5},
	{10, 10, 14, 14, 3, -3},
	{0, 14, 0, 19, 5, 0},
	{-10, 10, -14, 14, -3, -3}
};
const int lowQualityEyeOffsets[5][2] = {
	{0, -4},
	{3, -3},
	{4, 0},
	{-4, 0},
	{-3, -3}
};
const int lowQualityBeakOffsets[6][8] = {
	{10, -10, 10, -10, -5, 1, -1, 5},
	{15, 0, 12, 0, -5, -3, -5, 3},
	{10, 10, 10, 10 -5, -1, -1, -5},
	{-10, 10, -10, 10, 5, -1, 1, -5},
	{-15, 0, -12, 0, 5, -3, 5, 3},
	{-10, -10, -10, -10, 5, 1, 1, 5}
};

const char* qualityStrings[5] = {
	"Something messed up",
	"Ultra",
	"High",
	"Medium",
	"Low"
};


void drawDuck(int quality, int duckX, int duckY, int duckColor, int headAngle, int faceAngle, int legAngle, int footAngle, int flyFrame) {
	//ultra quality
	if (quality == 1) {
		//converts angles of body parts (measured clockwise from the northern point) to radians
		headRadians = headAngle * radianMult;
		faceRadians = faceAngle * radianMult;
		beakTriangle1Radians = (faceAngle-15) * radianMult;
		beakTriangle2Radians = (faceAngle+15) * radianMult;
		eyeRadians = (faceAngle-40) * radianMult;
		if (faceAngle > 180) {eyeRadians = (faceAngle+40) * radianMult;}
		legRadians = legAngle * radianMult;
		footRadians = footAngle * radianMult;
		
		//gets coordinates for body parts
		headX = duckX + 13 * sin(headRadians);
		headY = duckY - 13 * cos(headRadians);
		beakTipX = headX + 15 * sin(faceRadians);
		beakTipY = headY - 15 * cos(faceRadians);
		beakTip2X = headX + 13 * sin(faceRadians);
		beakTip2Y = headY - 13 * cos(faceRadians);
		beakTriangle1X = headX + 11 * sin(beakTriangle1Radians);
		beakTriangle1Y = headY - 11 * cos(beakTriangle1Radians);
		beakTriangle2X = headX + 11 * sin(beakTriangle2Radians);
		beakTriangle2Y = headY - 11 * cos(beakTriangle2Radians);
		eyeX = headX + 4 * sin(eyeRadians);
		eyeY = headY - 4 * cos(eyeRadians);
		legX1 = duckX + 13 * sin(legRadians);
		legY1 = duckY - 13 * cos(legRadians);
		legX2 = duckX + 18 * sin(legRadians);
		legY2 = duckY - 18 * cos(legRadians);
		footX = legX2 + 5 * sin(footRadians);
		footY = legY2 - 5 * cos(footRadians);
	}
	

	//low quality
	if (quality == 4) {
		//gets head location
		for(int i = 0; i < 8; i++) {
			if (headAngle < (i+1)*45) {
				headX = duckX + lowQualityHeadOffsets[i][0];
				headY = duckY + lowQualityHeadOffsets[i][1];
				break;
			}
		}
		
		//gets leg and foot locations
		if (legAngle < 100) {tempState = 0;}
		else if (legAngle >= 260) {tempState = 1;}
		else if ((legAngle >= 100) && (legAngle < 170)) {tempState = 2;}
		else if ((legAngle >= 170) && (legAngle < 190)) {tempState = 3;}
		else {tempState = 4;}
		legX1 = duckX + lowQualityLegOffsets[tempState][0];
		legY1 = duckY + lowQualityLegOffsets[tempState][1];
		legX2 = duckX + lowQualityLegOffsets[tempState][2];
		legY2 = duckY + lowQualityLegOffsets[tempState][3];
		footX = legX2 + lowQualityLegOffsets[tempState][4];
		footY = legY2 + lowQualityLegOffsets[tempState][5];
		if ((tempState == 3) && (footAngle >= 180)) {footX = legX2 - lowQualityLegOffsets[tempState][4];}
		
		//gets eye position, then beak position
		if (faceAngle < 80) {tempState = 0;}
		else if (faceAngle < 100) {tempState = 1;}
		else if (faceAngle < 180) {tempState = 2;}
		else if (faceAngle < 260) {tempState = 3;}
		else if (faceAngle < 280) {tempState = 4;}
		else {tempState = 0;}
		eyeX = headX + lowQualityEyeOffsets[tempState][0];
		eyeY = headY + lowQualityEyeOffsets[tempState][1];
		
		//gets beak position
		if (faceAngle < 80) {tempState = 0;}
		else if (faceAngle < 100) {tempState = 1;}
		else if (faceAngle < 180) {tempState = 2;}
		else if (faceAngle < 260) {tempState = 3;}
		else if (faceAngle < 280) {tempState = 4;}
		else {tempState = 5;}
		beakTipX = headX + lowQualityBeakOffsets[tempState][0];
		beakTipY = headY + lowQualityBeakOffsets[tempState][1];
		beakTip2X = headX + lowQualityBeakOffsets[tempState][2];
		beakTip2Y = headY + lowQualityBeakOffsets[tempState][3];
		beakTriangle1X = beakTipX + lowQualityBeakOffsets[tempState][4];
		beakTriangle1Y = beakTipY + lowQualityBeakOffsets[tempState][5];
		beakTriangle2X = beakTipX + lowQualityBeakOffsets[tempState][6];
		beakTriangle2Y = beakTipY + lowQualityBeakOffsets[tempState][7];
	}
	
	
	
	//draws silhouette
	gfx_SetColor(1);
	gfx_FillTriangle_NoClip(beakTipX, beakTipY, beakTriangle1X, beakTriangle1Y, beakTriangle2X, beakTriangle2Y);
	gfx_SetColor(5);
	gfx_FillTriangle_NoClip(beakTip2X, beakTip2Y, beakTriangle1X, beakTriangle1Y, beakTriangle2X, beakTriangle2Y);
	//draws body and head silhouette
	gfx_SetColor(1);
	gfx_FillCircle_NoClip(duckX, duckY, 13);
	gfx_FillCircle_NoClip(headX, headY, 11);
	//draws leg and foot
	gfx_Line_NoClip(legX1, legY1, legX2, legY2);
	gfx_Line_NoClip(legX2, legY2, footX, footY);
	//draws body
	gfx_SetColor(duckColor);
	gfx_FillCircle_NoClip(duckX, duckY, 11);
	
	//draws wings if applicable
	if (flyFrame > 0) {
		gfx_SetColor(1);
		gfx_Line_NoClip(duckX+flyPoints[flyFrame][0], duckY+flyPoints[flyFrame][1], duckX+flyPoints[flyFrame][2], duckY+flyPoints[flyFrame][3]);
		gfx_Line_NoClip(duckX+flyPoints[flyFrame][2], duckY+flyPoints[flyFrame][3], duckX+flyPoints[flyFrame][4], duckY+flyPoints[flyFrame][5]);
	}
	
	//draws head
	gfx_SetColor(duckColor);
	gfx_FillCircle_NoClip(headX, headY, 9);
	
	//draws eyes
	gfx_SetColor(1);
	gfx_FillCircle_NoClip(eyeX, eyeY, 3);
	gfx_SetColor(2);
	gfx_FillCircle_NoClip(eyeX, eyeY, 2);
	if (faceAngle <= 180) {
		gfx_SetColor(6);
		gfx_FillRectangle_NoClip(eyeX, eyeY-1, 3, 3);
		gfx_SetColor(1);
		gfx_FillRectangle_NoClip(eyeX+1, eyeY-1, 3, 3);
	}
	else {
		gfx_SetColor(6);
		gfx_FillRectangle_NoClip(eyeX-2, eyeY-1, 3, 3);
		gfx_SetColor(1);
		gfx_FillRectangle_NoClip(eyeX-2, eyeY-1, 2, 3);
	}
}