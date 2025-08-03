#include "../common.h"

void make_level_6_duel(custom_level_data* level) {
	level->used_rooms = 9;
	level->start_room = 1;
	level->start_pos =  20;
	level->start_dir =  dir_FF_left;
	level->bg_colour = (rgb_type){255,30,100};
	level->rose_colour = (rgb_type){90,61,109};
	// room 1: stairs base
	memcpy(level->rooms[0].fg, (byte[]){  0, 0, 0, 0, 1, 3, 0, 0, 0,20,
					      0, 0, 0, 1, 3, 0, 0, 0, 0,20,
					      1, 1, 1, 3, 1, 1, 1, 1, 1,20}, 30);
	level->rooms[0].links.left = 4;
	level->rooms[0].links.right = 7;
	level->rooms[0].links.up = 2;

	// room 2: stairs top
	memcpy(level->rooms[1].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					      0, 0, 0, 0, 0, 0, 1,31, 4, 1,
					      0, 0, 0, 0, 0, 1, 3, 0, 0,20}, 30);
	memcpy(level->rooms[1].bg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					      0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
					      0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->doorlinks_rooms[1] = 2;
	level->doorlinks_tiles[1] = 18;
	level->doorlinks_timers[1] = 0;
	level->doorlinks_nexts[1] = 0;
	level->rooms[1].links.left = 7;
	level->rooms[1].links.right = 3;
	level->rooms[1].links.down = 1;
	level->rooms[1].links.up = 7;

	// room 3: arena
	memcpy(level->rooms[2].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					      1, 1, 1, 1, 1, 1, 1, 1, 4, 1,
					     20,20,20,20,20,20,20,20,20,20}, 30);
	level->doorlinks_rooms[2] = 3;
	level->doorlinks_tiles[2] = 18;
	level->doorlinks_timers[2] = 0;
	level->doorlinks_nexts[2] = 0;
	level->rooms[2].links.left = 2;
	level->rooms[2].links.right = 5;
	level->rooms[2].links.up = 7;
	level->rooms[2].links.down = 7;
	level->rooms[2].guard_tile = 16;


	// room 4: pre-entry
	// just for the gate visible from at the edge of room 1
	memcpy(level->rooms[3].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
					      0, 0, 0, 0, 0, 0, 0, 0, 0,20,
					      0, 0, 0, 0, 0, 0, 0, 0, 0, 4}, 30);
	memcpy(level->rooms[3].bg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					      0, 0, 0, 0, 0, 0, 0, 0, 0,255}, 30);
	level->doorlinks_rooms[3] = 4;
	level->doorlinks_tiles[3] = 29;
	level->rooms[6].links.right = 1;

	// room 5: post-entry
	// win immediately on entry
	memcpy(level->rooms[4].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0,20,
					      1, 1, 1, 1, 1, 1, 1, 1, 1,20,
					      0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[6].links.left = 3;
	level->rooms[6].links.right = 7;
	level->rooms[6].links.up = 7;
	level->rooms[6].links.down = 7;


	// room 7: sky
	// for putting next to rooms that shouldn't have walls displayed on that edge
	memcpy(level->rooms[6].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					      0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[6].links.down = 8;
	level->rooms[6].links.left = 7;
	level->rooms[6].links.up = 7;
	level->rooms[6].links.right = 7;

	// room 8: floor
	// for falling onto from room 7
	memcpy(level->rooms[7].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					      1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 30);
	level->rooms[7].links.up = 7;
	level->rooms[7].links.right = 8;
	level->rooms[7].links.left = 8;
}
