#include <graphx.h>
#include <math.h>
#include "gfx/ducks.h"

void drawDuck(int duckX, int duckY, int duckColor, int headAngle, int faceAngle, int legAngle, int footAngle, int flyFrame) {
	
	//converts angles of body parts (measured clockwise from the northern point) to radians
	float headRadians = headAngle * (M_PI/180);
	float faceRadians = faceAngle * (M_PI/180);
	float beakTriangle1Radians = (faceAngle-15) * (M_PI/180);
	float beakTriangle2Radians = (faceAngle+15) * (M_PI/180);
	float eyeRadians = (faceAngle-40) * (M_PI/180);
	if (faceAngle > 180) {eyeRadians = (faceAngle+40) * (M_PI/180);}
	float legRadians = legAngle * (M_PI/180);
	float footRadians = footAngle * (M_PI/180);
	
	//gets coordinates for body parts
	int headX = duckX + 13 * sin(headRadians);
	int headY = duckY - 13 * cos(headRadians);
	int beakTipX = headX + 15 * sin(faceRadians);
	int beakTipY = headY - 15 * cos(faceRadians);
	int beakTip2X = headX + 13 * sin(faceRadians);
	int beakTip2Y = headY - 13 * cos(faceRadians);
	int beakTriangle1X = headX + 11 * sin(beakTriangle1Radians);
	int beakTriangle1Y = headY - 11 * cos(beakTriangle1Radians);
	int beakTriangle2X = headX + 11 * sin(beakTriangle2Radians);
	int beakTriangle2Y = headY - 11 * cos(beakTriangle2Radians);
	int eyeX = headX + 4 * sin(eyeRadians);
	int eyeY = headY - 4 * cos(eyeRadians);
	int legX1 = duckX + 13 * sin(legRadians);
	int legY1 = duckY - 13 * cos(legRadians);
	int legX2 = duckX + 18 * sin(legRadians);
	int legY2 = duckY - 18 * cos(legRadians);
	int footX = legX2 + 5 * sin(footRadians);
	int footY = legY2 - 5 * cos(footRadians);
	
	//draws beak
	gfx_SetColor(1);
	gfx_FillTriangle(beakTipX, beakTipY, beakTriangle1X, beakTriangle1Y, beakTriangle2X, beakTriangle2Y);
	gfx_SetColor(5);
	gfx_FillTriangle(beakTip2X, beakTip2Y, beakTriangle1X, beakTriangle1Y, beakTriangle2X, beakTriangle2Y);
	//draws body and head silhouette
	gfx_SetColor(1);
	gfx_FillCircle(duckX, duckY, 13);
	gfx_FillCircle(headX, headY, 11);
	//draws leg and foot
	gfx_Line(legX1, legY1, legX2, legY2);
	gfx_Line(legX2, legY2, footX, footY);
	//draws body and head
	gfx_SetColor(duckColor);
	gfx_FillCircle(duckX, duckY, 11);
	gfx_FillCircle(headX, headY, 9);
	
	//draws eyes
	gfx_SetColor(1);
	gfx_FillCircle(eyeX, eyeY, 3);
	gfx_SetColor(2);
	gfx_FillCircle(eyeX, eyeY, 2);
	if (faceAngle <= 180) {
		gfx_SetColor(6);
		gfx_FillRectangle(eyeX, eyeY-1, 3, 3);
		gfx_SetColor(1);
		gfx_FillRectangle(eyeX+1, eyeY-1, 3, 3);
	}
	else {
		gfx_SetColor(6);
		gfx_FillRectangle(eyeX-2, eyeY-1, 3, 3);
		gfx_SetColor(1);
		gfx_FillRectangle(eyeX-2, eyeY-1, 2, 3);
	}
	
	//draws wings if applicable
	if (flyFrame == 1) {
		gfx_Line(duckX+5, duckY, duckX+2, duckY+4);
		gfx_Line(duckX+2, duckY+4, duckX-5, duckY-2);
	}
	if (flyFrame == 2) {
		gfx_Line(duckX+5, duckY, duckX+2, duckY+2);
		gfx_Line(duckX+2, duckY+2, duckX-5, duckY-2);
	}
	if (flyFrame == 3) {
		gfx_Line(duckX+5, duckY, duckX-5, duckY);
	}
	if (flyFrame == 4) {
		gfx_Line(duckX+5, duckY, duckX+2, duckY-2);
		gfx_Line(duckX+2, duckY-2, duckX-5, duckY+2);
	}
	if (flyFrame == 5) {
		gfx_Line(duckX+5, duckY, duckX+2, duckY-4);
		gfx_Line(duckX+2, duckY-4, duckX-5, duckY+2);
	}
	if (flyFrame == 6) {
		gfx_Line(duckX+5, duckY, duckX+2, duckY-2);
		gfx_Line(duckX+2, duckY-2, duckX-5, duckY+2);
	}
	if (flyFrame == 7) {
		gfx_Line(duckX+5, duckY, duckX-5, duckY);
	}
	if (flyFrame == 8) {
		gfx_Line(duckX+5, duckY, duckX+2, duckY+2);
		gfx_Line(duckX+2, duckY+2, duckX-5, duckY-2);
	}
}