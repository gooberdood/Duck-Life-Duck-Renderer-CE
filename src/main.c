//libraries
#include <ti/getcsc.h>
#include <sys/util.h>
#include <compression.h>
#include <graphx.h>
#include <keypadc.h>
#include <time.h>
#include <math.h>
#include "gfx/ducks.h"
#include "loadSprites.h"
#include "functions.h"

//frame limit
#define TARGET_FRAMERATE 60
#define TARGET_FRAME_TIME (CLOCKS_PER_SEC / TARGET_FRAMERATE)

int main(void) {
	
	if (ducks_init() == 0) {return 1;}
	initGfx(); //setup / initialization
	gfx_FillScreen(1);
	gfx_PrintStringXY("Decompressing. Please wait...",1,1);
	gfx_SwapDraw();
	decompressSprites(); //decompressing spritezzz
	
	//main loop
	do {
		clock_t frame_start = clock(); //starts frame timer
		
		getInput(); //calls getInput function to, well, get input, and do stuff with said input
		renderWindow(); //graphics rendering
		
		//waits until ~1/60th of a second (minus logic time) to render frame
		clock_t frame_time = clock() - frame_start;
		do {frame_time = clock() - frame_start;} while (frame_time < TARGET_FRAME_TIME);
		
	} while (running == true);
	
	
	//ends gfx process and frees memory of pesky lil sprites
    gfx_End();
	
	free(seeds);
	free(superseeds);
}