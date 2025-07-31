#include "../common.h"

void make_level_6(custom_level_data* level) {
	level->used_rooms = 11;
        level->start_room = 1;
        level->start_pos =  25;
        level->bg_colour = (rgb_type){255,40,140};

	// room 1: cell
        memcpy(level->rooms[0].fg, (byte[]){ 3, 3, 1,15, 1, 1, 6, 1, 3, 3,
                                             4, 0, 0, 9, 0, 0, 9, 0, 0,23,
                                            20, 1,11, 8, 1, 1, 8, 1, 1,20}, 30);
        memcpy(level->rooms[0].bg, (byte[]){ 0, 0, 0, 1, 0, 0, 3, 0, 0, 0,
                                           255, 0, 0, 0, 0, 0, 0, 0, 0,255,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->doorlinks_rooms[1] = 1;
	level->doorlinks_tiles[1] = 10;
	level->doorlinks_nexts[1] = 1;
	level->doorlinks_rooms[2] = 1;
	level->doorlinks_tiles[2] = 19;
	level->doorlinks_rooms[3] = 1;
	level->doorlinks_tiles[3] = 10;
	level->doorlinks_nexts[3] = 1;
	level->doorlinks_rooms[4] = 1;
	level->doorlinks_tiles[4] = 19;
	level->rooms[0].links.down = 2;
	level->rooms[0].links.left = 5;
	level->rooms[0].links.right = 6;
	level->rooms[0].links.up = 8;


	// room 2: passage underneath
        memcpy(level->rooms[1].fg, (byte[]){ 1, 3, 1, 1, 1, 1, 1, 1, 3, 1,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[1].links.up = 1;
	level->rooms[1].links.left = 3;
	level->rooms[1].links.right = 4;

	// room 3: passage underneath left
        memcpy(level->rooms[2].fg, (byte[]){ 0, 0, 0, 0, 3, 1, 1, 1, 1, 1,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[2].links.right = 2;
	level->rooms[2].links.up = 5;

	// room 4: passage underneath right
        memcpy(level->rooms[3].fg, (byte[]){ 1, 1, 1, 1, 1, 3, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[3].links.left = 2;
	level->rooms[3].links.up = 6;

	// room 5: left climb and button
        memcpy(level->rooms[4].fg, (byte[]){ 0, 0, 0, 0, 3, 0, 8, 1, 1, 1,
                                             0, 0, 0, 0, 3, 0,20, 1,15, 1,
                                             0, 0, 0, 0, 3, 0,20,20,20,20}, 30);
        memcpy(level->rooms[4].bg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					     0, 0, 0, 0, 0, 0, 0, 0, 5, 0,
					     0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[4].links.down = 3;
	level->rooms[4].links.right = 1;
	level->rooms[4].links.up = 9;
	level->doorlinks_rooms[5] = 6;
	level->doorlinks_tiles[5] = 15;

	// room 6: right way out of cell
        memcpy(level->rooms[5].fg, (byte[]){ 1, 8, 1, 0,20, 1, 1, 0, 0, 0,
                                             1, 3, 0, 0, 0,23, 1, 1, 1, 0,
                                            20,20, 0, 0, 0,20,20,20,20, 0}, 30);
	level->rooms[5].links.down = 4;
	level->rooms[5].links.left = 1;
	level->rooms[5].links.up = 7;

	// room 7: bridge entry
        memcpy(level->rooms[6].fg, (byte[]){ 0, 1, 0, 0, 0, 0, 0, 3, 1,20,
                                             1, 3, 1, 1, 0, 0, 0, 3, 1,20,
                                             0, 9, 0,20, 1, 0, 0, 0, 0, 0}, 30);
	level->rooms[6].links.down = 6;
	level->rooms[6].links.left = 8;
	level->rooms[6].links.up = 11;

	// room 8: collapsing bridge
        memcpy(level->rooms[7].fg, (byte[]){ 0, 0, 0, 0,20,15, 3, 0, 0, 0,
                                             1, 1,11,11,11,11,11,11, 1, 1,
                                            20, 4, 0, 0, 0, 0, 0, 0,23,20}, 30);
        memcpy(level->rooms[7].bg, (byte[]){ 0, 0, 0, 0, 0, 6, 0, 0, 0, 0,
					     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					     0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[7].links.right = 7;
	level->rooms[7].links.down = 1;
	level->rooms[7].links.left = 9;
	level->rooms[7].links.up = 10;
	level->doorlinks_rooms[6] = 8;
	level->doorlinks_tiles[6] = 21;
	level->doorlinks_nexts[6] = 1;
	level->doorlinks_rooms[7] = 8;
	level->doorlinks_tiles[7] = 28;

	// room 9: exit
        memcpy(level->rooms[8].fg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 1,21,16,17,30, 1, 1, 1, 1,
                                             0, 3,31, 1,20, 0, 9, 0, 0, 0}, 30);
        memcpy(level->rooms[8].bg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					     0, 0, 8, 0, 0, 0, 0, 0, 0, 0}, 30);

	level->rooms[8].links.down = 5;
	level->rooms[8].links.right = 8;
	level->doorlinks_rooms[8] = 9;
	level->doorlinks_tiles[8] = 13;

	// room 10: above bridge
        memcpy(level->rooms[9].fg, (byte[]){ 0, 0, 0, 0,20, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0,20, 0, 1, 1, 1, 1,
                                             0, 0, 0, 0,20,11, 3, 0, 0, 0}, 30);
	level->rooms[9].links.down = 8;
	level->rooms[9].links.right = 11;

	// room 11: before above bridge
        memcpy(level->rooms[10].fg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 3, 1,20,
                                              1, 1, 1, 1, 1, 0, 0, 3, 1,20,
                                              0, 0, 0, 0, 0, 0, 0, 3, 1,20}, 30);
	level->rooms[10].links.down = 8;
	level->rooms[10].links.left = 10;

}
