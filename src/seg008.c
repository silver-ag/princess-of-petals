/*
SDLPoP, a port/conversion of the DOS game Prince of Persia.
Copyright (C) 2013-2025  Dávid Nagy

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

The authors of this program may be contacted at https://forum.princed.org
*/

#include "common.h"

// data:27E0
add_table_type ptr_add_table = add_backtable;

// data:259C
const piece tile_table[32] = {
// base_id, floor_left, base_y, right_id, floor_right, right_y, stripe_id, topright_id, bottom_id, fore_id, fore_x, fore_y, topright_x, topright_y
{   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}, // 0x00 empty
{  41,   1,   0,  42,   1,   2, 149,   0,  43,   0,   0,   0,   0,   0}, // 0x01 floor
{  41,   1,   0,  42,   1,   2, 149,   0,  43,   0,   0,   0,   0,   0}, // 0x02 CHANGED egg
{  92,   1,   0,  93,   1,   2,   0,  94,  43,  95,   1,   0,   0,   0}, // 0x03 pillar
{  46,   1,   0,  47,   1,   2,   0,  48,  43,  49,   3,   0,   0,   0}, // 0x04 door
{  41,   1,   1,  35,   1,   3, 149,   0,  36,   0,   0,   0,   0,   0}, // 0x05 stuck floor
{  41,   1,   0,  42,   1,   2, 149,   0,  96,   0,   0,   0,   0,   0}, // 0x06 close button
{  46,   1,   0,   0,   0,   2,   0,   0,  43,  49,   3,   0,   0,   0}, // 0x07 door top with floor
{  86,   1,   0,  87,   1,   2,   0,   0,  43,  88,   1,   0,   0,   0}, // 0x08 big pillar bottom
{   0,   0,   0,  89,   0,   3,   0,  90,   0,  91,   1,   3,   0,   0}, // 0x09 big pillar top
{  41,   1,   0,  42,   1,   2, 149,   0,  43,  12,   2,  -3,   0,   0}, // 0x0A potion
{   0,   1,   0,   0,   0,   0, 149,   0,   0,   0,   0,   0,   0,   0}, // 0x0B loose floor
{   0,   0,   0,   0,   0,   2,   0,   0,  85,  49,   3,   0,   0,   0}, // 0x0C door top
{  75,   1,   0,  42,   1,   2,   0,   0,  43,  77,   0,   0,   0,   0}, // 0x0D mirror
{  97,   1,   0,  98,   1,   2, 149,   0,  43, 100,   0,   0,   0,   0}, // 0x0E debris
{ 147,   1,   0,  42,   1,   1, 149,   0, 149,   0,   0,   0,   0,   0}, // 0x0F open button
{  41,   1,   0,  37,   0,   0,   0, 154,  43,   0,   0,   0,   0,   0}, // 0x10 leveldoor left - topright_id to 152, 154 for gate opening
{   0,   0,   0,  39,   1,   2,   0, 155,  43,   0,   0,   0,   0,   0}, // 0x11 leveldoor right - topright_id to 153, 155 for gate opening
{   0,   0,   0,  42,   1,   2, 149,   0,  43,   0,   0,   0,   0,   0}, // 0x12 chomper
// torches commented out because we can't have more than 32 tile types. it'd be a huge pain to add more because tiles are stored in curr_room_tiles as ints that are the fg and bg put together in one bitfield, so we can't take up more bits
//{  41,   1,   0,  42,   1,   2,   0,   0,  43,   0,   0,   0}, // 0x13 torch
{ 160,   1,   1, 162,   1,   2, 149,   0,  43,   0,   0,   0,   0,   0}, // ADDED rose seal floor
{   0,   0,   0,   1,   1,   2,   0,   2,   0,   0,   0,   0,   0,   0}, // 0x14 wall
{  30,   1,   0, 152,   1,   2,   0,   0,  43,   0,   0,   0,   0,  48}, // 0x15 skeleton CHANGED to rose gate wing left
{  41,   1,   0,  42,   1,   2, 149,   0,  43,   0,   0,   0,   0,   0}, // 0x16 sword
//{  41,   1,   0,  10,   0,   0,   0,  11,  43,   0,   0,   0,   0,   0}, // 0x17 balcony left
{ 170,   1,   0,  42,   1,   2,   0,   0,  43,  49,   0,   0,   0,   0}, // 0x17 CHANGED door left
{   0,   0,   0,  12,   1,   2,   0,  13,  43,   0,   0,   0,   0,   0}, // 0x18 balcony right
{  92,   1,   0,  42,   1,   2, 149,   0,  43,  95,   1,   0,   0,   0}, // 0x19 lattice pillar
{   1,   0,   0,   0,   0,   0,   0,   0,   2,   9,   0, -53,   0,   0}, // 0x1A lattice down
{   3,   0, -10,   0,   0,   0,   0,   0,   0,   9,   0, -53,   0,   0}, // 0x1B lattice small
{   4,   0, -10,   0,   0,   0,   0,   0,   0,   9,   0, -53,   0,   0}, // 0x1C lattice left
{   5,   0, -10,   0,   0,   0,   0,   0,   0,   9,   0, -53,   0,   0}, // 0x1D lattice right
//{  97,   1,   0,  98,   1,   2,   0,   0,  43, 100,   0,   0}, // 0x1E debris with torch
{ 127,   1,   0, 153,   1,   2, 149,   0,  43,   0,   0,   0,  22,  48}, // ADDED rose gate wing right
{ 160,   1,   0, 162,   1,   1, 149,   0, 149,   0,   0,   0,   0,   0}, // ADDED rose gate open button
};

// data:4334
short drawn_row;
// data:4352
short draw_bottom_y;
// data:4326
short draw_main_y;
// data:34D0
short drawn_col;
// global value so we can access it while rendering rose gate in get_image() and draw_tile_topright()?
short leveldoor_height;
short water_tick = 0;

// data:6592
byte tile_left;
// data:4CCC
byte modifier_left;

// seg008:0006
void redraw_room() {
	free_peels();
	memset(table_counts, 0, sizeof(table_counts));
	reset_obj_clip();
	draw_room();
	clear_tile_wipes();
}

// seg008:0035
void load_room_links() {
	room_BR = 0;
	room_BL = 0;
	room_AR = 0;
	room_AL = 0;
	if (drawn_room) {
		get_room_address(drawn_room);
		room_L = level.roomlinks[drawn_room-1].left;
		room_R = level.roomlinks[drawn_room-1].right;
		room_A = level.roomlinks[drawn_room-1].up;
		room_B = level.roomlinks[drawn_room-1].down;
		if (room_A) {
			room_AL = level.roomlinks[room_A-1].left;
			room_AR = level.roomlinks[room_A-1].right;
		} else {
			if (room_L) {
				room_AL = level.roomlinks[room_L-1].up;
			}
			if (room_R) {
				room_AR = level.roomlinks[room_R-1].up;
			}
		}
		if (room_B) {
			room_BL = level.roomlinks[room_B-1].left;
			room_BR = level.roomlinks[room_B-1].right;
		} else {
			if (room_L) {
				room_BL = level.roomlinks[room_L-1].down;
			}
			if (room_R) {
				room_BR = level.roomlinks[room_R-1].down;
			}
		}
	} else {
		room_B = 0;
		room_A = 0;
		room_R = 0;
		room_L = 0;
	}
}

// seg008:0125
void draw_room() {
	load_leftroom();
	for (drawn_row = 3; drawn_row--; ) { /*2,1,0*/
		load_rowbelow();
		draw_bottom_y = 63 * drawn_row + 65;
		draw_main_y = draw_bottom_y - 3;
		for (drawn_col = 0; drawn_col < 10; drawn_col++) {
			load_curr_and_left_tile();
			draw_tile();
		}
	}
	word saved_room = drawn_room;
	drawn_room = room_A;
	load_room_links();
	load_leftroom();
	drawn_row = 2;
	load_rowbelow();
	for (drawn_col = 0; drawn_col < 10; ++drawn_col) {
		load_curr_and_left_tile();
		draw_main_y = -1;
		draw_bottom_y = 2;
		draw_tile_aboveroom();
	}
	drawn_room = saved_room;
	load_room_links();
}

// seg008:01C7
void draw_tile() {
	draw_tile_floorright();
	draw_tile_anim_topright();
	draw_tile_right();
	draw_tile_anim_right();
	draw_tile_bottom(0);
	draw_loose(0);
	draw_tile_base();
	draw_tile_anim();
	draw_tile_fore();
}

// seg008:01F2
void draw_tile_aboveroom() {
	draw_tile_floorright();
	draw_tile_anim_topright();
	draw_tile_right();
	draw_tile_bottom(0);
	draw_loose(0);
	draw_tile_fore();
}

// seg008:0211
void redraw_needed(short tilepos) {
	if (wipe_frames[tilepos]) {
		--wipe_frames[tilepos];
		draw_tile_wipe(wipe_heights[tilepos]);
	}// else if (redraw_frames_full[tilepos]) {
		//--redraw_frames_full[tilepos];
		draw_tile();
	//} else {
		if (redraw_frames_anim[tilepos]) {
			--redraw_frames_anim[tilepos];
			draw_tile_anim_topright();
			draw_tile_anim_right();
			draw_tile_anim();
#ifdef FIX_ABOVE_GATE
			draw_tile_fore();
			draw_tile_bottom(0);
#endif
		}
	//}
	if (redraw_frames2[tilepos]) {
		--redraw_frames2[tilepos];
		draw_other_overlay();
	} else {
		if (redraw_frames_floor_overlay[tilepos]) {
			--redraw_frames_floor_overlay[tilepos];
			draw_floor_overlay();
		}
	}
	if (tile_object_redraw[tilepos]) {
		if (tile_object_redraw[tilepos] == 0xFF) {
			draw_objtable_items_at_tile(tilepos - 1);
		}
		draw_objtable_items_at_tile(tilepos);
		tile_object_redraw[tilepos] = 0;
	}
	if (redraw_frames_fore[tilepos]) {
		--redraw_frames_fore[tilepos];
		draw_tile_fore();
	}
}

// seg008:02C1
void redraw_needed_above(int column) {
	if (redraw_frames_above[column] != 0) {
		--redraw_frames_above[column];
#ifdef FIX_BIGPILLAR_JUMP_UP
		if (curr_tile != tiles_9_bigpillar_top)
#endif
		{
			draw_tile_wipe(3);
			draw_tile_floorright();
		}
		draw_tile_anim_topright();
		draw_tile_right();
		draw_tile_bottom(1);
		draw_loose(1);
		draw_tile_fore();
	}
}

// seg008:02FE
int get_tile_to_draw(int room, int column, int row, byte* ptr_tiletype, byte* ptr_modifier, byte tile_room0) {
	word tilepos = tbl_line[row] + column;
	if (column == -1) {
		*ptr_tiletype = leftroom_[row].tiletype;
		*ptr_modifier = leftroom_[row].modifier;
	} else if (room) {
		*ptr_tiletype = curr_room_tiles[tilepos] & 0x1F;
		*ptr_modifier = curr_room_modif[tilepos];
	} else {
		*ptr_modifier = 0;
		*ptr_tiletype = tile_room0;
	}
	// Is this a pressed button?
	byte tiletype = (*ptr_tiletype) & 0x1F;
	byte modifier = *ptr_modifier;
	if (tiletype == tiles_6_closer) {
		if (get_doorlink_timer(modifier) > 1) {
			*ptr_tiletype = tiles_5_stuck;
		}
	} else if (tiletype == tiles_15_opener) {
		if (get_doorlink_timer(modifier) > 1) {
			*ptr_modifier = 0;
			*ptr_tiletype = tiles_1_floor;
		}
	} else if (tiletype == tiles_rose_gate_opener) {
		if (get_doorlink_timer(modifier) > 1) {
			*ptr_modifier = 0;
			*ptr_tiletype = tiles_rose_seal_floor;
		}
	}

#ifdef USE_FAKE_TILES
	else if (tiletype == tiles_0_empty) {
		if (modifier == 4 || modifier == 12) {     // display a fake floor
			*ptr_tiletype = tiles_1_floor;
			*ptr_modifier = (modifier == 12) ? 1 : 0; // 12: noblue option
		}
		else if (modifier == 5 || modifier == 13) {   // display a fake wall
			*ptr_tiletype = tiles_20_wall;
			*ptr_modifier = (modifier == 13) ? 0x80 : 0; // 13: noblue option
		}
		else if (modifier == 50) {   // display a fake wall (pattern: no walls left or right)
			*ptr_tiletype = tiles_20_wall;
			*ptr_modifier = 0;
		}
		else if (modifier == 51) {   // display a fake wall (pattern: wall only to the right)
			*ptr_tiletype = tiles_20_wall;
			*ptr_modifier = 1;
		}
		else if (modifier == 52) {   // display a fake wall (pattern: wall only to the left)
			*ptr_tiletype = tiles_20_wall;
			*ptr_modifier = 2;
		}
		else if (modifier == 53) {   // display a fake wall (pattern: wall on both sides)
			*ptr_tiletype = tiles_20_wall;
			*ptr_modifier = 3;
		}
	}
	else if (tiletype == tiles_1_floor) {
		if (modifier == 6 || modifier == 14) {   // display nothing (invisible floor)
			*ptr_tiletype = tiles_0_empty;
			*ptr_modifier = (modifier == 14) ? 1 : 0; // modifier should be '0' for noblue, instead of '1'
		}
		else if (modifier == 5 || modifier == 13) {   // display a fake wall
			*ptr_tiletype = tiles_20_wall;
			*ptr_modifier = (modifier == 13) ? 0x80 : 0; // 13: noblue option
		}
		else if (modifier == 50) {   // display a fake wall (pattern: no walls left or right (noblue))
			*ptr_tiletype = tiles_20_wall;
			*ptr_modifier = 0;
		}
		else if (modifier == 51) {   // display a fake wall (pattern: wall only to the right)
			*ptr_tiletype = tiles_20_wall;
			*ptr_modifier = 1;
		}
		else if (modifier == 52) {   // display a fake wall (pattern: wall only to the left)
			*ptr_tiletype = tiles_20_wall;
			*ptr_modifier = 2;
		}
		else if (modifier == 53) {   // display a fake wall (pattern: wall on both sides)
			*ptr_tiletype = tiles_20_wall;
			*ptr_modifier = 3;
		}
	}
	else if (tiletype == tiles_20_wall) {
		// Walls are a bit strange, because a lot of modifier information is discarded in load_alter_mod() (seg008.c)
		// Also, the "noblue" info for the wall tile is moved to the --most significant-- modifier bit there.

		// load_alter_mod() has been tweaked to retain more information (now stored in the most significant 4 bytes)
		// Modifiers 2-7 are now accessible to define various fake tiles
		// Modifiers 9-15 'loop back' onto 2-7 (identical tiles), EXCEPT they also have the "noblue" bit set
		if (((modifier >> 4) & 7) == 4) {     // display a floor (invisible wall)
			*ptr_tiletype = tiles_1_floor;
			*ptr_modifier = (modifier >> 7); // modifier should be '1' for noblue option
		}
		else if (((modifier >> 4) & 7) == 6) {   // display empty tile (invisible wall)
			*ptr_tiletype = tiles_0_empty;
			*ptr_modifier = (modifier >> 7) ? 1 : 0; // modifier should be '0' for noblue, instead of '1'
		}
	}
#endif
#ifdef FIX_LOOSE_LEFT_OF_POTION
	else if (fixes->fix_loose_left_of_potion && tiletype == tiles_11_loose) {
		if ((*ptr_modifier & 0x7F) == 0) {
			*ptr_tiletype = tiles_1_floor;
		}
	}
#endif
	return *ptr_tiletype;
}

// data:24C6
const word col_xh[] = {0, 4, 8, 12, 16, 20, 24, 28, 32, 36};
// seg008:03BB
void load_curr_and_left_tile() {
	word tiletype = tiles_20_wall;
	if (drawn_row == 2) {
		tiletype = custom->drawn_tile_top_level_edge; // floor at top of level (default: tiles_1_floor)
	}
	get_tile_to_draw(drawn_room, drawn_col, drawn_row, &curr_tile, &curr_modifier, tiletype);
	get_tile_to_draw(drawn_room, drawn_col - 1, drawn_row, &tile_left, &modifier_left, tiletype);
	draw_xh = col_xh[drawn_col];
}

// seg008:041A
void load_leftroom() {
	get_room_address(room_L);
	for (word row = 0; row < 3; ++row) {
		// wall at left of level (drawn_tile_left_level_edge), default: tiles_20_wall
		get_tile_to_draw(room_L, 9, row, &leftroom_[row].tiletype, &leftroom_[row].modifier, custom->drawn_tile_left_level_edge);
	}
}

// seg008:0460
void load_rowbelow() {
	word row_below;
	word room;
	word room_left;
	if (drawn_row == 2) {
		room = room_B;
		room_left = room_BL;
		row_below = 0;
	} else {
		room = drawn_room;
		room_left = room_L;
		row_below = drawn_row + 1;
	}
	get_room_address(room);
	for (word column = 1; column < 10; ++column) {
		get_tile_to_draw(room, column - 1, row_below, &row_below_left_[column].tiletype, &row_below_left_[column].modifier, tiles_0_empty);
	}
	get_room_address(room_left);
	// wall at left of level
	get_tile_to_draw(room_left, 9, row_below, &row_below_left_[0].tiletype, &row_below_left_[0].modifier, tiles_20_wall);
	get_room_address(drawn_room);
}

// seg008:04FA
void draw_tile_floorright() {
	if (can_see_bottomleft() == 0) return;
	draw_tile_topright();
	if (tile_table[tile_left].floor_right == 0) return;
	add_backtable(id_chtab_6_environment, 42 /*floor right part*/, draw_xh, 0, tile_table[tiles_1_floor].right_y + draw_main_y, blitters_9_black, 1);
}

// seg008:053A
int can_see_bottomleft() {
	return curr_tile == tiles_0_empty ||
		curr_tile == tiles_9_bigpillar_top ||
		curr_tile == tiles_12_doortop ||
		curr_tile == tiles_26_lattice_down;
}

const byte doortop_fram_top[] = {0, 81, 83, 0};

// seg008:055A
void draw_tile_topright() {
	byte tiletype = row_below_left_[drawn_col].tiletype;
	if (tiletype == tiles_7_doortop_with_floor || tiletype == tiles_12_doortop) {
		if (custom->tbl_level_type[current_level] == 0) return;
		add_backtable(id_chtab_6_environment, doortop_fram_top[row_below_left_[drawn_col].modifier], draw_xh, 0, draw_bottom_y, blitters_2_or, 0);
	} else if (tiletype == tiles_20_wall) {
		add_backtable(id_chtab_7_environmentwall, 2, draw_xh, 0, draw_bottom_y, blitters_2_or, 0);
	} else {
		int id = tile_table[tiletype].topright_id;
		int dx = tile_table[tiletype].topright_x;
		int dy = tile_table[tiletype].topright_y;
#ifdef USE_TELEPORTS
		// Use teleport graphics:
		// * for the left half of a balcony, if it has a non-zero modifier.
		// * for the right half of a balcony, if it has modifier == 1.
		/*if (
			(tiletype == tiles_23_balcony_left && row_below_left_[drawn_col].modifier != 0)
			|| (tiletype == tiles_24_balcony_right && row_below_left_[drawn_col].modifier == 1)
		) {
			id += 4;
		}*/
#endif
		// rose gate opening
		if (tiletype == tiles_16_level_door_left) {
			if (row_below_left_[drawn_col].modifier < 40) {
				id = 154;
			} else if (row_below_left_[drawn_col].modifier < 60) {
				id = 156;
			} else {
				id = 158;
			}
		} else if (tiletype == tiles_17_level_door_right) {
			if (row_below_left_[drawn_col-1].modifier < 40) {
				id = 155;
			} else if (row_below_left_[drawn_col-1].modifier < 60) {
				id = 157;
			} else {
				id = 159;
			}
		} else if (tiletype == tiles_21_rose_gate_wing_left) {
			if (leveldoor_height > 0) {
				id = 166 + water_tick;
			} else {
				id = 0;
			}
		} else if (tiletype == tiles_30_rose_gate_wing_right) {
			if (leveldoor_height > 0) {
				id = 166 + water_tick;
			} else {
				id = 0;
			}
		} else if (tiletype == tiles_1_floor && (row_below_left_[drawn_col].modifier == 11 || row_below_left_[drawn_col].modifier == 12)) { // johnny statue
			if (row_below_left_[drawn_col].modifier == 11) {
				id = 179;
			} else {
				id = 180;
			}
			dy = 50;
			dx = -35;
		}
		add_backtable(id_chtab_6_environment, id, draw_xh, dx, draw_bottom_y+dy, blitters_2_or, 0);
	}
}

const byte door_fram_top[] = {60, 61, 62, 63, 64, 65, 66, 67};

// seg008:05D1
void draw_tile_anim_topright() {
	if (	(curr_tile == tiles_0_empty ||
		curr_tile == tiles_9_bigpillar_top ||
		curr_tile == tiles_12_doortop)
		&& (row_below_left_[drawn_col].tiletype == tiles_4_gate || row_below_left_[drawn_col].tiletype == tiles_23_left_gate)
	) {
		int x_offset = 0;
		if (row_below_left_[drawn_col].tiletype == tiles_23_left_gate) {
			x_offset = -24;
		}
		add_backtable(id_chtab_6_environment, 68 /*gate top mask*/, draw_xh, x_offset, draw_bottom_y, /*blitters_40h_mono*/blitters_11_mono_bg, 0);
		word modifier = row_below_left_[drawn_col].modifier;
		if (modifier > 188) modifier = 188;
		add_backtable(id_chtab_6_environment, door_fram_top[(modifier>>2) % 8], draw_xh, x_offset, draw_bottom_y, blitters_2_or, 0);
	}
}

const byte blueline_fram1[] = {0, 124, 125, 126};
const sbyte blueline_fram_y[] = {0, -20, -20, 0};
const byte blueline_fram3[] = {44, 44, 45, 45};
const byte doortop_fram_bot[] = {78, 80, 82, 0};

// seg008:066A
void draw_tile_right() {
	byte id;
	byte blit;
	byte num;
	if (curr_tile == tiles_20_wall) return;
	switch (tile_left) {
		default:
			id = tile_table[tile_left].right_id;
#ifdef USE_TELEPORTS
			// Use teleport graphics:
			// * for the left half of a balcony, if it has a non-zero modifier.
			// * for the right half of a balcony, if it has modifier == 1.
			/*if (tile_left == tiles_23_balcony_left && modifier_left != 0) {
				id += 4;
			} else if (tile_left == tiles_24_balcony_right && modifier_left == 1) {
				id += 4;
			}*/
#endif
			if (id) {
				if (tile_left == tiles_5_stuck) {
					blit = blitters_10h_transp;
					if (curr_tile == tiles_0_empty || curr_tile == tiles_5_stuck || !tile_is_floor(curr_tile)) {
						id = 42; /*floor B*/
					}
				} else {
					blit = blitters_2_or;
				}
				add_backtable(id_chtab_6_environment, id, draw_xh, 0, tile_table[tile_left].right_y + draw_main_y, blit, 0);
			}
			if (custom->tbl_level_type[current_level] != 0) {
				add_backtable(id_chtab_6_environment, tile_table[tile_left].stripe_id, draw_xh, 0, draw_main_y - 27, blitters_2_or, 0);
			}
			//if (tile_left == tiles_19_torch) { // || tile_left == tiles_30_torch_with_debris) {
			//	add_backtable(id_chtab_6_environment, 146 /*torch base*/, draw_xh, 0, draw_bottom_y - 28, blitters_0_no_transp_tile, 0);
			//}
			break;
		case tiles_0_empty:
			if (modifier_left > 3) return;
			add_backtable(id_chtab_6_environment, blueline_fram1[modifier_left], draw_xh, 0, blueline_fram_y[modifier_left] + draw_main_y, blitters_2_or, 0);
			break;
		case tiles_1_floor:
			ptr_add_table(id_chtab_6_environment, 42 /*floor B*/, draw_xh, 0, tile_table[tile_left].right_y + draw_main_y, blitters_10h_transp, 0);
			num = modifier_left;
			if (num > 3) num = 0;
			if (num == !!custom->tbl_level_type[current_level]) return;
			add_backtable(id_chtab_6_environment, blueline_fram3[num], draw_xh, 0, draw_main_y - 20, blitters_2_or, 0);
			break;
		case tiles_7_doortop_with_floor:
		case tiles_12_doortop:
			if (custom->tbl_level_type[current_level] == 0) return;
			add_backtable(id_chtab_6_environment, doortop_fram_bot[modifier_left], draw_xh, 0, tile_table[tile_left].right_y + draw_main_y, blitters_2_or, 0);
			break;
		case tiles_20_wall:
			if (custom->tbl_level_type[current_level] && (modifier_left & 0x80) == 0) {
				add_backtable(id_chtab_6_environment, 84 /*wall stripe*/, draw_xh + 3, 0, draw_main_y - 27, blitters_0_no_transp_tile, 0);
			}
			add_backtable(id_chtab_7_environmentwall, 1, draw_xh, 0, tile_table[tile_left].right_y + draw_main_y, blitters_2_or, 0);
			break;
	}
}

const byte spikes_fram_right[] = {0, 134, 135, 136, 137, 138, 137, 135, 134, 0};
const byte loose_fram_right[] = {42, 71, 42, 72, 72, 42, 42, 42, 72, 72, 72, 0};

// seg008:08A0
int get_spike_frame(byte modifier) {
	if (modifier & 0x80) {
		return 5;
	} else {
		return modifier;
	}
}

// seg008:08B5
void draw_tile_anim_right() {
	switch (tile_left) {
		//case tiles_2_spike:
		//	add_backtable(id_chtab_6_environment, spikes_fram_right[get_spike_frame(modifier_left)], draw_xh, 0, draw_main_y - 7, blitters_10h_transp, 0);
		//break;
		case tiles_4_gate:
			draw_gate_back();
		break;
		case tiles_11_loose:
			add_backtable(id_chtab_6_environment, loose_fram_right[get_loose_frame(modifier_left)], draw_xh, 0, draw_bottom_y - 1, blitters_2_or, 0);
		break;
		case tiles_16_level_door_left:
			draw_leveldoor();
		break;
		/*case tiles_19_torch:
		case tiles_30_torch_with_debris:
			if (modifier_left < 9) {
				int blit = blitters_0_no_transp_tile;
#ifdef USE_COLORED_TORCHES
				int color;
				if (drawn_col == 0) {
					// Torch is in the rightmost column of the left-side room.
					color = torch_colors[room_L][drawn_row * 10 + 9];
				} else {
					color = torch_colors[drawn_room][drawn_row * 10 + drawn_col - 1];
				}
				if (color != 0) {
					blit = blitters_colored_flame + (color & 0x3F);
				}
#endif
				// images 1..9 are the flames
				add_backtable(id_chtab_1_flameswordpotion, modifier_left + 1, draw_xh + 1, 0, draw_main_y - 40, blit, 0);
			}
		break;*/
	}
}

const byte wall_fram_bottom[] = {7, 9, 5, 3};

// seg008:0971
void draw_tile_bottom(word arg_0) {
	byte id = 0;
	byte blit = blitters_0_no_transp_tile;
	word chtab_id = id_chtab_6_environment;
	switch (curr_tile) {
		case tiles_20_wall:
			if (custom->tbl_level_type[current_level] == 0 || custom->enable_wda_in_palace || graphics_mode != gmMcgaVga) {
				id = wall_fram_bottom[curr_modifier & 0x7F];
			}
			chtab_id = id_chtab_7_environmentwall;
			break;
		case tiles_12_doortop:
			blit = blitters_2_or;
			// fallthrough!
		default:
			id = tile_table[curr_tile].bottom_id;
			break;
	}
	if (ptr_add_table(chtab_id, id, draw_xh, 0, draw_bottom_y, blit, 0) && arg_0) {
		add_foretable(chtab_id, id, draw_xh, 0, draw_bottom_y, blit, 0);
	}
	if (chtab_id == id_chtab_7_environmentwall && graphics_mode != gmCga && graphics_mode != gmHgaHerc) {
		wall_pattern(0, 0);
	}
}

const byte loose_fram_bottom[] = {43, 73, 43, 74, 74, 43, 43, 43, 74, 74, 74, 0};

// seg008:0A38
void draw_loose(int arg_0) {
	word id;
	if (curr_tile == tiles_11_loose) {
		id = loose_fram_bottom[get_loose_frame(curr_modifier)];
		add_backtable(id_chtab_6_environment, id, draw_xh, 0, draw_bottom_y, blitters_0_no_transp_tile, 0);
		add_foretable(id_chtab_6_environment, id, draw_xh, 0, draw_bottom_y, blitters_0_no_transp_tile, 0);
	}
}

const byte loose_fram_left[] = {41, 69, 41, 70, 70, 41, 41, 41, 70, 70, 70, 0};

// seg008:0A8E
void draw_tile_base() {
	word id;
	word ybottom = draw_main_y;
#ifdef USE_SUPER_HIGH_JUMP
	// Latice tiles are drawn in the draw_tile_fore() method.
	if (fixes->enable_super_high_jump) {
		if ((curr_tile >= tiles_26_lattice_down && curr_tile <= tiles_29_lattice_right) ||
			(tile_left == tiles_26_lattice_down && curr_tile == tiles_12_doortop)) {
			return;
		}
	}
#endif
	if (tile_left == tiles_26_lattice_down && curr_tile == tiles_12_doortop) {
		id = 6; // Lattice + door A
		ybottom += 3;
	} else if (curr_tile == tiles_11_loose) {
		id = loose_fram_left[get_loose_frame(curr_modifier)];
	} else if (curr_tile == tiles_15_opener && tile_left == tiles_0_empty && custom->tbl_level_type[current_level] == 0) {
		id = 148; // left half of open button with no floor to the left
	} else if (curr_tile == tiles_rose_gate_opener && tile_left == tiles_0_empty && custom->tbl_level_type[current_level] == 0) {
		id = 161; // left half of rose gate open button with no floor to the left
	} else {
		id = tile_table[curr_tile].base_id;
	}
	ptr_add_table(id_chtab_6_environment, id, draw_xh, 0, tile_table[curr_tile].base_y + ybottom, blitters_10h_transp, 0);
}

const byte spikes_fram_left[] = {0, 128, 129, 130, 131, 132, 131, 129, 128, 0};
const byte potion_fram_bubb[] = {0, 16, 17, 18, 19, 20, 21, 22};
const byte chomper_fram1[] = {3, 2, 0, 1, 4, 3, 3, 0};
const byte chomper_fram_bot[] = {101, 102, 103, 104, 105, 0};
const byte chomper_fram_top[] = {0, 0, 111, 112, 113, 0};
const byte chomper_fram_y[] = {0, 0, 0x25, 0x2F, 0x32};

// seg008:0B2B
void draw_tile_anim() {
	word chomper_num;
	//word pot_size = 0;
	//word color = 12; // red
	switch (curr_tile) {
		//case tiles_2_spike:
		//	ptr_add_table(id_chtab_6_environment, spikes_fram_left[get_spike_frame(curr_modifier)], draw_xh, 0, draw_main_y - 2, blitters_10h_transp, 0);
		//	break;
		/*case tiles_10_potion:
			switch((curr_modifier & 0xF8) >> 3) {
				case 0: // empty
					return;
				case 5: // hurt
				case 6: // open
					color = 9; // blue
					break;
				case 3: // slow fall
				case 4: // upside down
					color = 10; // green
					// fallthrough!
				case 2: // life
					pot_size = 1;
					break;
			}
			//add_backtable(id_chtab_1_flameswordpotion, 23 bubble mask, draw_xh + 3, 1, draw_main_y - (pot_size << 2) - 14, blitters_40h_mono, 0);
			add_foretable(id_chtab_1_flameswordpotion, potion_fram_bubb[curr_modifier & 0x7], draw_xh + 3, 1, draw_main_y - (pot_size << 2) - 14, blitters_10h_transp, 0);
			break;*/
		case tiles_23_left_gate:
			draw_left_gate_back();
			break;
		case tiles_22_sword:
			add_midtable(id_chtab_1_flameswordpotion, (curr_modifier == 1) + 10, draw_xh, 0, draw_main_y - 3, blitters_10h_transp, curr_modifier == 1);
			break;
		case tiles_18_chomper:
			chomper_num = chomper_fram1[MIN(curr_modifier & 0x7F, 6)];
			add_backtable(id_chtab_6_environment, chomper_fram_bot[chomper_num], draw_xh, 0, draw_main_y, blitters_10h_transp, 0);
			if (curr_modifier & 0x80) { // blood
				add_backtable(id_chtab_6_environment, chomper_num + 114, draw_xh + 1, 4, draw_main_y - 6, blitters_4Ch_mono_12, 0);
			}
			add_backtable(id_chtab_6_environment, chomper_fram_top[chomper_num], draw_xh, 0, draw_main_y - chomper_fram_y[chomper_num], blitters_10h_transp, 0);
			break;
	}
}

const byte spikes_fram_fore[] = {0, 139, 140, 141, 142, 143, 142, 140, 139, 0};
const byte chomper_fram_for[] = {106, 107, 108, 109, 110, 0};
const byte wall_fram_main[] = {8, 10, 6, 4};

// seg008:0D15
void draw_tile_fore() {
	word ybottom;
	byte xh;
	word potion_type;
	word id;
	word chomper_num;
	if (tile_left == tiles_4_gate && Kid.curr_row == drawn_row && Kid.curr_col == drawn_col - 1 && Kid.room != room_R) {
		if (!((Kid.frame >= 70 && Kid.frame < 100) || (Kid.frame >= frame_135_climbing_1 && Kid.frame <= frame_149_climbing_15))) {
			draw_gate_fore();
		}
	} else if (curr_tile == tiles_23_left_gate && Kid.curr_row == drawn_row && Kid.curr_col + 2 == drawn_col) { // && Kid.room != room_R) { // left gate
		draw_left_gate_fore();
	} else if (curr_tile == tiles_23_left_gate && Kid.curr_row == drawn_row + 1 && Kid.curr_col + 1 == drawn_col) { // && Kid.room != room_R) { // left gate climb up (no equivalent for regular gates because you can't climb up behind them because they're on the front side of the tile wrt to the isometric view)
		draw_left_gate_fore();
	} else if (curr_tile == tiles_23_left_gate) {// && Kid.curr_row == drawn_row) {
		if ((Kid.frame >= 70 && Kid.frame < 100) || (Kid.frame >= frame_135_climbing_1 && Kid.frame <= frame_149_climbing_15)) {
			draw_left_gate_fore();
		}
	}
	switch (curr_tile) {
		case tiles_2_egg:
			draw_egg();
			break;
		case tiles_18_chomper:
			chomper_num = chomper_fram1[MIN(curr_modifier & 0x7F, 6)];
			add_foretable(id_chtab_6_environment, chomper_fram_for[chomper_num], draw_xh, 0, draw_main_y, blitters_10h_transp, 0);
			if (curr_modifier & 0x80) {
				add_foretable(id_chtab_6_environment, chomper_num + 119, draw_xh + 1, 4, draw_main_y - 6, blitters_4Ch_mono_12, 0);
			}
			break;
		case tiles_20_wall:
			if (custom->tbl_level_type[current_level] == 0 || custom->enable_wda_in_palace || graphics_mode != gmMcgaVga) {
				add_foretable(id_chtab_7_environmentwall, wall_fram_main[curr_modifier & 0x7F], draw_xh, 0, draw_main_y, blitters_0_no_transp_tile, 0);
			}
			if (graphics_mode != gmCga && graphics_mode != gmHgaHerc) {
				wall_pattern(1, 1);
			}
			// shrine text
			if (curr_modifier == 1) {
				add_foretable(id_chtab_7_environmentwall, 18, draw_xh-27, 0, draw_main_y-10, blitters_0_no_transp_tile, 0);
			}
			break;
#ifdef USE_SUPER_HIGH_JUMP
		// Draw front parts of lattice in the foretable
		// so prince is not in front of it while jumping.
		case tiles_26_lattice_down:
		case tiles_27_lattice_small:
		case tiles_28_lattice_left:
		case tiles_29_lattice_right:
			if (fixes->enable_super_high_jump) {
				add_foretable(id_chtab_6_environment, tile_table[curr_tile].base_id, draw_xh, 0, tile_table[curr_tile].base_y + draw_main_y, blitters_10h_transp, 0);
			}
			// fallthrough!
		default:
			if (fixes->enable_super_high_jump && tile_left == tiles_26_lattice_down && curr_tile == tiles_12_doortop) {
				add_foretable(id_chtab_6_environment, 6, draw_xh, 0, tile_table[curr_tile].base_y + draw_main_y + 3, blitters_10h_transp, 0);
			}
#else
		default:
#endif
			id = tile_table[curr_tile].fore_id;
			if (id == 0) return;
			if (curr_tile == tiles_10_potion) {
				// large pots are drawn for potion types 2, 3, 4
				potion_type = (curr_modifier & 0xF8) >> 3;
				if (potion_type < 5 && potion_type >= 2) id = 13; // small pot = 12, large pot = 13
			}
			xh = tile_table[curr_tile].fore_x + draw_xh;
			ybottom = tile_table[curr_tile].fore_y + draw_main_y;
			if (curr_tile == tiles_10_potion) {
				// potions look different in the dungeon and the palace
				if (custom->tbl_level_type[current_level] != 0) id += 2;
				add_foretable(id_chtab_1_flameswordpotion, id, xh, 6, ybottom, blitters_10h_transp, 0);
			} else {
				if ((curr_tile == tiles_3_pillar && custom->tbl_level_type[current_level] == 0) || (curr_tile >= tiles_27_lattice_small && curr_tile < 30)) { // ??
					add_foretable(id_chtab_6_environment, id, xh, 0, ybottom, blitters_0_no_transp_tile, 0);
				} else {
					add_foretable(id_chtab_6_environment, id, xh, 0, ybottom, blitters_10h_transp, 0);
				}
			}
			break;
	}
}

// seg008:0FF6
int get_loose_frame(byte modifier) {
	// Don't display garbled tiles if the delay is greater than the default.
	if ((modifier & 0x80) || custom->loose_floor_delay > 11) {
		modifier &= 0x7F;
		if (modifier > 10) {
			return 1;
		}
	}
	return modifier;
}

// Get an image, with index and NULL checks.
image_type* get_image(short chtab_id, int id) {
	if (chtab_id < 0 || chtab_id > COUNT(chtab_addrs)) {
		printf("Tried to use chtab %d not in 0..%d\n", chtab_id, (int)COUNT(chtab_addrs));
		return NULL;
	}
	chtab_type* chtab = chtab_addrs[chtab_id];
	if (chtab == NULL) {
		//printf("Tried to use null chtab %d\n", chtab_id);
		return NULL;
	}
	if (id < 0 || id >= chtab->n_images || (id == -1 && chtab_id == id_chtab_6_environment)) {
		if (id != 255) printf("Tried to use image %d of chtab %d, not in 0..%d\n", id, chtab_id, chtab->n_images-1);
		return NULL;
	}
	// construct leveldoor image
	if (id == 164 && chtab_id == id_chtab_6_environment) { // image 165, rose gate
		image_type* rose_gate_door_surface = SDL_CreateRGBSurface(0, 43, 54, 32, Rmsk, Gmsk, Bmsk, Amsk);
		int height = 0;
		if (leveldoor_height > 20) {
			height = leveldoor_height - 20;
		}
		method_1_blit_rect(rose_gate_door_surface, chtab->images[143], &(rect_type){5,5,50,43}, &(rect_type){0,0,49,41}, blitters_10h_transp);
		method_1_blit_rect(rose_gate_door_surface, chtab->images[162], &(rect_type){0,0,54,43}, &(rect_type){0,height/1.5,62,43+height/1.5}, blitters_10h_transp);
		method_1_blit_rect(rose_gate_door_surface, chtab->images[163], &(rect_type){0,0,54,43}, &(rect_type){0,-(height/1.5),62,43-(height/1.5)}, blitters_10h_transp);
		method_1_blit_rect(rose_gate_door_surface, chtab->images[164], &(rect_type){0,0,54,43}, &(rect_type){height,0,62+height,43}, blitters_10h_transp);
		if (silhouette_mode || shadow_world) {
			return silhouette_of(rose_gate_door_surface);
		} else {
			return rose_gate_door_surface;
		}
	}

	if (((!shadow_world) && silhouette_mode) || (shadow_world && chtab_id != id_chtab_2_kid && chtab_id != id_chtab_10_shadow && chtab_id != id_chtab_5_guard)) {
		return silhouette_of(chtab->images[id]);
	} else {
		return chtab->images[id];
	}
}

// seg008:10A8
int add_backtable(short chtab_id, int id, sbyte xh, sbyte xl, int ybottom, int blit, byte peel) {
	if (id == 0) {
		return 0;
	}
	word index = backtable_count;
	if (index >= 300) {
		show_dialog("BackTable Overflow");
		return 0; // added
	}
	back_table_type* backtable_item = &backtable[index];
	backtable_item->xh = xh;
	backtable_item->xl = xl;
	backtable_item->chtab_id = chtab_id;
	backtable_item->id = id - 1;
	image_type* image = get_image(chtab_id, id - 1);
	if (image == NULL) {
		return 0;
	}
	backtable_item->y = ybottom - image->h/*height*/ + 1;
	backtable_item->blit = blit;
	if (draw_mode) {
		draw_back_fore(0, index);
	}
	++backtable_count;
	return 1;
}

// seg008:1017
int add_foretable(short chtab_id, int id, sbyte xh, sbyte xl, int ybottom, int blit, byte peel) {
	if (id == 0) return 0;
	word index = foretable_count;
	if (index >= 200) {
		show_dialog("ForeTable Overflow");
		return 0; // added
	}
	back_table_type* foretable_item = &foretable[index];
	foretable_item->xh = xh;
	foretable_item->xl = xl;
	foretable_item->chtab_id = chtab_id;
	foretable_item->id = id - 1;
	image_type* image = get_image(chtab_id, id - 1);
	if (image == NULL) {
		return 0;
	}
	foretable_item->y = ybottom - image->h/*height*/ + 1;
	foretable_item->blit = blit;
	if (draw_mode) {
		draw_back_fore(1, index);
	}
	++foretable_count;
	return 1;
}

// seg008:113A
int add_midtable(short chtab_id, int id, sbyte xh, sbyte xl, int ybottom, int blit, byte peel) {
	if (id == 0) {
		return 0;
	}
	word index = midtable_count;
	if (index >= 50) {
		show_dialog("MidTable Overflow");
		return 0; // added
	}
	midtable_type* midtable_item = &midtable[index];
	midtable_item->xh = xh;
	midtable_item->xl = xl;
	midtable_item->chtab_id = chtab_id;
	midtable_item->id = id - 1;
	image_type* image = get_image(chtab_id, id - 1);
	if (image == NULL) {
		return 0;
	}
	midtable_item->y = ybottom - image->h/*height*/ + 1;
	if (obj_direction == dir_0_right && chtab_flip_clip[chtab_id] != 0) {
		blit += 0x80;
	}
	midtable_item->blit = blit;
	midtable_item->peel = peel;
	midtable_item->clip.left = obj_clip_left;
	midtable_item->clip.right = obj_clip_right;
	midtable_item->clip.top = obj_clip_top;
	midtable_item->clip.bottom = obj_clip_bottom;
	if (draw_mode) {
		draw_mid(index);
	}
	++midtable_count;
	return 1;
}

// seg008:1208
void add_peel(int left,int right,int top,int height) {
	rect_type rect;
	if (peels_count >= 50) {
		show_dialog("Peels OverFlow");
		return /*0*/; // added
	}
	rect.left = left;
	rect.right = right;
	rect.top = top;
	rect.bottom = top + height;
	peels_table[peels_count] = read_peel_from_screen(&rect);
	peels_count++;
}

// seg008:1254
void add_wipetable(sbyte layer,short left,short bottom,sbyte height,short width,sbyte color) {
	word index = wipetable_count;
	if (index >= 300) {
		show_dialog("WipeTable Overflow");
		return /*0*/; // added
	}
	wipetable_type* wipetable_item = &wipetable[index];
	wipetable_item->left = left;
	wipetable_item->bottom = bottom + 1;
	wipetable_item->height = height;
	wipetable_item->width = width;
	wipetable_item->color = color;
	wipetable_item->layer = layer;
	if (draw_mode) {
		draw_wipe(index);
	}
	++wipetable_count;
}

// seg008:12BB
void draw_table(int which_table) {
	short count = table_counts[which_table];
	for (short index = 0; index < count; ++index) {
		if (which_table == 3) {
			draw_mid(index);
		} else {
			draw_back_fore(which_table, index);
		}
	}
}

// seg008:12FE
void draw_wipes(int which) {
	word count = wipetable_count;
	for (word index = 0; index < count; ++index) {
		if (which == wipetable[index].layer) {
			draw_wipe(index);
		}
	}
}

// seg008:133B
void draw_back_fore(int which_table,int index) {
	image_type* image;
	image_type* mask;
	back_table_type* table_entry;
	if (which_table == 0) {
		table_entry = &backtable[index];
	} else /* if (which_table == 1) this is always true */ {
		table_entry = &foretable[index];
	}
	image = mask = get_image(table_entry->chtab_id, table_entry->id);
	/*
	if ((graphics_mode == gmCga || graphics_mode == gmHgaHerc) &&
		chtab_shift[table_entry->chtab_id] == 0) {
		chtab_type* chtab = chtab_addrs[table_entry->chtab_id];
		mask = chtab->images[chtab->n_images / 2 + table_entry->id];
	}
	*/

	draw_image(image, mask, table_entry->xh * 8 + table_entry->xl, table_entry->y, table_entry->blit);
}


SDL_Surface* hflip(SDL_Surface* input) {
	int width = input->w;
	int height = input->h;

	// The simplest way to create a surface with same format as input:
	SDL_Surface* output = SDL_ConvertSurface(input, input->format, 0);
	SDL_SetSurfacePalette(output, input->format->palette);
	// The copied image will be overwritten anyway.
	if (output == NULL) {
		sdlperror("hflip: SDL_ConvertSurface");
		quit(1);
	}

	SDL_SetSurfaceBlendMode(input, SDL_BLENDMODE_NONE);
	// Temporarily turn off alpha and colorkey on input. So we overwrite the output image.
	SDL_SetColorKey(input, SDL_FALSE, 0);
	SDL_SetColorKey(output, SDL_FALSE, 0);
	SDL_SetSurfaceAlphaMod(input, 255);

	for (int source_x = 0, target_x = width-1; source_x < width; ++source_x, --target_x) {
		SDL_Rect srcrect = {source_x, 0, 1, height};
		SDL_Rect dstrect = {target_x, 0, 1, height};
		if (SDL_BlitSurface(input/*32*/, &srcrect, output, &dstrect) != 0) {
			sdlperror("hflip: SDL_BlitSurface");
			quit(1);
		}
	}

	return output;
}


// seg008:140C
void draw_mid(int index) {
	image_type*mask;
//	word image_flipped;

	word blit_flip = 0;
	word need_free_image = 0;
	word need_free_mask = 0;
	midtable_type* midtable_entry = &midtable[index];
	word image_id = midtable_entry->id;
	word chtab_id = midtable_entry->chtab_id;
	image_type* image = mask = get_image(chtab_id, image_id);
	/*
	if ((graphics_mode == gmCga || graphics_mode == gmHgaHerc) && chtab_shift[chtab_id]) {
		mask = chtab_addrs[chtab_id]->images[image_id + chtab_addrs[chtab_id]->n_images / 2];
	}
	*/
	short xpos = midtable_entry->xh * 8 + midtable_entry->xl;
	short ypos = midtable_entry->y;
	word blit = midtable_entry->blit;
	if (blit & 0x80) {
		blit_flip = 0x8000;
		blit &= 0x7F;
	}

	if (chtab_flip_clip[chtab_id]) {
		set_clip_rect(&midtable_entry->clip);
		if (chtab_id != id_chtab_0_sword) {
			xpos = calc_screen_x_coord(xpos);
		}
	}
	if (blit_flip) {
		xpos -= image->w/*width*/;
		// for this version:
		need_free_image = 1;
		image = hflip(image);
	}

	if (midtable_entry->peel) {
		add_peel(round_xpos_to_byte(xpos, 0), round_xpos_to_byte(image->w/*width*/ + xpos, 1), ypos, image->h/*height*/);
	}
	//printf("Midtable: drawing (chtab %d, image %d) at (x=%d, y=%d)\n",chtab_id,image_id,xpos,ypos); // debug

	draw_image(image, mask, xpos, ypos, blit);

	if (chtab_flip_clip[chtab_id]) {
		reset_clip_rect();
	}
	if (need_free_image) {
		//free(image);
		SDL_FreeSurface(image);
	}
	if (need_free_mask) {
		free(mask);
	}
}

// seg008:167B
void draw_image(image_type* image,image_type* mask,int xpos,int ypos,int blit) {
	rect_type rect;
	switch (blit) {
		case blitters_10h_transp:
			draw_image_transp(image, mask, xpos, ypos);
		break;
		case blitters_9_black:
			method_6_blit_img_to_scr(mask, xpos, ypos, blitters_9_black);
		break;
		case blitters_11_mono_bg:
			method_6_blit_img_to_scr(mask, xpos, ypos, blitters_11_mono_bg);
		break;
		case blitters_0_no_transp:
		case blitters_0_no_transp_tile:
		case blitters_2_or:
		case blitters_3_xor:
			method_6_blit_img_to_scr(image, xpos, ypos, blit);
		break;
		default:
			if (blit >= 0x100) {
				method_6_blit_img_to_scr(mask, xpos, ypos, blit);
			} else {
				method_3_blit_mono(image, xpos, ypos, 0, blit & 0xBF);
			}
		break;
	}
	if (need_drects) {
		rect.left = rect.right = xpos;
		rect.right += image->w;
		rect.top = rect.bottom = ypos;
		rect.bottom += image->h;
		add_drect(&rect);
	}
}

// seg008:1730
void draw_wipe(int index) {
	rect_type rect;
	wipetable_type* ptr = &wipetable[index];
	rect.left = rect.right = ptr->left;
	rect.right += ptr->width;
	rect.bottom = rect.top = ptr->bottom;
	rect.top -= ptr->height;
	draw_rect_rgb(&rect, bg_colour); // ignores the colour in the wipetable entry
	if (need_drects) {
		add_drect(&rect);
	}
}

int egg_fram_fore[9] = {171, 172, 173, 174, 174, 175, 177, 176, 178};
void draw_egg() {
	add_wipetable(0, (draw_xh*8)+20, draw_bottom_y, 60, 4*8, 0);
	add_foretable(id_chtab_6_environment, egg_fram_fore[((curr_modifier-1)/2)%10], draw_xh, 15, draw_main_y - 5, blitters_10h_transp, 0);
}


// data:4E8C
word gate_top_y;
// data:4CB6
word gate_openness;
// data:436C
word gate_bottom_y;

// seg008:178E
void calc_gate_pos() {
	gate_top_y = draw_bottom_y - 62;
	gate_openness = (MIN(modifier_left, 188) >> 2) + 1;
	gate_bottom_y = draw_main_y - gate_openness;
}
void calc_left_gate_pos() {
	gate_top_y = draw_bottom_y - 62;
	gate_openness = (MIN(curr_modifier, 188) >> 2) + 1;
	gate_bottom_y = draw_main_y - gate_openness;
}

// data:2785
const byte door_fram_slice[] = {67, 59, 58, 57, 56, 55, 54, 53, 52};
// seg008:17B7
void draw_gate_back() {
	draw_tile_wipe(63);
	calc_gate_pos();
	if (gate_bottom_y + 12 < draw_main_y) {
		add_backtable(id_chtab_6_environment, 50 /*gate bottom with B*/, draw_xh, 0, gate_bottom_y, blitters_10h_transp, 0);
	} else {
		// The following line (erroneously) erases the top-right of the tile below-left (because it is drawn non-transparently).
		// -- But it draws something that was already drawn! (in draw_tile_right()).
		//add_backtable(id_chtab_6_environment, tile_table[tiles_4_gate].right_id, draw_xh, 0,
		//              tile_table[tiles_4_gate].right_y + draw_main_y, blitters_10h_transp, 0);
		// And this line tries to fix it. But it fails if it was a gate or a pillar.
		//if (can_see_bottomleft()) draw_tile_topright();
#ifdef FIX_GATE_DRAWING_BUG
		if (fixes->fix_gate_drawing_bug) {
			draw_tile_anim_topright(); // redraw the erased top-right section of the gate below-left
		}
#endif
		// The following 3 lines draw things that are drawn after this anyway.
		draw_tile_bottom(0);
		draw_loose(0);
		draw_tile_base();
		add_backtable(id_chtab_6_environment, 51 /*gate bottom*/, draw_xh, 0, gate_bottom_y - 2, blitters_10h_transp, 0);
	}
	short ybottom = gate_bottom_y - 12;
	if (ybottom < 192) {
		for (; ybottom >= 0 && ybottom > 7 && ybottom - 7 > gate_top_y; ybottom -= 8) {
			add_backtable(id_chtab_6_environment, 52 /*gate slice 8px*/, draw_xh, 0, ybottom, blitters_10h_transp, 0);
		}
	}
	word gate_frame = ybottom - gate_top_y + 1;
	if (gate_frame > 0 && gate_frame < 9) {
		add_backtable(id_chtab_6_environment, door_fram_slice[gate_frame], draw_xh, 0, ybottom, blitters_10h_transp, 0);
	}
}
void draw_left_gate_back() {
	int x_offset = 8;//-24
	add_wipetable(0, (draw_xh*8)+x_offset, draw_bottom_y, 63, 4*8, 0);
	calc_left_gate_pos();
	if (gate_bottom_y + 12 < draw_main_y) {
		add_backtable(id_chtab_6_environment, 50 /*gate bottom with B*/, draw_xh, x_offset, gate_bottom_y, blitters_10h_transp, 0);
	} else {
		// The following line (erroneously) erases the top-right of the tile below-left (because it is drawn non-transparently).
		// -- But it draws something that was already drawn! (in draw_tile_right()).
		//add_backtable(id_chtab_6_environment, tile_table[tiles_4_gate].right_id, draw_xh, 0/*x_offset*/,
		//              tile_table[tiles_4_gate].right_y + draw_main_y, blitters_10h_transp, 0);
		// And this line tries to fix it. But it fails if it was a gate or a pillar.
		//if (can_see_bottomleft()) draw_tile_topright();
#ifdef FIX_GATE_DRAWING_BUG
		if (fixes->fix_gate_drawing_bug) {
			draw_tile_anim_topright(); // redraw the erased top-right section of the gate below-left
		}
#endif
		// The following 3 lines draw things that are drawn after this anyway.
		draw_tile_bottom(0);
		draw_loose(0);
		draw_tile_base();
		add_backtable(id_chtab_6_environment, 51 /*gate bottom*/, draw_xh, x_offset, gate_bottom_y - 2, blitters_10h_transp, 0);
	}
	short ybottom = gate_bottom_y - 12;
	if (ybottom < 192) {
		for (; ybottom >= 0 && ybottom > 7 && ybottom - 7 > gate_top_y; ybottom -= 8) {
			add_backtable(id_chtab_6_environment, 52 /*gate slice 8px*/, draw_xh, x_offset, ybottom, blitters_10h_transp, 0);
		}
	}
	word gate_frame = ybottom - gate_top_y + 1;
	if (gate_frame > 0 && gate_frame < 9) {
		add_backtable(id_chtab_6_environment, door_fram_slice[gate_frame], draw_xh, x_offset, ybottom, blitters_10h_transp, 0);
	}
}

// seg008:18BE
void draw_gate_fore() {
	int x_offset = 0;
	calc_gate_pos();
	add_foretable(id_chtab_6_environment, 51 /*gate bottom*/, draw_xh, x_offset, gate_bottom_y - 2, blitters_10h_transp, 0);
	short ybottom = gate_bottom_y - 12;
	if (ybottom < 192) {
		for (; ybottom >= 0 && ybottom > 7 && ybottom - 7 > gate_top_y; ybottom -= 8) {
			add_foretable(id_chtab_6_environment, 52 /*gate slice 8px*/, draw_xh, x_offset, ybottom, blitters_10h_transp, 0);
		}
	}
}
void draw_left_gate_fore() {
	int x_offset = 8;
	calc_left_gate_pos();
	add_foretable(id_chtab_6_environment, 51 /*gate bottom*/, draw_xh, x_offset, gate_bottom_y - 2, blitters_10h_transp, 0);
	short ybottom = gate_bottom_y - 12;
	if (ybottom < 192) {
		for (; ybottom >= 0 && ybottom > 7 && ybottom - 7 > gate_top_y; ybottom -= 8) {
			add_foretable(id_chtab_6_environment, 52 /*gate slice 8px*/, draw_xh, x_offset, ybottom, blitters_10h_transp, 0);
		}
	}
}

// seg008:1937
void alter_mods_allrm() {

#ifdef USE_COLORED_TORCHES
	memset(torch_colors, 0, sizeof(torch_colors));
#endif

	// level.used_rooms is 25 on some levels. Limit it to the actual number of rooms.
	if (level.used_rooms > 24) level.used_rooms = 24;

	for (word room = 1; room <= level.used_rooms; room++) {
		get_room_address(room);
		room_L = level.roomlinks[room-1].left;
		room_R = level.roomlinks[room-1].right;
		for (word tilepos = 0; tilepos < 30; tilepos++) {
			load_alter_mod(tilepos);
		}
	}
}

// seg008:198E
void load_alter_mod(int tilepos) {
	word wall_to_right;
	word wall_to_left;
	byte* curr_tile_modif = tilepos + curr_room_modif;
	word tiletype = curr_room_tiles[tilepos] & 0x1F;
	switch (tiletype) {
		case tiles_4_gate:
			if (*curr_tile_modif == 1) {
				*curr_tile_modif = 188;
			} else {
				*curr_tile_modif = 0;
			}
			break;
		case tiles_11_loose:
			*curr_tile_modif = 0;
			break;
		case tiles_10_potion:
			*curr_tile_modif <<= 3;
#ifdef USE_COPYPROT
			if (current_level == 15) {
				// Copy protection
				if (copyprot_room[copyprot_plac] == loaded_room &&
					copyprot_tile[copyprot_plac] == tilepos
				) {
					*curr_tile_modif = 6 << 3; // place open potion
				}
			}
#endif
			break;


		case tiles_20_wall:
		{
			byte stored_modif = *curr_tile_modif;
			//*curr_tile_modif <<= 7; // original: "no blue" mod becomes most significant bit //*/
			if (stored_modif == 1) *curr_tile_modif = 0x80;
			else *curr_tile_modif = (stored_modif << 4);
			// retain three bits more information:
			// most significant bit:       1 ==> "no blue"
			// next 3 bits:                for displaying various fake tiles (invisible walls)
			// ..
			// least significant 2 bits:   wall to left/right?
		}
			// fallthrough: not done yet, just moving to another scope
			goto label_wall_continued;

#ifdef USE_FAKE_TILES
		// Need to deal with the possibility that certain tiles can impersonate walls
		case tiles_0_empty:
		case tiles_1_floor:
			if ((*curr_tile_modif & 7) != 5) break;
			// if tile is a fake wall, fall through
#endif

			label_wall_continued:
		{
			// Here, ahead of time, we define the condition for a neighbouring tile to be seen as a wall connection
			#ifndef USE_FAKE_TILES
			#define read_adj_tile_modif_in_curr_room()      // nop; access to modifier of adjacent tiles is not needed
			#define read_adj_tile_modif_in_external_room()  // nop
			#define WALL_CONNECTION_CONDITION (adj_tile == tiles_20_wall)

			#else // #ifdef USE_FAKE_TILES
			// When determining wall connections for fake walls, we need access to the tile modifier of adjacent tiles
			#define read_adj_tile_modif_in_curr_room() \
			int adj_tile_modif = curr_room_modif[adj_tile_index];
			#define read_adj_tile_modif_in_external_room() \
			int adj_tile_modif = level.bg[adj_tile_index];
			// Now redefine the condition for what tiletype / modifier combination counts as a valid "wall"
			#define WALL_CONNECTION_CONDITION (                                                                       \
				(adj_tile == tiles_20_wall && adj_tile_modif != 4 && (adj_tile_modif >> 4) != 4 &&                    \
				             adj_tile_modif != 6 && (adj_tile_modif >> 4) != 6) ||                                    \
				(adj_tile == tiles_0_empty && (adj_tile_modif == 5 || adj_tile_modif == 13 ||                         \
				             (adj_tile_modif >= 50 && adj_tile_modif <= 53))) ||                                      \
				(adj_tile == tiles_1_floor && (adj_tile_modif == 5 || adj_tile_modif == 13 ||                         \
				             (adj_tile_modif >= 50 && adj_tile_modif <= 53))))
			#endif

			if (graphics_mode != gmCga && graphics_mode != gmHgaHerc) {
				wall_to_right = 1;
				wall_to_left = 1;
				int adj_tile_index, adj_tile;
				if (tilepos % 10 == 0) {
					if (room_L) {
						adj_tile_index = 30*(room_L-1)+tilepos+9;
						adj_tile = (level.fg[adj_tile_index] & 0x1F);
						read_adj_tile_modif_in_external_room(); // only executed when fake tiles are enabled
						wall_to_left = WALL_CONNECTION_CONDITION;
					}
				} else {
					adj_tile_index = tilepos-1;
					adj_tile = (curr_room_tiles[adj_tile_index] & 0x1F);
					read_adj_tile_modif_in_curr_room();
					wall_to_left = WALL_CONNECTION_CONDITION;
				}
				if (tilepos % 10 == 9) {
					if (room_R) {
						adj_tile_index = 30*(room_R-1)+tilepos-9;
						adj_tile = (level.fg[adj_tile_index] & 0x1F);
						read_adj_tile_modif_in_external_room();
						wall_to_right = WALL_CONNECTION_CONDITION;
					}
				} else {
					adj_tile_index = tilepos+1;
					adj_tile = (curr_room_tiles[adj_tile_index] & 0x1F);
					read_adj_tile_modif_in_curr_room();
					wall_to_right = WALL_CONNECTION_CONDITION;
				}

				#ifdef USE_FAKE_TILES
				if (tiletype == tiles_1_floor || tiletype == tiles_0_empty) {
					if (wall_to_left && wall_to_right) {
						*curr_tile_modif = 53;
					} else if (wall_to_left) {
						*curr_tile_modif = 52;
					} else if (wall_to_right) {
						*curr_tile_modif = 51;
					}
					break;
				}
				#endif

				if (wall_to_left && wall_to_right) {
					*curr_tile_modif |= 3;
				} else if (wall_to_left) {
					*curr_tile_modif |= 2;
				} else if (wall_to_right) {
					*curr_tile_modif |= 1;
				}
			} else {
				*curr_tile_modif = 3;
			}
		}
			break;

#ifdef USE_COLORED_TORCHES
		/*case tiles_19_torch:
		case tiles_30_torch_with_debris:
			torch_colors[loaded_room][tilepos] = *curr_tile_modif;
			*curr_tile_modif = 0;
		break;*/
#endif
	}
}

// seg008:1AF8
void draw_moving() {
	draw_mobs();
	draw_people();
	redraw_needed_tiles();
}

// seg008:1B06
void redraw_needed_tiles() {
	load_leftroom();
	draw_objtable_items_at_tile(30);
	for (drawn_row = 3; drawn_row--; ) {
		load_rowbelow();
		draw_bottom_y = 63 * drawn_row + 65;
		draw_main_y = draw_bottom_y - 3;
		for (drawn_col = 0; drawn_col < 10; ++drawn_col) {
			load_curr_and_left_tile();
			redraw_needed(tbl_line[drawn_row] + drawn_col);
		}
	}
	word saved_drawn_room = drawn_room;
	drawn_room = room_A;
	load_room_links();
	load_leftroom();
	drawn_row = 2;
	load_rowbelow();
	for (drawn_col = 0; drawn_col < 10; ++drawn_col) {
		load_curr_and_left_tile();
		draw_main_y = -1;
		draw_bottom_y = 2;
		redraw_needed_above(drawn_col);
	}
	drawn_room = saved_drawn_room;
	load_room_links();
	draw_objtable_items_at_tile(-1);
}

// seg008:1BCB
void draw_tile_wipe(byte height) {
	add_wipetable(0, draw_xh*8, draw_bottom_y, height, 4*8, 0);
}

// seg008:1BEB
void draw_tables() {
	water_tick = (water_tick + 1) % 4;

	drects_count = 0;
	current_target_surface = offscreen_surface;
	if (is_blind_mode) {
		draw_rect_rgb(&rect_top, bg_colour);
	}
	restore_peels();
	draw_wipes(0);
	draw_table(0); // backtable
	//printf("midtable_count = %d\n", midtable_count); // debug
#ifdef FIX_BLACK_RECT // I'm not sure if this is the best way to fix this.
	draw_wipes(1);
#endif
	draw_table(3); // midtable
	draw_wipes(1);
	draw_table(1); // foretable
	current_target_surface = onscreen_surface_;
	show_copyprot(1);
}

// seg008:1C4E
void restore_peels() {
	peel_type* peel;
	while (peels_count) {
		peels_count--;
		peel = peels_table[peels_count];
		if (need_drects) {
			add_drect(&peel->rect);
		}
		restore_peel(peel);
	}
	peels_count = 0;
}

// seg008:1C8F
void add_drect(rect_type *source) {
	for (short index = 0; index < drects_count; ++index) {
		rect_type target_rect; // Dummy output argument, we care only about whether the intersection is non-empty.
		if (intersect_rect(&target_rect, shrink2_rect(&target_rect, source, -1, -1), &drects[index])) {
			rect_type* current_drect = &drects[index];
			union_rect(current_drect, current_drect, source);
			return;
		}
	}
	if (drects_count >= 30){
		show_dialog("DRects Overflow");
		return /*0*/; // added
	}
	drects[drects_count] = *source;
	drects_count++;
}

// seg008:1D29
void draw_leveldoor() {
	short ybottom = draw_main_y - 13;
	leveldoor_right = (draw_xh<<3)+48;
	if (custom->tbl_level_type[current_level]) leveldoor_right += 8;
	//add_backtable(id_chtab_6_environment, 99, draw_xh + 1, 0, ybottom, blitters_0_no_transp_tile, 0); // 99: leveldoor stairs bottom
	/*if (modifier_left) {
		if (level.start_room != drawn_room) {
			add_backtable(id_chtab_6_environment, 144, draw_xh + 1, 0, ybottom - 4, blitters_0_no_transp_tile, 0); // 144 level door stairs
		}
		else {
			short leveldoor_width = (custom->tbl_level_type[current_level] == 0) ? 39 : 48;
			sbyte x_low = (custom->tbl_level_type[current_level] == 0) ? 2 : 0; // dungeon level doors are shifted 2px to the right
			add_wipetable(0, 8*(draw_xh + 1) + x_low, ybottom - 4, 45, leveldoor_width, 0);
		}
	}*/
	//leveldoor_ybottom = ybottom - (modifier_left & 3) - 48;
	//short y = ybottom - modifier_left;
	//do { // runs at least once
	leveldoor_height = modifier_left;
	add_backtable(id_chtab_6_environment, 165, draw_xh + 1, 0, ybottom, blitters_10h_transp, 0); // 33 special leveldoor value to be handled in get_image()
	//	if (y > leveldoor_ybottom) leveldoor_ybottom += 4;
	//	else break;
	//} while (true);
	//add_backtable(id_chtab_6_environment, 34, draw_xh + 1, 0, draw_main_y - 64, blitters_0_no_transp_tile, 0); // 34 level door top
}

// seg008:1E0C
void get_room_address(int room) {
	//if (room < 0 || room > 24) printf("Tried to access room %d, not in 0..24.\n", room);
	loaded_room = (word) room;
	if (room) {
		curr_room_tiles = &level.fg[(room-1)*30];
		curr_room_modif = &level.bg[(room-1)*30];
	}
}

// data:286A
const word floor_left_overlay[] = {32, 151, 151, 150, 150, 151, 32, 32};

// seg008:1E3A
void draw_floor_overlay() {
#ifdef FIX_BIGPILLAR_CLIMB
	if (tile_left != tiles_0_empty) {
		// Bug: When climbing up to a floor with a big pillar top behind, turned right, Kid sees through floor.
		// The bigpillar_top tile should be treated similarly to an empty tile here.
		if (!fixes->fix_bigpillar_climb || (tile_left != tiles_9_bigpillar_top)) {
			return;
		}
	}
#else
	if (tile_left != tiles_0_empty) return;
#endif
	if (curr_tile == tiles_1_floor ||
		curr_tile == tiles_3_pillar ||
		curr_tile == tiles_5_stuck //||
		//curr_tile == tiles_19_torch
	) {
		// frames 137..144: climb
		// index overflow here?
		if (Kid.frame >= frame_137_climbing_3 && Kid.frame <= frame_144_climbing_10) {
			add_midtable(id_chtab_6_environment, floor_left_overlay[Kid.frame - 137], draw_xh, 0, (curr_tile == tiles_5_stuck) + draw_main_y, blitters_10h_transp, 0);
		} else if (Char.frame >= frame_137_climbing_3 && Char.frame <= frame_144_climbing_10) { // shadow needs to climb too
			add_midtable(id_chtab_6_environment, floor_left_overlay[Char.frame - 137], draw_xh, 0, (curr_tile == tiles_5_stuck) + draw_main_y, blitters_10h_transp, 0);
		} else {
			// triggered by 02-random-broken
			printf("draw_floor_overlay: attempted to draw floor overlay with frame %d not in 137..144\n", Kid.frame);
			//quit(1);
		}
		ptr_add_table = &add_midtable;
		draw_tile_bottom(0);
		ptr_add_table = &add_backtable;
	} else {
		draw_other_overlay();
	}
}

// seg008:1EB5
void draw_other_overlay() {
	byte tiletype;
	byte modifier;
	if (tile_left == tiles_0_empty) {
		ptr_add_table = &add_midtable;
		draw_tile2();
	} else if (curr_tile != tiles_0_empty && drawn_col > 0 &&
		get_tile_to_draw(drawn_room, drawn_col - 2, drawn_row, &tiletype, &modifier, tiles_0_empty) == tiles_0_empty
	) {
		ptr_add_table = &add_midtable;
		draw_tile2();
		ptr_add_table = &add_backtable;
		draw_tile2();
		tile_object_redraw[tbl_line[drawn_row] + drawn_col] = 0xFF;
	}
	ptr_add_table = &add_backtable;
}

// seg008:1F48
void draw_tile2() {
	draw_tile_right();
	draw_tile_anim_right();
	draw_tile_base();
	draw_tile_anim();
	draw_tile_bottom(0);
	draw_loose(0);
}

// seg008:1F67
void draw_objtable_items_at_tile(byte tilepos) {
	//printf("draw_objtable_items_at_tile(%d)\n",tilepos); // debug
	short obj_count = objtable_count;
	if (obj_count) {
		n_curr_objs = 0;
		for (short obj_index = obj_count - 1; obj_index >= 0; --obj_index) {
			if (objtable[obj_index].tilepos == tilepos) {
				curr_objs[n_curr_objs] = obj_index;
				n_curr_objs++;
			}
		}
		if (n_curr_objs) {
			sort_curr_objs();
			for (short obj_index = 0; obj_index < n_curr_objs; ++obj_index) {
				draw_objtable_item(curr_objs[obj_index]);
			}
		}
	}
}

// seg008:1FDE
void sort_curr_objs() {
	short swapped;
	// bubble sort
	short last = n_curr_objs - 1;
	do {
		swapped = 0;
		for (short index = 0; index < last; ++index) {
			if (compare_curr_objs(index, index + 1)) {
				short temp = curr_objs[index];
				curr_objs[index] = curr_objs[index + 1];
				curr_objs[index + 1] = temp;
				swapped = 1;
			}
		}
		// --last ?
	} while (swapped);
}

// seg008:203C
int compare_curr_objs(int index1,int index2) {
	short obj_index1 = curr_objs[index1];
	if (objtable[obj_index1].obj_type == 1) return 1;
	short obj_index2 = curr_objs[index2];
	if (objtable[obj_index2].obj_type == 1) return 0;
	if (objtable[obj_index1].obj_type == 0x80 &&
		objtable[obj_index2].obj_type == 0x80
	) {
		return (objtable[obj_index1].y < objtable[obj_index2].y);
	} else {
		return (objtable[obj_index1].y > objtable[obj_index2].y);
	}
	return 1;
}

// seg008:20CA
void draw_objtable_item(int index) {
	switch (load_obj_from_objtable(index)) {
		case 0: // Kid
		case 4: // mirror image
			//printf("index = %d, obj_id = %d\n", index, obj_id); // debug
			if (obj_id == 0xFF) return;
			// the Kid blinks a bit after uniting with shadow
			if (united_with_shadow && (united_with_shadow % 2) == 0) goto shadow;
			// fallthrough!
		case 2: // Guard
		case 3: // sword
		case 5: // hurt splash
			add_midtable(obj_chtab, obj_id + 1, obj_xh, obj_xl, obj_y, blitters_10h_transp, 1);
		break;
		case 1: // shadow
		shadow:
			if (united_with_shadow == 2) {
				play_sound(sound_41_end_level_music); // united with shadow
			}
			add_midtable(id_chtab_10_shadow, obj_id + 1, obj_xh, obj_xl, obj_y, blitters_10h_transp, 1);
			//add_midtable(obj_chtab, obj_id + 1, obj_xh, obj_xl, obj_y, blitters_2_or, 1);
			//add_midtable(obj_chtab, obj_id + 1, obj_xh, obj_xl + 1, obj_y, blitters_3_xor, 1);
		break;
		case 0x80: // loose floor
			obj_direction = dir_FF_left;
			add_midtable(obj_chtab, loose_fram_left[obj_id], obj_xh, obj_xl, obj_y - 3, blitters_10h_transp, 1);
			add_midtable(obj_chtab, loose_fram_bottom[obj_id], obj_xh, obj_xl, obj_y, 0, 1);
			add_midtable(obj_chtab, loose_fram_right[obj_id], obj_x + 4, obj_xl, obj_y - 1, blitters_10h_transp, 1);
		break;
	}
}

// seg008:2228
int load_obj_from_objtable(int index) {
	objtable_type* curr_obj = &objtable[index];
	obj_xh = obj_x = curr_obj->xh;
	obj_xl = curr_obj->xl;
	obj_y = curr_obj->y;
	obj_id = curr_obj->id;
	obj_chtab = curr_obj->chtab_id;
	obj_direction = curr_obj->direction;
	obj_clip_top = curr_obj->clip.top;
	obj_clip_bottom = curr_obj->clip.bottom;
	obj_clip_left = curr_obj->clip.left;
	obj_clip_right = curr_obj->clip.right;
	return curr_obj->obj_type;
}

// seg008:228A
void draw_people() {
	check_mirror();
	draw_kid();
	draw_guard();
	reset_obj_clip();
	draw_hp();
}

// seg008:22A2
void draw_kid() {
	if (Kid.room != 0 && Kid.room == drawn_room) {
		add_kid_to_objtable();
		if (hitp_delta < 0) {
			draw_hurt_splash();
		}
		add_sword_to_objtable();
	}
}

// seg008:22C9
void draw_guard() {
	if (Guard.direction != dir_56_none && Guard.room == drawn_room) {
		add_guard_to_objtable();
		if (guardhp_delta < 0) {
			draw_hurt_splash();
		}
		add_sword_to_objtable();
	}
}

// seg008:22F0
void add_kid_to_objtable() {
	//printf("add_kid_to_objtable\n");
	loadkid();
	load_fram_det_col();
	load_frame_to_obj();
	stuck_lower();
	set_char_collision();
	set_objtile_at_char();
	redraw_at_char();
	redraw_at_char2();
	clip_char();
	add_objtable(0); // Kid
}

// seg008:2324
void add_guard_to_objtable() {
	word obj_type;
	loadshad();
	load_fram_det_col();
	load_frame_to_obj();
	stuck_lower();
	set_char_collision();
	set_objtile_at_char();
	redraw_at_char();
	redraw_at_char2();
	clip_char();
	if (Char.charid == charid_1_shadow) {
		// Special event: shadow is clipped: may appear only right from the mirror
		if (current_level == /*4*/ custom->mirror_level && Char.room == /*4*/ custom->mirror_room) {
			obj_clip_left = 137;
			obj_clip_left += (custom->mirror_column - 4) * 32; // added
		}
		obj_type = 1; // shadow
	} else {
		obj_type = 2; // Guard
	}
	add_objtable(obj_type);
}

// seg008:2388
void add_objtable(byte obj_type) {
	//printf("in add_objtable: objtable_count = %d\n",objtable_count); // debug
	word index = objtable_count++;
	//printf("in add_objtable: objtable_count = %d\n",objtable_count); // debug
	if (index >= 50) {
		show_dialog("ObjTable Overflow");
		return /*0*/; // added
	}
	objtable_type* entry_addr = &objtable[index];
	entry_addr->obj_type = obj_type;
	x_to_xh_and_xl(obj_x, &entry_addr->xh, &entry_addr->xl);
	entry_addr->y = obj_y;
	entry_addr->clip.top = obj_clip_top;
	entry_addr->clip.bottom = obj_clip_bottom;
	entry_addr->clip.left = obj_clip_left;
	entry_addr->clip.right = obj_clip_right;
	entry_addr->chtab_id = obj_chtab;
	entry_addr->id = obj_id;
	entry_addr->direction = obj_direction;
	mark_obj_tile_redraw(index);
}

// seg008:2423
void mark_obj_tile_redraw(int index) {
	//printf("mark_obj_tile_redraw: obj_tile = %d\n", obj_tile); // debug
	objtable[index].tilepos = obj_tilepos;
	if (obj_tilepos < 30) {
		tile_object_redraw[obj_tilepos] = 1;
	}
}

// seg008:2448
void load_frame_to_obj() {
	word chtab_base = id_chtab_2_kid;
	reset_obj_clip();
	load_frame();
	obj_direction = Char.direction;
	obj_id = cur_frame.image;
	// top 6 bits of sword are the chtab
	obj_chtab = chtab_base + (cur_frame.sword >> 6);
	obj_x = (char_dx_forward(cur_frame.dx) << 1) - 116;
	obj_y = cur_frame.dy + Char.y;
	if ((sbyte)(cur_frame.flags ^ obj_direction) >= 0) {
		// 0x80: even/odd pixel
		++obj_x;
	}
}

// seg008:24A8
void show_time() {
	char sprintf_temp[40];
	word rem_sec;
	if (Kid.alive < 0 &&
		#ifdef FREEZE_TIME_DURING_END_MUSIC
		(!(fixes->enable_freeze_time_during_end_music && next_level != current_level)) &&
		#endif
		#ifdef ALLOW_INFINITE_TIME
		// prevent overflow
		(!(rem_min == INT16_MIN && rem_tick == 1)) &&
		#endif
		rem_min != 0 &&
		(current_level < /*13*/ custom->victory_stops_time_level || (current_level == /*13*/ custom->victory_stops_time_level && leveldoor_open == 0)) &&
		current_level < 15
	) {
		// Time passes
		--rem_tick;
		if (rem_tick == 0) {
			rem_tick = 719; // 720=12*60 ticks = 1 minute
			--rem_min;
#ifndef ALLOW_INFINITE_TIME
			if (rem_min != 0 && (rem_min <= 5 || rem_min % 5 == 0)) {
				is_show_time = 1;
			}
#else
			if (rem_min > 0 && (rem_min <= 5 || rem_min % 5 == 0)) {
				is_show_time = 1;
			} else if (rem_min < 0) {
				is_show_time = ((~rem_min) % 5 == 0 ) ? 1 : 0;
			}
#endif
		} else {
			if (rem_min == 1 && rem_tick % 12 == 0) {
				is_show_time = 1;
				text_time_remaining = 0;
			}
		}
	}
	if (is_show_time && text_time_remaining == 0) {
		text_time_remaining = text_time_total = 24;
		if (rem_min > 0) {
			if (rem_min == 1) {
				rem_sec = (rem_tick + 1) / 12;
				if (rem_sec == 1) {
					strncpy(sprintf_temp, "1 SECOND LEFT", sizeof(sprintf_temp));
					text_time_remaining = text_time_total = 12;
				} else {
					snprintf(sprintf_temp, sizeof(sprintf_temp), "%d SECONDS LEFT", rem_sec);
				}
			} else {
				snprintf(sprintf_temp, sizeof(sprintf_temp), "%d MINUTES LEFT", rem_min);
			}
			display_text_bottom(sprintf_temp);
		} else {

#ifdef ALLOW_INFINITE_TIME
			if (rem_min < 0) {
				if (~rem_min == 0) {
					// don't display time elapsed in the first minute
					text_time_remaining = 0;
					text_time_total = 0;
					sprintf_temp[0] = '\0';
				}
				else if (~rem_min == 1) {
					snprintf(sprintf_temp, sizeof(sprintf_temp), "1 MINUTE PASSED");
				} else {
					snprintf(sprintf_temp, sizeof(sprintf_temp), "%d MINUTES PASSED", ~rem_min);
				}
				display_text_bottom(sprintf_temp);
			}

			else if (rem_min == 0) // may also be negative, don't report "expired" in that case!
#endif

			display_text_bottom("TIME HAS EXPIRED!");
		}
		is_show_time = 0;
	}
}

// seg008:25A8
void show_level() {
#ifdef FIX_LEVEL_14_RESTARTING
	text_time_remaining = text_time_total = 0;
#endif
	char sprintf_temp[38];
	byte disp_level = current_level;
	text_time_remaining = text_time_total = 24;
	snprintf(sprintf_temp, sizeof(sprintf_temp), "LEVEL %d%s", (disp_level+1)/2, disp_level%2?"":" DUEL");
	display_text_bottom(sprintf_temp);
	is_show_time = 1;
	seamless = 0;
}

// seg008:2602
short calc_screen_x_coord(short logical_x) {
	return logical_x*320/280;
}

// seg008:2627
void free_peels() {
	while (peels_count > 0) {
		--peels_count;
		free_peel(peels_table[peels_count]);
	}
}


// seg008:2644
void display_text_bottom(const char* text) {
	draw_rect(&rect_bottom_text, color_0_black);
	show_text(&rect_bottom_text, halign_center, valign_bottom, text);
#ifndef USE_TEXT
	SDL_SetWindowTitle(window_, text);
#endif
}

// seg008:266D
void erase_bottom_text(int arg_0) {
	draw_rect(&rect_bottom_text, color_0_black);
	if (arg_0) {
		text_time_total = 0;
		text_time_remaining = 0;
	}
#ifndef USE_TEXT
	SDL_SetWindowTitle(window_, WINDOW_TITLE);
#endif
}

// Dungeon wall drawing algorithm by HTamas

#define RSET_WALL              7

#define RES_WALL_FACE_MAIN     1    //(face stack main.bmp)
#define RES_WALL_FACE_TOP      2    //(face stack top.bmp)
#define RES_WALL_CENTRE_BASE   3    //(centre stack base.bmp)
#define RES_WALL_CENTRE_MAIN   4    //(centre stack main.bmp)
#define RES_WALL_RIGHT_BASE    5    //(right stack base.bmp)
#define RES_WALL_RIGHT_MAIN    6    //(right stack main.bmp)
#define RES_WALL_SINGLE_BASE   7    //(single stack base.bmp)
#define RES_WALL_SINGLE_MAIN   8    //(single stack main.bmp)
#define RES_WALL_LEFT_BASE     9    //(left stack base.bmp)
#define RES_WALL_LEFT_MAIN    10    //(left stack main.bmp)
#define RES_WALL_DIVIDER1     11    //(divider01.bmp, the broad divider)
#define RES_WALL_DIVIDER2     12    //(divider02.bmp, the narrow divider)
#define RES_WALL_RNDBLOCK     13    //(random block.bmp)
#define RES_WALL_MARK_TL      14    //(mark01.bmp, top left mark)
#define RES_WALL_MARK_BL      15    //(mark02.bmp, bottom left mark)
#define RES_WALL_MARK_TR      16    //(mark03.bmp, top right mark)
#define RES_WALL_MARK_BR      17    //(mark04.bmp, bottom right mark)

#define BLIT_NO_TRANS          0
#define BLIT_OR                2
#define BLIT_XOR               3
#define BLIT_BLACK             9
#define BLIT_TRANS            16

#define GRAPHICS_CGA          1
#define GRAPHICS_HERCULES     2
#define GRAPHICS_EGA          3
#define GRAPHICS_TANDY        4
#define GRAPHICS_VGA          5

#define DESIGN_DUNGEON        0
#define DESIGN_PALACE         1

#define WALL_MODIFIER_SWS     0
#define WALL_MODIFIER_SWW     1
#define WALL_MODIFIER_WWS     2
#define WALL_MODIFIER_WWW     3


// seg008:268F
void wall_pattern(int which_part,int which_table) {
	word bottom_divider; word middle_divider; byte bottom_divider_offset; byte middle_divider_offset;
	// save the value for the sprite insertion method, so that it can be restored
	add_table_type saved_sim = ptr_add_table;
	// set the sprite insertion method based on the arguments
	if (which_table == 0) {
		ptr_add_table = &add_backtable;
	} else {
		ptr_add_table = &add_foretable;
	}
	// save the state of the pseudorandom number generator
	dword saved_prng_state = random_seed;
	// set the new seed
	random_seed = drawn_room + tbl_line[drawn_row] + drawn_col;
	prandom(1); // fetch a random number and discard it
	word is_dungeon = (custom->tbl_level_type[current_level] < DESIGN_PALACE) || custom->enable_wda_in_palace;
	if ( (!is_dungeon) && (graphics_mode== GRAPHICS_VGA) ) {
		// I haven't traced the palace WDA
		//[...]
		if (which_part) {
			// Draw solid colours for the bricks
			add_wipetable(which_table, 8*(draw_xh)    , draw_main_y - 40, 20, 4*8, palace_wall_colors[44 * drawn_row +      drawn_col]);
			add_wipetable(which_table, 8*(draw_xh)    , draw_main_y - 19, 21, 2*8, palace_wall_colors[44 * drawn_row + 11 + drawn_col]);
			add_wipetable(which_table, 8*(draw_xh + 2), draw_main_y - 19, 21, 2*8, palace_wall_colors[44 * drawn_row + 12 + drawn_col]);
			add_wipetable(which_table, 8*(draw_xh)    , draw_main_y     , 19, 1*8, palace_wall_colors[44 * drawn_row + 22 + drawn_col]);
			add_wipetable(which_table, 8*(draw_xh + 1), draw_main_y     , 19, 3*8, palace_wall_colors[44 * drawn_row + 23 + drawn_col]);
			
			// Draw the dividing decals between bricks
			ptr_add_table(id_chtab_7_environmentwall, prandom(2) +  3, draw_xh + 3, 0, draw_main_y - 53, blitters_46h_mono_6, 0);
			ptr_add_table(id_chtab_7_environmentwall, prandom(2) +  6, draw_xh    , 0, draw_main_y - 34, blitters_46h_mono_6, 0);
			ptr_add_table(id_chtab_7_environmentwall, prandom(2) +  9, draw_xh    , 0, draw_main_y - 13, blitters_46h_mono_6, 0);
			ptr_add_table(id_chtab_7_environmentwall, prandom(2) + 12, draw_xh    , 0, draw_main_y     , blitters_46h_mono_6, 0);
		}
		add_wipetable(which_table, 8*draw_xh    , draw_bottom_y   ,  3, 4*8, palace_wall_colors[44 * drawn_row + 33 + drawn_col]);
		ptr_add_table(id_chtab_7_environmentwall, prandom(2) + 15, draw_xh    , 0, draw_bottom_y   , blitters_46h_mono_6, 0);
	} else {
		middle_divider = prandom(1); // 0 = thick middle brick divider, 1 = thin middle brick divider
		middle_divider_offset = prandom(4); // Horizontal render offset for middle brick divider
		
		// Same as above but for bottom brick dividers
		bottom_divider = prandom(1);
		bottom_divider_offset = prandom(4);

		// store the background modifier for the current tile in a local variable
		// apparently, for walls, the modifier stores whether there are adjacent walls
		byte bg_modifier = curr_modifier & 0x7F;
		switch (bg_modifier) {
			case WALL_MODIFIER_WWW: // left and right tiles are walls
				if (which_part != 0) {
					if (prandom(4) == 0) {
						ptr_add_table(RSET_WALL, RES_WALL_RNDBLOCK, draw_xh, 0, draw_bottom_y - 42, BLIT_NO_TRANS, 0);
					}
					ptr_add_table(RSET_WALL, RES_WALL_DIVIDER1 + middle_divider, draw_xh + 1, middle_divider_offset, draw_bottom_y - 21, BLIT_TRANS, 0);
				}
				ptr_add_table(RSET_WALL, RES_WALL_DIVIDER1 + bottom_divider, draw_xh, bottom_divider_offset, draw_bottom_y, BLIT_TRANS, 0);
				if (which_part != 0) {
					if (is_dungeon) {
						if (prandom(4) == 0) {
							draw_right_mark(prandom(3), middle_divider_offset);
						}
						if (prandom(4) == 0) {
							draw_left_mark(prandom(4), middle_divider_offset - middle_divider, bottom_divider_offset - bottom_divider);
						}
					}
				}
				break;
			case WALL_MODIFIER_SWS: // left and right tiles are not walls
				if (is_dungeon) {
					if (which_part != 0) {
						if (prandom(6) == 0) {
							draw_left_mark(prandom(1), middle_divider_offset - middle_divider, bottom_divider_offset - bottom_divider);
						}
					}
				}
				break;
			case WALL_MODIFIER_SWW: // right tile is a wall, but not left
				if (which_part != 0) {
					if (prandom(4) == 0) {
						ptr_add_table(RSET_WALL, RES_WALL_RNDBLOCK, draw_xh, 0, draw_bottom_y - 42, BLIT_NO_TRANS, 0);
					}
					ptr_add_table(RSET_WALL, RES_WALL_DIVIDER1 + middle_divider, draw_xh + 1 /*fix*/ , middle_divider_offset, draw_bottom_y - 21, BLIT_TRANS, 0);
					if (is_dungeon) {
						if (prandom(4) == 0) {
							draw_right_mark(prandom(3), middle_divider_offset);
						}
						if (prandom(4) == 0) {
							draw_left_mark(prandom(3), middle_divider_offset - middle_divider, bottom_divider_offset - bottom_divider);
						}
					}
				}
				break;
			case WALL_MODIFIER_WWS: // left tile is a wall, but not right
				if (which_part != 0) {
					ptr_add_table(RSET_WALL, RES_WALL_DIVIDER1 + middle_divider, draw_xh + 1, middle_divider_offset, draw_bottom_y - 21, BLIT_TRANS, 0);
				}
				ptr_add_table(RSET_WALL, RES_WALL_DIVIDER1 + bottom_divider, draw_xh, bottom_divider_offset, draw_bottom_y, BLIT_TRANS, 0);
				if (which_part != 0) {
					if (is_dungeon) {
						if (prandom(4) == 0) {
							draw_right_mark(prandom(1) + 2, middle_divider_offset);
						}
						if (prandom(4) == 0) {
							draw_left_mark(prandom(4), middle_divider_offset - middle_divider, bottom_divider_offset - bottom_divider);
						}
					}
				}
				break;
		}
	}
	random_seed = saved_prng_state;
	ptr_add_table = saved_sim;
}

void draw_left_mark (word decal_variant, word arg2, word arg1) {
	static const word LPOS[] = {58, 41, 37, 20, 16}; // Vertical render offset for all brick decal variants (last entry seems to be unused)
	word image_id = RES_WALL_MARK_TL;
	word lv2 = 0;
	if (decal_variant % 2) { // Variants alternate between bottomleft and topleft decals
		image_id = RES_WALL_MARK_BL;
	}
	if (decal_variant > 3) {
		lv2 = arg1 + 6;
	} else if (decal_variant > 1) {
		lv2 = arg2 + 6;
	}
	ptr_add_table(RSET_WALL, image_id, draw_xh + (decal_variant == 2 || decal_variant == 3), lv2, draw_bottom_y - LPOS[decal_variant], BLIT_TRANS, 0);
}

void draw_right_mark (word decal_variant, word arg1) {
	static const word RPOS[] = {52, 42, 31, 21}; // Vertical render offset for all brick decal variants (last entry seems to be unused)
	word image_id = RES_WALL_MARK_TR;
	if (decal_variant % 2) { // Variants alternate between bottomright and topright decals
		image_id = RES_WALL_MARK_BR;
	}
	if (decal_variant < 2) {
		arg1 = 24;
	} else {
		arg1 -= 3;
	}
	ptr_add_table(RSET_WALL, image_id, draw_xh + (decal_variant > 1), arg1, draw_bottom_y - RPOS[decal_variant], BLIT_TRANS, 0);
}
