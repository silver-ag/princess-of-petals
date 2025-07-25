#include "../common.h"

void make_level_1(custom_level_data* level) {
	level->used_rooms = 9;
        level->start_room = 1;
        level->start_pos =  20;

	// room 1: starting room
	memcpy(level->rooms[0].fg, (byte[]){ 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
						       9, 0, 0, 9, 0, 0, 9, 0, 0, 9,
						       8, 1, 1, 8, 1, 1, 8, 1, 1, 8}, 30);
	memcpy(level->rooms[0].bg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						       0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[0].links.left = 2;
	level->rooms[0].links.right = 3;
	level->rooms[0].links.up = 5;

	// room 2: garden
	memcpy(level->rooms[1].fg, (byte[]){  1, 0, 0, 0, 0, 0, 0, 3, 0, 0,
						       20, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						       20, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 30);
	level->rooms[1].links.right = 1;
	level->rooms[1].links.left = 7;
	level->rooms[1].links.up = 4;

	// room 3: climbable gate
	memcpy(level->rooms[2].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
						        1, 0, 0, 0, 0, 0, 0, 0, 0,20,
						        3, 1, 1, 1, 1, 1, 1, 1, 1,20}, 30);
	level->rooms[2].links.left = 1;
	level->rooms[2].links.up = 7;

	// room 4: sky entrance
	memcpy(level->rooms[3].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
						        0, 0, 0, 0, 0, 0, 0, 3, 0, 0}, 30);
	level->rooms[3].links.down = 2;
	level->rooms[3].links.right = 5;
	level->rooms[3].links.left = 7;
	level->rooms[3].links.up = 7;


	// room 5: sky passage
	memcpy(level->rooms[4].fg, (byte[]){ 20, 1, 1, 1, 1, 0, 1, 1, 1,20,
						        3, 1, 1, 1,11,11, 1, 1, 1,20,
						        0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	memcpy(level->rooms[4].bg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[4].links.left = 4;
	level->rooms[4].links.down = 1;
	level->rooms[4].links.up = 6;

	// room 6: exit
	memcpy(level->rooms[5].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 0, 1,21,16,17,30, 1, 0, 0,
						        1, 0, 3, 1,31, 1, 1, 3, 0, 1}, 30);
	memcpy(level->rooms[5].bg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, 30);
	level->doorlinks_rooms[1] = 6;
	level->doorlinks_tiles[1] = 14;
	level->doorlinks_nexts[1] = 0;
	level->rooms[5].links.down = 5;
	level->rooms[5].links.up = 7;
	level->rooms[5].links.left = 9;
	level->rooms[5].links.right = 7;

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

	// room 9: sky by button
	memcpy(level->rooms[6].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[8].links.down = 4;
	level->rooms[8].links.left = 7;
	level->rooms[8].links.up = 7;
	level->rooms[8].links.right = 6;
}
