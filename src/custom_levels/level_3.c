#include "../common.h"

void make_level_3(custom_level_data* level) {
	level->used_rooms = 9;
        level->start_room = 1;
        level->start_pos =  24;
	// room 1: starting room
        memcpy(level->rooms[0].fg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 1, 2, 1, 1, 1, 1, 2, 1, 0}, 30);
        memcpy(level->rooms[0].bg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
}
