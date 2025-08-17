#include "../common.h"

void make_level_3(custom_level_data* level) {
	level->used_rooms = 13;
        level->start_room = 1;
        level->start_pos =  24;
	level->bg_colour = (rgb_type){150,70,255};
	level->rose_colour = (rgb_type){216,130,57};

	// room 1: starting room
        memcpy(level->rooms[0].fg, (byte[]){20, 1, 0, 0, 0, 0, 0, 0, 1,20,
                                            20,20, 2, 1, 0, 0, 1, 1,20,20,
                                             0,20,11, 3, 1, 1, 3, 1,20, 0}, 30);
	level->rooms[0].links.down = 2;
	level->rooms[0].links.up = 4;
	level->rooms[0].links.left = 8;

	// room 2: shrine entrance
        memcpy(level->rooms[1].fg, (byte[]){ 0,20, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0,20, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0,20, 1, 1, 1, 1, 1, 1, 1, 1}, 30);
	level->rooms[1].links.up = 1;
	level->rooms[1].links.right = 3;
	level->rooms[1].links.left = 8;

	// room 3: shrine
        memcpy(level->rooms[2].fg, (byte[]){20,20,20,20,20,20,20,20,20,20,
                                            20, 0, 0, 0, 9, 9, 0, 0, 0,20,
                                             1, 1, 1, 1, 8, 8, 1, 1, 1,20}, 30);
        memcpy(level->rooms[2].bg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0,11, 0, 0, 0, 0,12, 0, 0}, 30);
	level->rooms[2].links.left = 2;

	// room 4: tower A
        memcpy(level->rooms[3].fg, (byte[]){20, 0, 1, 1, 1,20, 1, 1, 0,20,
                                            20, 0, 3, 6, 1,23, 6, 3, 0,20,
                                            20, 0, 3,15, 2, 3, 1, 3, 0,20}, 30);
        memcpy(level->rooms[3].bg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 3, 0,255,4, 0, 0, 0,
                                             0, 0, 0, 2, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[3].links.down = 1;
	level->rooms[3].links.up = 5;
	level->doorlinks_rooms[2] = 4;
	level->doorlinks_tiles[2] = 15;
	level->doorlinks_rooms[3] = 4;
	level->doorlinks_tiles[3] = 15;
	level->doorlinks_rooms[4] = 4;
	level->doorlinks_tiles[4] = 15;

	// room 5: tower B
        memcpy(level->rooms[4].fg, (byte[]){20, 0, 1, 1, 1, 1, 1, 1, 1, 1,
                                            20, 0, 3, 1, 1, 3, 0, 1, 2, 1,
                                            20, 1, 3, 1, 0,20, 0, 1,20,20}, 30);
	level->rooms[4].links.down = 4;
	level->rooms[4].links.right = 6;
	level->rooms[4].links.up = 11;

	// room 6: tower C
        memcpy(level->rooms[5].fg, (byte[]){ 1, 1, 1, 2, 1, 1, 2, 1, 1, 1,
                                             1, 1, 1, 1,11,11,11, 1, 1, 1,
                                             0, 0, 9, 0, 0, 0, 0, 9, 0, 0}, 30);
	level->rooms[5].links.left = 5;
	level->rooms[5].links.right = 7;
	level->rooms[5].links.up = 8;
	level->rooms[5].links.down = 13;

	// room 7: exit
        memcpy(level->rooms[6].fg, (byte[]){ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
                                             1, 3, 1,21,16,17,30, 2,31, 1,
                                             0, 0, 9, 0, 0, 0, 0, 9, 0, 0}, 30);
        memcpy(level->rooms[6].bg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[6].links.up = 8;
	level->rooms[6].links.left = 6;
	level->rooms[6].links.down = 8;
	level->rooms[6].links.right = 10;
	level->doorlinks_rooms[1] = 7;
	level->doorlinks_tiles[1] = 14;

	// room 8: sky
        memcpy(level->rooms[7].fg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[7].links.left = 8;
	level->rooms[7].links.right = 8;
	level->rooms[7].links.up = 8;
	level->rooms[7].links.down = 9;

	// room 9: floor
        memcpy(level->rooms[8].fg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 30);
	level->rooms[8].links.left = 9;
	level->rooms[8].links.right = 9;
	level->rooms[8].links.up = 8;

	// room 10: promenade
        memcpy(level->rooms[9].fg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
                                             0, 9, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[9].links.left = 7;
	level->rooms[9].links.right = 8;
	level->rooms[9].links.up = 8;
	level->rooms[9].links.down = 12;

	// room 11: above tower
        memcpy(level->rooms[10].fg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[10].links.down = 5;

	// room 12: below promenade
        memcpy(level->rooms[11].fg, (byte[]){ 0,13, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0,13, 0, 0, 0, 0, 0, 0, 0, 0,
                                              1, 8, 1, 1, 1, 1, 1, 1, 1, 1}, 30);
	level->rooms[11].links.up = 10;
	level->rooms[11].links.left = 12;
	level->rooms[11].links.right = 12;

	// room 13: below C
        memcpy(level->rooms[12].fg, (byte[]){ 0, 0,13, 0, 0, 0, 0,13, 0, 0,
                                              0, 0,13, 0, 0, 0, 0,13, 0, 0,
                                              1, 1, 8, 1, 1, 1, 1, 8, 1, 1}, 30);
	level->rooms[12].links.up = 6;
	level->rooms[12].links.left = 13;
	level->rooms[12].links.right = 13;

}
