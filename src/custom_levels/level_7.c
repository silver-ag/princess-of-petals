#include "../common.h"

void make_level_7(custom_level_data* level) {
	level->used_rooms = 21;
        level->start_room = 10;
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
	level->rooms[0].links.right = 16;
	level->rooms[0].links.up = 3;
	level->doorlinks_rooms[2] = 3;
	level->doorlinks_tiles[2] = 23;
	// room 2: base left
        memcpy(level->rooms[1].fg, (byte[]){ 0,20, 1, 1,11, 1, 3, 1, 1, 1,
                                             0, 3, 1, 1, 1, 1, 4, 1, 1, 1,
                                             1, 3, 1, 1, 1, 1, 3, 1, 1, 1}, 30);
	level->rooms[1].links.right = 1;
	level->rooms[1].links.up = 4;
	level->rooms[1].links.left = 11;


	// room 3: floor 1 right
        memcpy(level->rooms[2].fg, (byte[]){ 1, 1, 1, 3, 1, 1, 1, 1, 3, 0,
                                             1,15, 1,20, 1, 1, 1, 1, 4, 0,
                                             1, 1, 1, 4, 1, 1,15,11, 3, 0}, 30);
        memcpy(level->rooms[2].bg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 3, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, 30);
	level->rooms[2].links.left = 4;
	level->rooms[2].links.right = 17;
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
	level->rooms[3].links.left = 12;
	level->doorlinks_rooms[4] = 3;
	level->doorlinks_tiles[4] = 18;
	level->doorlinks_rooms[5] = 4;
	level->doorlinks_tiles[5] = 26;

	// room 5: floor 2 right
        memcpy(level->rooms[4].fg, (byte[]){11,11,11, 3, 1, 1, 1,11,20, 0,
                                             0, 0, 0, 9,23,11,11, 1, 3, 0,
                                             1, 1, 1, 8, 3, 1, 1, 1, 3, 0}, 30);
	level->rooms[4].links.left = 6;
	level->rooms[4].links.right = 18;
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
	level->rooms[5].links.left = 13;
	level->doorlinks_rooms[8] = 7;
	level->doorlinks_tiles[8] = 8;

	// room 7: floor 3 right
        memcpy(level->rooms[6].fg, (byte[]){ 1, 1, 1, 3, 1, 1, 1, 1, 4, 0, // todo: this gate not connected
                                             1, 1, 1, 3, 1, 1,11, 1,20, 0,
                                             1, 1, 1,20, 1, 1, 1, 1, 3, 0}, 30);
	level->rooms[6].links.left = 8;
	level->rooms[6].links.right = 19;
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
	level->rooms[7].links.left = 14;
	level->doorlinks_rooms[6] = 10;
	level->doorlinks_tiles[6] = 13;

	// room 9: floor 4 right
        memcpy(level->rooms[8].fg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0,12, 0,
                                             1, 1, 1, 1, 1, 1, 1, 1, 4, 0,
                                             1, 1, 1,20, 1,15, 1, 1, 3, 0}, 30);
        memcpy(level->rooms[8].bg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 7, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 9, 0, 0, 0, 0}, 30);
	level->rooms[8].links.left = 10;
	level->rooms[8].links.right = 20;
	level->rooms[8].links.down = 7;
	level->rooms[8].links.up = 21;
	level->doorlinks_rooms[9] = 10;
	level->doorlinks_tiles[9] = 11;

	// room 10: floor 4 left
        memcpy(level->rooms[9].fg, (byte[]){ 0, 7, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0,23,21,16,17,30, 1, 1, 1, 1,
                                             0, 3, 1, 1,15, 1,20, 1, 1, 1}, 30);
        memcpy(level->rooms[9].bg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                             0, 0, 0, 0,10, 0, 0, 0, 0, 0}, 30);
	level->rooms[9].links.right = 9;
	level->rooms[9].links.down = 8;
	level->rooms[9].links.left = 15;
	level->rooms[9].links.up = 21;
	level->doorlinks_rooms[10] = 9;
	level->doorlinks_tiles[10] = 18;

	// room 11: left sky ground floor
        memcpy(level->rooms[10].fg, (byte[]){ 1, 0, 0, 0,13, 0, 0, 0, 0, 0,
                                             20, 0, 0, 0,13, 0, 0, 0, 0, 0,
                                             20, 1, 1, 1, 8, 1, 1, 1, 1, 1}, 30);
	level->rooms[10].links.right = 2;
	level->rooms[10].links.up = 12;
	level->rooms[10].links.left = 21;
	// room 12: left sky floor 1
        memcpy(level->rooms[11].fg, (byte[]){ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 9, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0,13, 0, 0, 0, 0, 0}, 30);
	level->rooms[11].links.right = 4;
	level->rooms[11].links.up = 13;
	level->rooms[11].links.down = 11;
	level->rooms[11].links.left = 21;
	// room 13: left sky floor 2
        memcpy(level->rooms[12].fg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[12].links.right = 6;
	level->rooms[12].links.up = 14;
	level->rooms[12].links.down = 12;
	level->rooms[12].links.left = 21;
	// room 14: left sky floor 3
        memcpy(level->rooms[13].fg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[13].links.right = 8;
	level->rooms[13].links.up = 15;
	level->rooms[13].links.down = 13;
	level->rooms[13].links.left = 21;
	// room 15: left sky floor 4
        memcpy(level->rooms[14].fg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[14].links.right = 10;
	level->rooms[14].links.down = 14;
	level->rooms[14].links.left = 21;

	// room 16: right sky ground floor
        memcpy(level->rooms[15].fg, (byte[]){ 0, 0, 0, 0,13, 0, 0, 0, 0, 1,
                                              0, 0, 0, 0,13, 0, 0, 0, 0,20,
                                              1, 1, 1, 1, 8, 1, 1, 1, 1,20}, 30);
	level->rooms[15].links.right = 21;
	level->rooms[15].links.up = 17;
	level->rooms[15].links.left = 1;
	// room 17: right sky floor 1
        memcpy(level->rooms[16].fg, (byte[]){ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 9, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0,13, 0, 0, 0, 0, 0}, 30);
	level->rooms[16].links.right = 21;
	level->rooms[16].links.up = 18;
	level->rooms[16].links.down = 16;
	level->rooms[16].links.left = 3;
	// room 18: right sky floor 2
        memcpy(level->rooms[17].fg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[17].links.right = 21;
	level->rooms[17].links.up = 19;
	level->rooms[17].links.down = 17;
	level->rooms[17].links.left = 5;
	// room 19: right sky floor 3
        memcpy(level->rooms[18].fg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[18].links.right = 21;
	level->rooms[18].links.up = 20;
	level->rooms[18].links.down = 18;
	level->rooms[18].links.left = 7;
	// room 20: left sky floor 4
        memcpy(level->rooms[19].fg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[19].links.right = 21;
	level->rooms[19].links.down = 19;
	level->rooms[19].links.left = 9;

	// room 21: empty sky
        memcpy(level->rooms[20].fg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	level->rooms[20].links.left = 21;
	level->rooms[20].links.down = 21;
}
