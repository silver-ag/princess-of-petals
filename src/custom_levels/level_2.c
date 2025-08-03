#include "../common.h"

void make_level_2(custom_level_data* level) {
	level->used_rooms = 12;
	level->start_room = 1;
	level->start_pos =  24;
	level->bg_colour = (rgb_type){100,80,255};
	level->rose_colour = (rgb_type){11,70,150};
	// room 1
	memcpy(level->rooms[0].fg, (byte[]){  0, 0, 0, 3, 0, 0, 3, 0, 0, 0,
					      0, 0, 0, 3, 0, 0, 3, 0, 0, 0,
					      1, 1, 1, 3, 1, 1, 3, 1, 1, 1}, 30);
	memcpy(level->rooms[0].bg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					      0, 0, 3, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[0].links.up = 2;
	level->rooms[0].links.left = 10;
	level->rooms[0].links.right = 11;

	// room 2
	memcpy(level->rooms[1].fg, (byte[]){  4, 0, 0, 3, 1, 1, 3, 0, 0,23,
					      4, 0, 0, 3, 1,11, 3, 0, 0,23,
					      4, 0, 0, 3, 1, 1, 3, 0, 0,23}, 30);
	memcpy(level->rooms[1].bg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					    255, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					      0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);

	level->rooms[1].links.down = 1;
	level->rooms[1].links.up = 3;
	level->rooms[1].links.left = 4;
	level->rooms[1].links.right = 5;

	level->doorlinks_rooms[1] = 2;
	level->doorlinks_tiles[1] = 0;
	level->doorlinks_nexts[1] = 1;
	level->doorlinks_rooms[2] = 2;
	level->doorlinks_tiles[2] = 9;
	level->doorlinks_rooms[3] = 2;
	level->doorlinks_tiles[3] = 20;
	level->doorlinks_rooms[4] = 2;
	level->doorlinks_tiles[4] = 29;
	level->doorlinks_rooms[5] = 3;
	level->doorlinks_tiles[5] = 10;
	level->doorlinks_rooms[6] = 3;
	level->doorlinks_tiles[6] = 20;
	level->doorlinks_rooms[7] = 3;
	level->doorlinks_tiles[7] = 14;


	// room 3
	memcpy(level->rooms[2].fg, (byte[]){ 12, 0, 0, 0, 0, 0, 0, 0, 0, 1,
					      4, 0,11,21,16,17,30,11, 0,20,
					      4, 0, 0, 3, 1, 1, 3, 0, 0,20}, 30);
	level->rooms[2].links.down = 2;
	level->rooms[2].links.left = 9;
	level->rooms[2].links.up = 7;
	level->rooms[2].links.right = 7;

	// room 4
	memcpy(level->rooms[3].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0,20,15, 1,
					      0, 0, 0, 0, 0, 0, 0,20,15, 1,
					      0, 0, 0, 0, 0, 0, 0,20,15, 1}, 30);
	memcpy(level->rooms[3].bg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 3, 0,
					      0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
					      0, 0, 0, 0, 0, 0, 0, 0, 5, 0}, 30);
	level->rooms[3].links.right = 2;
	level->rooms[3].links.left = 7;
	level->rooms[3].links.down = 7;
	level->rooms[3].links.up = 6;

	// room 5
	memcpy(level->rooms[4].fg, (byte[]){  1,15,20, 0, 0, 0, 0, 0, 0, 0,
					     11,31,20, 0, 0, 0, 0, 0, 0, 0,
					      1,15,20, 0, 0, 0, 0, 0, 0, 0}, 30);
	memcpy(level->rooms[4].bg, (byte[]){  0, 4, 0, 0, 0, 0, 0, 0, 0, 0,
					      0, 7, 0, 0, 0, 0, 0, 0, 0, 0,
					      0, 6, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[4].links.left = 2;
	level->rooms[4].links.right = 7;
	level->rooms[4].links.down = 7;
	level->rooms[4].links.up = 12;

	// room 6
	memcpy(level->rooms[5].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					      0, 0, 0, 0, 0, 0,20, 0, 1, 4,
					      0, 0, 0, 0, 0, 0,20, 1, 1, 4}, 30);
	level->rooms[5].links.right = 3;
	level->rooms[5].links.left = 7;
	level->rooms[5].links.up = 7;
	level->rooms[5].links.down = 4;

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

	// room 9: passage up to exit
	memcpy(level->rooms[8].fg, (byte[]){  0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
					      0, 0, 0, 0, 0, 0,20, 0, 1, 1,
					      0, 0, 0, 0, 0, 0,20, 1, 1, 1}, 30);
	level->rooms[8].links.up = 7;
	level->rooms[8].links.left = 7;
	level->rooms[8].links.down = 7;
	level->rooms[8].links.right = 3;

	// room 10: bottom left
	memcpy(level->rooms[9].fg, (byte[]){  1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					     20, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					     20, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 30);
	level->rooms[9].links.up = 7;
	level->rooms[9].links.left = 7;
	level->rooms[9].links.right = 1;
	// room 11: bottom right
	memcpy(level->rooms[10].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
					       0, 0, 0, 0, 0, 0, 0, 0, 0,20,
					       1, 1, 1, 1, 1, 1, 1, 1, 1,20}, 30);
	level->rooms[10].links.up = 7;
	level->rooms[10].links.left = 1;
	level->rooms[10].links.right = 7;

	// room 12: roof for top right
	memcpy(level->rooms[11].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					       1, 1, 1, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[11].links.down = 5;
}
