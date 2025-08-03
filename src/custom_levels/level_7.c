#include "../common.h"

void make_level_7(custom_level_data* level) {
	level->used_rooms = 11;
        level->start_room = 1;
        level->start_pos =  25;
        level->bg_colour = (rgb_type){255,15,50};
	level->rose_colour = (rgb_type){136,20,29};

	// room 1: base right
        memcpy(level->rooms[0].fg, (byte[]){ 1, 1, 1, 3, 1, 1, 1, 1, 3, 0,
                                             1, 1, 1, 3, 1, 1,15, 1,20, 0,
                                             1, 1, 1, 3, 1, 1, 1, 1, 3, 1}, 30);
        memcpy(level->rooms[0].bg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 2, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[0].links.left = 2;
	level->rooms[0].links.up = 3;
	level->doorlinks_rooms[2] = 3;
	level->doorlinks_tiles[2] = 23;
	// room 2: base left
        memcpy(level->rooms[1].fg, (byte[]){ 0,20, 1, 1,11, 1, 3, 1, 1, 1,
                                             0, 3, 1, 1, 1, 1, 4, 1, 1, 1,
                                             1, 3, 1, 1, 1, 1, 3, 1, 1, 1}, 30);
	level->rooms[1].links.right = 1;
	level->rooms[1].links.up = 4;


	// room 3: floor 1 right
        memcpy(level->rooms[2].fg, (byte[]){ 1, 1, 1, 3, 1, 1, 1, 1, 3, 0,
                                             1,15, 1,20, 1, 1, 1, 1, 4, 0,
                                             1, 1, 1, 4, 1, 1,15,11, 3, 0}, 30);
        memcpy(level->rooms[2].bg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 3, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, 30);
	level->rooms[2].links.left = 4;
	level->rooms[2].links.down = 1;
	level->rooms[2].links.up = 5;
	level->doorlinks_rooms[1] = 2;
	level->doorlinks_tiles[1] = 16;
	level->doorlinks_rooms[3] = 6;
	level->doorlinks_tiles[3] = 11;
	// room 4: floor 1 left
        memcpy(level->rooms[3].fg, (byte[]){ 0,20, 1, 1,15, 1, 3, 1, 1, 1,
                                             0, 3, 1, 1,15, 1,20, 1,11, 1,
                                             0, 3,11, 1, 1, 1, 4, 1, 1, 1}, 30);
        memcpy(level->rooms[3].bg, (byte[]){ 0, 0, 0, 0, 5, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 4, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[3].links.right = 3;
	level->rooms[3].links.down = 2;
	level->rooms[3].links.up= 6;
	level->doorlinks_rooms[4] = 3;
	level->doorlinks_tiles[4] = 18;
	level->doorlinks_rooms[5] = 4;
	level->doorlinks_tiles[5] = 26;

	// room 5: floor 2 right
        memcpy(level->rooms[4].fg, (byte[]){11,11,11, 3, 1, 1, 1,11, 4, 0,
                                             0, 0, 0, 9,23,11,11, 1, 3, 0,
                                             1, 1, 1, 8, 3, 1, 1, 1, 3, 0}, 30);
	level->rooms[4].links.left = 6;
	level->rooms[4].links.down = 3;
	level->rooms[4].links.up = 7;
	// room 6: floor 2 left
        memcpy(level->rooms[5].fg, (byte[]){ 0, 3, 1,15, 1, 1, 3,11,11,11,
                                             0,23, 1, 1, 1, 3, 9, 0, 0, 0,
                                             0, 3, 1, 1, 1, 3, 8, 1, 1, 1}, 30);
        memcpy(level->rooms[5].bg, (byte[]){ 0, 0, 0, 8, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[5].links.right = 5;
	level->rooms[5].links.down = 4;
	level->rooms[5].links.up = 8;
	level->doorlinks_rooms[8] = 7;
	level->doorlinks_tiles[8] = 8;

	// room 7: floor 3 right
        memcpy(level->rooms[6].fg, (byte[]){ 1, 1, 1, 3, 1, 1, 1, 1, 4, 0, // todo: this gate not connected
                                             1, 1, 1, 3, 1, 1,11, 1,20, 0,
                                             1, 1, 1,20, 1, 1, 1, 1, 3, 0}, 30);
	level->rooms[6].links.left = 8;
	level->rooms[6].links.down = 5;
	level->rooms[6].links.up = 9;
	// room 8: floor 3 left
        memcpy(level->rooms[7].fg, (byte[]){ 0, 3, 1, 1, 1, 1, 3, 1, 1, 1,
                                             0, 3, 1, 1, 1, 1,20, 1,31, 1,
                                             0, 3, 1, 1, 1, 1, 3, 1, 1, 1}, 30);
        memcpy(level->rooms[7].bg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 6, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[7].links.right = 7;
	level->rooms[7].links.down = 6;
	level->rooms[7].links.up = 10;
	level->doorlinks_rooms[6] = 10;
	level->doorlinks_tiles[6] = 13;

	// room 9: floor 4 right
        memcpy(level->rooms[8].fg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             1, 1, 1, 1, 1, 1, 1, 1, 4, 0,
                                             1, 1, 1,20, 1,15, 1, 1, 3, 0}, 30);
        memcpy(level->rooms[8].bg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 9, 0, 0, 0, 0}, 30);
	level->rooms[8].links.left = 10;
	level->rooms[8].links.down = 7;
	level->doorlinks_rooms[9] = 10;
	level->doorlinks_tiles[9] = 11;

	// room 10: floor 4 left
        memcpy(level->rooms[9].fg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0,23,21,16,17,30, 1, 1, 1, 1,
                                             0, 3, 1, 1,15, 1,20, 1, 1, 1}, 30);
        memcpy(level->rooms[9].bg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0,10, 0, 0, 0, 0, 0}, 30);
	level->rooms[9].links.right = 9;
	level->rooms[9].links.down = 8;
	level->doorlinks_rooms[10] = 9;
	level->doorlinks_tiles[10] = 18;

}
