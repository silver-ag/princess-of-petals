#include "../common.h"

void make_level_5(custom_level_data* level) {
	level->used_rooms = 1;
        level->start_room = 1;
        level->start_pos =  15;
        level->bg_colour = (rgb_type){255,55,220};

	// room 1
        memcpy(level->rooms[0].fg, (byte[]){ 0, 0, 9, 0, 0, 0, 0, 9, 0, 0,
                                             1, 1, 8, 1, 1, 1, 1, 8, 1, 1,
                                             3, 1, 1, 3, 1, 1, 3, 1, 1, 3}, 30);
}
