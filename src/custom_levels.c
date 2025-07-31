#include "common.h"

#include "custom_levels/level_1.c"
#include "custom_levels/level_1_duel.c"
#include "custom_levels/level_2.c"
#include "custom_levels/level_2_duel.c"
#include "custom_levels/level_3.c"
#include "custom_levels/level_3_duel.c"
#include "custom_levels/level_4.c"
#include "custom_levels/level_4_duel.c"
#include "custom_levels/level_5.c"
#include "custom_levels/level_5_duel.c"
#include "custom_levels/level_6.c"

// it's honestly easier to construct the level_type structs directly than to use a level editor
// plus it means we can store extra stuff like background colour directly in our level data

#define NUM_LEVELS 11

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

	make_level_1(&custom_levels[0]);
	make_level_1_duel(&custom_levels[1]);
	make_level_2(&custom_levels[2]);
	make_level_2_duel(&custom_levels[3]);
	make_level_3(&custom_levels[4]);
	make_level_3_duel(&custom_levels[5]);
	make_level_4(&custom_levels[6]);
	make_level_4_duel(&custom_levels[7]);
	make_level_5(&custom_levels[8]);
	make_level_5_duel(&custom_levels[9]);
	make_level_6(&custom_levels[10]);
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
