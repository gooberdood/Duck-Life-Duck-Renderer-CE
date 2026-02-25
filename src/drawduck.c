#include <graphx.h>
#include <math.h>
#include "drawduck.h"
#include "gfx/ducks.h"

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
float radianMult = M_PI/180;

int flyPoints[9][6] = {
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


void duckSetup(void) {

}	


void drawDuck(int duckX, int duckY, int duckColor, int headAngle, int faceAngle, int legAngle, int footAngle, int flyFrame) {
	
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
	gfx_Line_NoClip(duckX+flyPoints[flyFrame][0], duckY+flyPoints[flyFrame][1], duckX+flyPoints[flyFrame][2], duckY+flyPoints[flyFrame][3]);
	gfx_Line_NoClip(duckX+flyPoints[flyFrame][2], duckY+flyPoints[flyFrame][3], duckX+flyPoints[flyFrame][4], duckY+flyPoints[flyFrame][5]);
	
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
	
	gfx_SetTextXY(1,100);
	gfx_PrintInt((int)(headRadians*10000),6);
}