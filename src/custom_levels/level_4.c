#include "../common.h"

void make_level_4(custom_level_data* level) {
	level->used_rooms = 16;
        level->start_room = 7;//test
        level->start_pos =  15;
        level->bg_colour = (rgb_type){220,55,255};

	// room 1
        memcpy(level->rooms[0].fg, (byte[]){ 0, 0, 9, 0, 0, 0, 0, 9, 0, 0,
                                             1, 1, 8, 1, 1, 1, 1, 8, 1, 1,
                                             3, 1, 1, 3, 1, 1, 3, 1, 1, 3}, 30);
	level->rooms[0].links.right = 2;
	level->rooms[0].links.left = 3;
	level->rooms[0].links.up = 7;

	// room 2
        memcpy(level->rooms[1].fg, (byte[]){ 0, 0, 9, 0, 0, 0, 0, 9, 0,20,
                                             1, 1, 8, 1, 1,11, 1, 8, 1,20,
                                             3, 1, 1, 3, 1, 1, 3,11, 1,20}, 30);
	level->rooms[1].links.left = 1;
	level->rooms[1].links.down = 14;
	level->rooms[1].links.up = 8;

	// room 3: climb outside
        memcpy(level->rooms[2].fg, (byte[]){ 0, 0, 0, 0, 0, 1,20, 0, 0, 0,
                                             0, 0, 0, 0, 0, 1,20, 1, 1, 1,
                                             0, 0, 0, 0, 0, 1, 3, 1, 1, 1}, 30);
	level->rooms[2].links.right = 1;
	level->rooms[2].links.up = 4;
	level->rooms[2].links.left = 5;
	level->rooms[2].links.down = 12;

	// room 4: hall roof 1
        memcpy(level->rooms[3].fg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 1, 1, 1, 1, 1}, 30);
	level->rooms[3].links.down = 3;
	level->rooms[3].links.left = 6;
	level->rooms[3].links.right = 7;
	level->rooms[3].links.up = 15;

	// room 5: tower
        memcpy(level->rooms[4].fg, (byte[]){ 0, 0, 0, 0, 0, 0, 3,20,20, 3,
                                             0, 0, 0, 0, 0, 0, 3,20,20, 3,
                                             0, 0, 0, 0, 0, 0, 3,20,20, 3}, 30);
	level->rooms[4].links.right = 3;
	level->rooms[4].links.up = 6;
	level->rooms[4].links.down = 11;
	level->rooms[4].links.left = 15;

	// room 6: tower top
        memcpy(level->rooms[5].fg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0,15, 1, 1, 1}, 30);
        memcpy(level->rooms[5].bg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, 30);
	level->rooms[5].links.right = 4;
	level->rooms[5].links.down = 5;
	level->rooms[5].links.up = 15;
	level->rooms[5].links.left = 15;
	level->doorlinks_rooms[1] = 7;
	level->doorlinks_tiles[1] = 16;

	// room 7: hall roof 2
        memcpy(level->rooms[6].fg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 1, 1, 4, 1, 1, 0,
                                             1, 1, 1,11, 3,20,20,20, 3, 1}, 30);
        memcpy(level->rooms[6].bg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0,255, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[6].links.left = 4;
	level->rooms[6].links.right = 8;
	level->rooms[6].links.down = 1;
	level->rooms[6].links.up = 15;

	// room 8: hall roof 3
        memcpy(level->rooms[7].fg, (byte[]){ 0, 0, 0, 0, 0, 9, 0, 0, 1,20,
                                             0, 0, 0, 0, 0, 8, 0, 0, 1,20,
                                            11, 1, 1, 1, 1, 3, 1, 1, 1,20}, 30);
	level->rooms[7].links.left = 7;
	level->rooms[7].links.down = 2;
	level->rooms[7].links.up = 9;

	// room 9: hall roof up
        memcpy(level->rooms[8].fg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0,15, 0, 0, 1, 1}, 30);
        memcpy(level->rooms[8].bg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 3, 0, 0, 0, 0}, 30);
	level->rooms[8].links.right = 10;
	level->rooms[8].links.down = 8;
	level->rooms[8].links.left = 15;
	level->rooms[8].links.up = 15;
	level->doorlinks_rooms[3] = 11;
	level->doorlinks_tiles[3] = 16;

	// room 10: exit
        memcpy(level->rooms[9].fg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             1, 1, 1, 1,21,16,17,30, 0, 0}, 30);
	level->rooms[9].links.left = 9;
	level->rooms[9].links.right = 15;
	level->rooms[9].links.up = 15;
	level->rooms[9].links.down = 15;

	// room 11: tower bottom
        memcpy(level->rooms[10].fg, (byte[]){ 0, 0, 0, 0, 0, 0, 3,20,20,20,
                                              0, 0, 0, 0, 0, 0, 4,31, 3, 3,
                                              0, 0, 0, 0, 0, 0,20,20,20,20}, 30);
        memcpy(level->rooms[10].bg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 2, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[10].links.up = 5;
	level->rooms[10].links.right = 12;
	level->rooms[10].links.left = 15;
	level->doorlinks_rooms[2] = 10;
	level->doorlinks_tiles[2] = 25;

	// room 12: pit below
        memcpy(level->rooms[11].fg, (byte[]){ 0, 0, 0, 0, 0,20,20,20,20,20,
                                              0, 0, 0, 0, 1, 3, 1, 1, 1, 3,
                                              0, 0, 0, 0,20,20,20,20,20,20}, 30);
	level->rooms[11].links.left = 11;
	level->rooms[11].links.right = 13;
	level->rooms[11].links.up = 3;

	// room 13: tunnel below hall 1
        memcpy(level->rooms[12].fg, (byte[]){20,20,20,20,20,20,20,20,20,20,
                                              3, 1, 1, 3,11, 1, 3, 1, 1, 3,
                                             20,20,20,20, 0,20,20,20,20,20}, 30);
	level->rooms[12].links.left = 12;
	level->rooms[12].links.right = 14;

	// room 14: tunnel below hall 2
        memcpy(level->rooms[13].fg, (byte[]){20,20,20,20,20,20, 3, 0,20,20,
                                              3, 1, 2, 3, 1, 1, 3, 1, 1,20,
                                             20,20,20,20,20,20,20,20,20,20}, 30);
	level->rooms[13].links.up = 2;
	level->rooms[13].links.left = 13;

	// room 15: sky
        memcpy(level->rooms[14].fg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[14].links.up = 15;
	level->rooms[14].links.left = 15;
	level->rooms[14].links.right = 15;
	level->rooms[14].links.down = 16;

	// room 16: ground
        memcpy(level->rooms[15].fg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 30);
	level->rooms[15].links.up = 15;
	level->rooms[15].links.left = 16;
	level->rooms[15].links.right = 16;
}
