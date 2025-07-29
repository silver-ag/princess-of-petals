#include "../common.h"

void make_level_5(custom_level_data* level) {
	level->used_rooms = 10;
        level->start_room = 1;
        level->start_pos =  25;
        level->bg_colour = (rgb_type){255,55,220};

	// room 1
        memcpy(level->rooms[0].fg, (byte[]){ 1, 3, 0, 0, 0, 0, 0, 3, 1, 1,
                                             0, 9, 0, 0, 0, 0, 0, 3, 0, 0,
                                             1, 8, 1, 1, 1, 1, 1, 3, 0, 0}, 30);

	level->rooms[0].links.left = 2;
	level->rooms[0].links.right = 3;
	level->rooms[0].links.up = 4;

	// room 2: aiko
        memcpy(level->rooms[1].fg, (byte[]){ 1, 0, 0, 0, 0, 1, 0, 0, 1, 1,
                                            20,11, 1,15, 1,20, 0, 0, 9, 0,
                                            20, 1, 3, 1, 1, 3, 1, 1, 8, 1}, 30);
        memcpy(level->rooms[1].bg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[1].links.right = 1;
	level->rooms[1].guard_tile = 21;
	level->doorlinks_rooms[1] = 4;
	level->doorlinks_tiles[1] = 22;

	// room 3: yuuko
        memcpy(level->rooms[2].fg, (byte[]){ 1,11, 1, 0, 0, 0, 0, 0, 0, 1,
                                             0, 0, 0, 1, 1, 1, 1, 1, 1,20,
                                             0, 0, 0, 3, 1, 1,15, 1, 1,20}, 30);
        memcpy(level->rooms[2].bg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 2, 0, 0, 0}, 30);
	level->rooms[2].links.left = 1;
	level->rooms[2].guard_tile =18;
	level->doorlinks_rooms[2] = 4;
	level->doorlinks_tiles[2] = 24;

	// room 4: gate
        memcpy(level->rooms[3].fg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
                                             0, 1, 4, 1, 4, 1, 1,20, 0, 0}, 30);
	level->rooms[3].links.down = 1;
}
