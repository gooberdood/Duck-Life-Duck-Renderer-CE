#ifndef ducks_appvar_include_file
#define ducks_appvar_include_file

#ifdef __cplusplus
extern "C" {
#endif

#define sizeof_global_palette 28
#define global_palette (ducks_appvar[0])
#define sprites_palette_offset 0
#define seeds_width 20
#define seeds_height 16
#define ducks_sprites_seeds_compressed_index 1
#define seeds_compressed ducks_appvar[1]
#define superseeds_width 20
#define superseeds_height 16
#define ducks_sprites_superseeds_compressed_index 2
#define superseeds_compressed ducks_appvar[2]
#define ducks_entries_num 3
extern unsigned char *ducks_appvar[3];
unsigned char ducks_init(void);

#ifdef __cplusplus
}
#endif

#endif
