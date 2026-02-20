#include <compression.h>
#include <graphx.h>
#include "gfx/ducks.h"

gfx_sprite_t *seeds;
gfx_sprite_t *superseeds;

//decompresses sprites
void decompressSprites(void) {
	seeds = gfx_MallocSprite(seeds_width, seeds_height);
	zx0_Decompress(seeds, seeds_compressed);
	
	superseeds = gfx_MallocSprite(superseeds_width, superseeds_height);
	zx0_Decompress(superseeds, superseeds_compressed);
}