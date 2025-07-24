#include "common.h"

// it's honestly easier to construct the level_type structs directly than to use a level editor
// plus it means we can store extra stuff like background colour directly in our level data

#define NUM_LEVELS 3

typedef struct room_type {
	byte fg[30];
	byte bg[30];
	link_type links;
	byte guard_tile;
	// more guard info to come once we know how we're handling guards
} room_type;

typedef struct custom_level_data {
	room_type rooms[24];
	byte doorlinks_rooms[256];  // five bits, 0-32
	byte doorlinks_tiles[256];  // five bits, 0-32
	byte doorlinks_timers[256]; // five bits, 0-32
	byte doorlinks_nexts[256];  // one bit, 0-1
	byte used_rooms;
	byte start_room;
	byte start_pos;
	byte start_dir;
	rgb_type bg_colour;
} custom_level_data;

custom_level_data custom_levels[NUM_LEVELS];

void initialise_custom_levels() {
	// set some defaults
	for (int level = 0; level < NUM_LEVELS; level++) {
		custom_levels[level].start_room = 1; // 1-indexed
		custom_levels[level].bg_colour = (rgb_type){100,100,255};
		for (int room = 0; room < 24; room++) {
			custom_levels[level].rooms[room].guard_tile = -1; // no guard
		}
	}

	// LEVEL 1
	custom_levels[0].used_rooms = 9;
	custom_levels[0].start_room = 1;
	custom_levels[0].start_pos =  20;
	// room 1: starting room
	memcpy(custom_levels[0].rooms[0].fg, (byte[]){ 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
						       9, 0, 0, 9, 0, 0, 9, 0, 0, 9,
						       8, 1, 1, 8, 1, 1, 8, 1, 1, 8}, 30);
	memcpy(custom_levels[0].rooms[0].bg, (byte[]){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						       0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	custom_levels[0].rooms[0].links.left = 2;
	custom_levels[0].rooms[0].links.right = 3;
	custom_levels[0].rooms[0].links.up = 5;

	// room 2: garden
	memcpy(custom_levels[0].rooms[1].fg, (byte[]){  1, 0, 0, 0, 0, 0, 0, 3, 0, 0,
						       20, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						       20, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 30);
	custom_levels[0].rooms[1].links.right = 1;
	custom_levels[0].rooms[1].links.left = 7;
	custom_levels[0].rooms[1].links.up = 4;

	// room 3: climbable gate
	memcpy(custom_levels[0].rooms[2].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
						        1, 0, 0, 0, 0, 0, 0, 0, 0,20,
						        3, 1, 1, 1, 1, 1, 1, 1, 1,20}, 30);
	custom_levels[0].rooms[2].links.left = 1;
	custom_levels[0].rooms[2].links.up = 7;

	// room 4: sky entrance
	memcpy(custom_levels[0].rooms[3].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
						        0, 0, 0, 0, 0, 0, 0, 3, 0, 0}, 30);
	custom_levels[0].rooms[3].links.down = 2;
	custom_levels[0].rooms[3].links.right = 5;
	custom_levels[0].rooms[3].links.left = 7;
	custom_levels[0].rooms[3].links.up = 7;


	// room 5: sky passage
	memcpy(custom_levels[0].rooms[4].fg, (byte[]){ 20, 1, 1, 1, 1, 0, 1, 1, 1,20,
						        3, 1, 1, 1,11,11, 1, 1, 1,20,
						        0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	memcpy(custom_levels[0].rooms[4].bg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	custom_levels[0].rooms[4].links.left = 4;
	custom_levels[0].rooms[4].links.down = 1;
	custom_levels[0].rooms[4].links.up = 6;

	// room 6: exit
	memcpy(custom_levels[0].rooms[5].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 0, 1,21,16,17,30, 1, 0, 0,
						        1, 0, 3, 1,31, 1, 1, 3, 0, 1}, 30);
	memcpy(custom_levels[0].rooms[5].bg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, 30);
	custom_levels[0].doorlinks_rooms[1] = 6;
	custom_levels[0].doorlinks_tiles[1] = 14;
	custom_levels[0].doorlinks_timers[1] = 20;
	custom_levels[0].doorlinks_nexts[1] = 0;
	custom_levels[0].rooms[5].links.down = 5;
	custom_levels[0].rooms[5].links.up = 7;
	custom_levels[0].rooms[5].links.left = 9;
	custom_levels[0].rooms[5].links.right = 7;

	// room 7: sky
	// for putting next to rooms that shouldn't have walls displayed on that edge
	memcpy(custom_levels[0].rooms[6].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	custom_levels[0].rooms[6].links.down = 8;
	custom_levels[0].rooms[6].links.left = 7;
	custom_levels[0].rooms[6].links.up = 7;
	custom_levels[0].rooms[6].links.right = 7;

	// room 8: floor
	// for falling onto from room 7
	memcpy(custom_levels[0].rooms[7].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 30);
	custom_levels[0].rooms[7].links.up = 7;
	custom_levels[0].rooms[7].links.right = 8;
	custom_levels[0].rooms[7].links.left = 8;

	// room 9: sky by button
	memcpy(custom_levels[0].rooms[6].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	custom_levels[0].rooms[8].links.down = 4;
	custom_levels[0].rooms[8].links.left = 7;
	custom_levels[0].rooms[8].links.up = 7;
	custom_levels[0].rooms[8].links.right = 6;


	// LEVEL 1: DUEL 1
	custom_levels[1].used_rooms = 9;
	custom_levels[1].start_room = 1;
	custom_levels[1].start_pos =  20;
	custom_levels[1].start_dir =  0;
	// room 1: stairs base
	memcpy(custom_levels[1].rooms[0].fg, (byte[]){  0, 0, 0, 0, 1, 3, 0, 0, 0,20,
						        0, 0, 0, 1, 3, 0, 0, 0, 0,20,
						        1, 1, 1, 3, 1, 1, 1, 1, 1,20}, 30);
	custom_levels[1].rooms[0].links.left = 4;
	custom_levels[1].rooms[0].links.right = 7;
	custom_levels[1].rooms[0].links.up = 2;

	// room 2: stairs top
	memcpy(custom_levels[1].rooms[1].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 0, 0, 0, 0, 0, 1,31, 4, 1,
						        0, 0, 0, 0, 0, 1, 3, 0, 0,20}, 30);
	memcpy(custom_levels[1].rooms[1].bg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
						        0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	custom_levels[1].doorlinks_rooms[1] = 2;
	custom_levels[1].doorlinks_tiles[1] = 18;
	custom_levels[1].doorlinks_timers[1] = 0;
	custom_levels[1].doorlinks_nexts[1] = 0;
	custom_levels[1].rooms[1].links.left = 7;
	custom_levels[1].rooms[1].links.right = 3;
	custom_levels[1].rooms[1].links.down = 1;
	custom_levels[1].rooms[1].links.up = 7;

	// room 3: arena
	memcpy(custom_levels[1].rooms[2].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        1, 1, 1, 1, 1, 1, 1, 1, 4, 1,
						       20,20,20,20,20,20,20,20,20,20}, 30);
	custom_levels[1].doorlinks_rooms[2] = 3;
	custom_levels[1].doorlinks_tiles[2] = 18;
	custom_levels[1].doorlinks_timers[2] = 0;
	custom_levels[1].doorlinks_nexts[2] = 0;
	custom_levels[1].rooms[2].links.left = 2;
	custom_levels[1].rooms[2].links.right = 5;
	custom_levels[1].rooms[2].links.up = 7;
	custom_levels[1].rooms[2].links.down = 7;
	custom_levels[1].rooms[2].guard_tile = 16;


	// room 4: pre-entry
	// just for the gate visible from at the edge of room 1
	memcpy(custom_levels[1].rooms[3].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
						        0, 0, 0, 0, 0, 0, 0, 0, 0,20,
						        0, 0, 0, 0, 0, 0, 0, 0, 0, 4}, 30);
	custom_levels[1].rooms[6].links.right = 1;

	// room 5: post-entry
	// win immediately on entry
	memcpy(custom_levels[1].rooms[4].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0,20,
						        1, 1, 1, 1, 1, 1, 1, 1, 1,20,
						        0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	custom_levels[1].rooms[6].links.left = 3;
	custom_levels[1].rooms[6].links.right = 7;
	custom_levels[1].rooms[6].links.up = 7;
	custom_levels[1].rooms[6].links.down = 7;


	// room 7: sky
	// for putting next to rooms that shouldn't have walls displayed on that edge
	memcpy(custom_levels[1].rooms[6].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	custom_levels[1].rooms[6].links.down = 8;
	custom_levels[1].rooms[6].links.left = 7;
	custom_levels[1].rooms[6].links.up = 7;
	custom_levels[1].rooms[6].links.right = 7;

	// room 8: floor
	// for falling onto from room 7
	memcpy(custom_levels[1].rooms[7].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 30);
	custom_levels[1].rooms[7].links.up = 7;
	custom_levels[1].rooms[7].links.right = 8;
	custom_levels[1].rooms[7].links.left = 8;


	// LEVEL 2
	custom_levels[2].used_rooms = 9;
	custom_levels[2].start_room = 2;
	custom_levels[2].start_pos =  23;
	custom_levels[2].bg_colour = (rgb_type){20,20,255};
	// room 1
	memcpy(custom_levels[2].rooms[0].fg, (byte[]){  0, 0, 0, 3, 0, 0, 3, 0, 0, 0,
						        0, 0, 0, 3, 0, 0, 3, 0, 0, 0,
						        1, 1, 1, 3, 1, 1, 3, 1, 1, 1}, 30);
	custom_levels[2].rooms[0].links.up = 2;

	// room 2
	memcpy(custom_levels[2].rooms[1].fg, (byte[]){  4, 0, 0,23, 0, 0, 3, 0, 0,23,
						        4, 0, 0, 3, 0, 0, 3, 0, 0,23,
						        4, 0, 0, 3, 0, 0, 3, 0, 0,23}, 30);
	memcpy(custom_levels[2].rooms[1].bg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						      255, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);

	custom_levels[2].rooms[1].links.down = 1;
	custom_levels[2].rooms[1].links.up = 3;
	custom_levels[2].rooms[1].links.left = 4;
	custom_levels[2].rooms[1].links.right = 5;

	custom_levels[2].doorlinks_rooms[1] = 2;
	custom_levels[2].doorlinks_tiles[1] = 0;
	custom_levels[2].doorlinks_timers[1] = 0;
	custom_levels[2].doorlinks_nexts[1] = 1;
	custom_levels[2].doorlinks_rooms[2] = 2;
	custom_levels[2].doorlinks_tiles[2] = 9;
	custom_levels[2].doorlinks_nexts[2] = 0;


	// room 3
	memcpy(custom_levels[2].rooms[2].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        4, 0,11,21,16,17,30,11, 0, 0,
						        4, 0, 0, 3, 0, 0, 3, 0, 0, 0}, 30);
	custom_levels[2].rooms[2].links.down = 2;

	// room 4
	memcpy(custom_levels[2].rooms[3].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0,20,31, 1,
						        0, 0, 0, 0, 0, 0, 0,20,31, 1,
						        0, 0, 0, 0, 0, 0, 0,20,31, 1}, 30);
	memcpy(custom_levels[2].rooms[3].bg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 3, 0,
						        0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
						        0, 0, 0, 0, 0, 0, 0, 0, 4, 0}, 30);
	custom_levels[2].rooms[3].links.right = 2;

	// room 5
	memcpy(custom_levels[2].rooms[4].fg, (byte[]){ 11,31,20, 0, 0, 0, 0, 0, 0, 0,
						        1,31,20, 0, 0, 0, 0, 0, 0, 0,
						        1, 1,20, 0, 0, 0, 0, 0, 0, 0}, 30);
	memcpy(custom_levels[2].rooms[4].bg, (byte[]){  0, 5, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 6, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 30);
	custom_levels[2].rooms[4].links.left = 2;

	// room 6
	memcpy(custom_levels[2].rooms[5].fg, (byte[]){  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 0, 0, 0, 0, 0,20, 0, 1, 4,
						        0, 0, 0, 0, 0, 0,20, 1, 1, 4}, 30);
	custom_levels[2].rooms[5].links.right = 3;
}

void load_custom_level(int n, level_type* level_ref) {
	n--; // level numbers are 1-indexed
	custom_level_data level_data = custom_levels[n];

	// zero out level_ref

	for (int i = 0; i < 720; i++) {
		level_ref->fg[i] = 0;
	}

	for (int i = 0; i < 256; i++) {
		level_ref->doorlinks_rooms[i] = 0;
		level_ref->doorlinks_tiles[i] = 0;
		level_ref->doorlinks_timers[i] = 0;
		level_ref->doorlinks_nexts[i] = 0;
	}

	for (int i = 0; i < 24; i++) {
		level_ref->roomlinks[i].up = 0;
		level_ref->roomlinks[i].down = 0;
		level_ref->roomlinks[i].left = 0;
		level_ref->roomlinks[i].right = 0;
		level_ref->roomxs[i] = 0;
		level_ref->roomys[i] = 0;
		level_ref->guards_tile[i] = -1; // no guard
		level_ref->guards_x[i] = 0;
		level_ref->guards_seq_lo[i] = 0;
		level_ref->guards_seq_hi[i] = 0;
		level_ref->guards_skill[i] = 0;
		level_ref->guards_color[i] = 0;
	}

	level_ref->used_rooms = 1;
	level_ref->start_room = 1;
	level_ref->start_pos = 1;
	level_ref->start_dir = 0;

	// load from level_data

	for (int room = 0; room < level_data.used_rooms; room++) {
		for (int space = 0; space < 30; space++) {
			level_ref->bg[(room*30)+space] = level_data.rooms[room].bg[space];
			level_ref->fg[(room*30)+space] = level_data.rooms[room].fg[space];
		}
		level_ref->roomlinks[room] = level_data.rooms[room].links;
		level_ref->guards_tile[room] = level_data.rooms[room].guard_tile;
	}
	for (int n = 0; n < 256; n++) {
		level_ref->doorlinks_tiles[n] = level_data.doorlinks_tiles[n];
		level_ref->doorlinks_rooms[n] = level_data.doorlinks_rooms[n];
		level_ref->doorlinks_nexts[n] = level_data.doorlinks_nexts[n];
		level_ref->doorlinks_timers[n] = level_data.doorlinks_timers[n];
	}
	level_ref->used_rooms = level_data.used_rooms;
	level_ref->start_room = level_data.start_room;
	level_ref->start_pos = level_data.start_pos;
	level_ref->start_dir = level_data.start_dir;
	bg_colour = level_data.bg_colour;
}
