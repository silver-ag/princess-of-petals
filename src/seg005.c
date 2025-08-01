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

// data:1888
extern const word seqtbl_offsets[];

// seg005:000A
void seqtbl_offset_char(short seq_index) {
	Char.curr_seq = seqtbl_offsets[seq_index];
}

// seg005:001D
void seqtbl_offset_opp(int seq_index) {
	Opp.curr_seq = seqtbl_offsets[seq_index];
}

// seg005:0030
void do_fall() {
	if (is_screaming == 0 && Char.fall_y >= 31) {
		play_sound(sound_1_falling); // falling
		is_screaming = 1;
	}
	if ((word)y_land[Char.curr_row + 1] > (word)Char.y) {
		check_grab();

		#ifdef FIX_GLIDE_THROUGH_WALL
		if (fixes->fix_glide_through_wall) {
			// Fix for the kid falling through walls after turning around while running (especially when weightless)
			determine_col();
			get_tile_at_char();
			if (curr_tile2 == tiles_20_wall ||
					((curr_tile2 == tiles_12_doortop || curr_tile2 == tiles_7_doortop_with_floor) &&
					 Char.direction == dir_FF_left)
			) {
				int delta_x = distance_to_edge_weight();
				//printf("delta_x = %d\n", delta_x);
				// When falling into a wall or doortop after turning or running, delta_x is likely to be either 8, 11 or 12
				// Calling in_wall() here produces the desired fix (no glitching through wall), but only when delta_x >= 10
				// The code below "emulates" in_wall() to always get the same effect as if delta_x == 10
				// (which distance actually looks/behaves best is a matter of preference)
				#define delta_x_reference 10
				if (delta_x >= 8) {
					delta_x = -5 + delta_x - delta_x_reference;
					Char.x = (byte) char_dx_forward(delta_x);

					Char.fall_x = 0; // not in in_wall(), but we do need to cancel horizontal movement
				}
			}
		}
		#endif

	} else {

		#ifdef FIX_JUMP_THROUGH_WALL_ABOVE_GATE
		if (fixes->fix_jump_through_wall_above_gate) {
			// At this point, Char.curr_col has not yet been updated since check_bumped()
			// Basically, Char.curr_col is still set to the column of the wall itself (even though the kid
			// may have 'bumped' against the wall, with Char.x being offset)

			// To prevent in_wall() from being called we need to update Char.curr_col here.
			// (in_wall() only makes things worse, because it tries to 'eject' the kid from the wall the wrong way.
			// For this reason, the kid can end up behind a closed gate below, like is possible in Level 7)

			// The fix is calling determine_col() here.

			// One caveat: the kid can also land on the rightmost edge of a closed gate tile, when doing a running jump
			// to the left from two floors up. This 'trick' can be used in original PoP, but is 'fixed' by this change.
			// To still allow this trick to be possible, we can check that we not jumping into a gate tile.
			// (By the way, strangely enough, in unmodified PoP the trick even works with a tapestry + floor tile...)

			if (get_tile_at_char() != tiles_4_gate)
				determine_col();
		}
		#endif

		if (get_tile_at_char() == tiles_20_wall) {
			in_wall();
		}
		#ifdef FIX_DROP_THROUGH_TAPESTRY
		else if (fixes->fix_drop_through_tapestry && get_tile_at_char() == tiles_12_doortop && Char.direction == dir_FF_left) {
			if (distance_to_edge_weight() >= 8) // only intervene if the kid is actually IN FRONT of the tapestry
				in_wall();
		}
		#endif

		if (tile_is_floor(curr_tile2)) {
			land();
		} else {
			inc_curr_row();
		}
	}
}

// seg005:0090
void land() {
	word seq_id;
	is_screaming = 0;

	#ifdef USE_SUPER_HIGH_JUMP
	if (fixes->enable_super_high_jump) {
		super_jump_fall = 0;
	}
	#endif

	Char.y = y_land[Char.curr_row + 1];
	if (1) { //(get_tile_at_char() != tiles_2_spike) {


		if (! tile_is_floor(get_tile_infrontof_char()) &&
			distance_to_edge_weight() < 3
		) {
			Char.x = char_dx_forward(-3);
		}

		#ifdef FIX_LAND_AGAINST_GATE_OR_TAPESTRY
		else if (fixes->fix_land_against_gate_or_tapestry) {
			// A closed gate right in front of the landing spot should not behave like an open floor tile, but like a wall
			// Similar for a tapestry tile (with floor)
			get_tile_infrontof_char();
			if (Char.direction == dir_FF_left && (
							(curr_tile2 == tiles_4_gate && can_bump_into_gate()) ||
							(curr_tile2 == tiles_7_doortop_with_floor))
					&& distance_to_edge_weight() < 3
			) {
				Char.x = char_dx_forward(-3);
			}
		}
		#endif
		start_chompers();
	} else {
		// fell on spikes
		goto loc_5EE6;
	}
	if (Char.alive < 0) {
		// alive
		if ((distance_to_edge_weight() >= 12 //&&
			//get_tile_behind_char() == tiles_2_spike) ||
			//get_tile_at_char() == tiles_2_spike
		)) {
			// fell on spikes
			loc_5EE6:
			if (is_spike_harmful()) {
				spiked();
				return;
			}
			#ifdef FIX_SAFE_LANDING_ON_SPIKES
			else if (fixes->fix_safe_landing_on_spikes && curr_room_modif[curr_tilepos] == 0) {
				// spikes ARE dangerous, just not out yet.
				spiked();
				return;
			}
			#endif // FIX_SAFE_LANDING_ON_SPIKES
		}
		{
			if (Char.fall_y < 22) {
				// fell 1 row
				loc_5EFD:
				if (Char.charid >= charid_2_guard || Char.sword == sword_2_drawn) {
					Char.sword = sword_2_drawn;
					seq_id = seq_63_guard_active_after_fall; // stand active after landing
				} else {
					seq_id = seq_17_soft_land; // crouch (soft land)
				}
				if (Char.charid == charid_0_kid) {
					play_sound(sound_17_soft_land); // soft land (crouch)
					is_guard_notice = 1;
				}
			} else if (Char.fall_y < 33) {
				// fell 2 rows
				if (Char.charid == charid_1_shadow) goto loc_5EFD;
				if (Char.charid == charid_2_guard) goto loc_5F6C;
				// kid (or skeleton (bug!))
				if (! take_hp(1)) {
					// still alive
					play_sound(sound_16_medium_land); // medium land
					is_guard_notice = 1;
					seq_id = seq_20_medium_land; // medium land (lose 1 HP, crouch)
				} else {
					// dead (this was the last HP)
					goto loc_5F75;
				}
			} else {
				// fell 3 or more rows
				goto loc_5F6C;
			}
		}
	} else {
		// dead
		loc_5F6C:
		take_hp(100);
		loc_5F75:
		play_sound(sound_0_fell_to_death); // prince crashing into the floor
		seq_id = seq_22_crushed; // dead (after falling)
	}
	seqtbl_offset_char(seq_id);
	play_seq();
	Char.fall_y = 0;
}

// seg005:01B7
void spiked() {
	// If someone falls into spikes, those spikes become harmless (to others).
	curr_room_modif[curr_tilepos] = 0xFF;
	Char.y = y_land[Char.curr_row + 1];
	#ifdef FIX_OFFSCREEN_GUARDS_DISAPPEARING
	// a guard can get teleported to the other side of kid's room
	// when landing on spikes in another room
	if (fixes->fix_offscreen_guards_disappearing) {
		short spike_col = tile_col;
		if (curr_room != Char.room)	{
			if (curr_room == level.roomlinks[Char.room - 1].right) {
				spike_col += 10;
			} else if (curr_room == level.roomlinks[Char.room - 1].left) {
				spike_col -= 10;
			}
		}
		Char.x = x_bump[spike_col + FIRST_ONSCREEN_COLUMN] + 10;
	} else {
	#endif
		Char.x = x_bump[tile_col + FIRST_ONSCREEN_COLUMN] + 10;
	#ifdef FIX_OFFSCREEN_GUARDS_DISAPPEARING
	}
	#endif
	Char.x = char_dx_forward(8);
	Char.fall_y = 0;
	play_sound(sound_48_spiked); // something spiked
	take_hp(100);
	seqtbl_offset_char(seq_51_spiked); // spiked
	play_seq();
}

// seg005:0213
void control() {
	short char_frame = Char.frame;
	if (Char.alive >= 0) {
		if (char_frame == frame_15_stand || // stand
			char_frame == frame_166_stand_inactive || // stand
			char_frame == frame_158_stand_with_sword || // stand with sword
			char_frame == frame_171_stand_with_sword // stand with sword
		) {
			seqtbl_offset_char(seq_71_dying); // dying (not stabbed)
		}
	} else {
		short char_action = Char.action;
		if (char_action == actions_5_bumped ||
			char_action == actions_4_in_freefall
		) {
			release_arrows();
		} else if (Char.sword == sword_2_drawn) {
			control_with_sword();
		} else if (Char.charid >= charid_2_guard) {
			control_guard_inactive();
		} else if (char_frame == frame_15_stand || // standing
			(char_frame>= frame_50_turn && char_frame<53) // end of turning
		) {
			control_standing();
		} else if (char_frame == frame_48_turn) { // a frame in turning
			control_turning();
		} else if (char_frame < 4) { // start run
			control_startrun();
		} else if (char_frame >= frame_67_start_jump_up_1 && char_frame < frame_70_jumphang) { // start jump up
			control_jumpup();
		} else if (char_frame < 15) { // running
			control_running();
		} else if (char_frame >= frame_87_hanging_1 && char_frame < 100) { // hanging
			control_hanging();
		} else if (char_frame == frame_109_crouch) { // crouching
			control_crouched();
		}

		#ifdef ALLOW_CROUCH_AFTER_CLIMBING
		// When ducking with down+forward, give time to release the forward control (prevents unintended crouch-hops)
		else if (fixes->enable_crouch_after_climbing && Char.curr_seq >= seqtbl_offsets[seq_50_crouch] &&
				Char.curr_seq < seqtbl_offsets[seq_49_stand_up_from_crouch]) // while stooping
			if (control_forward != CONTROL_IGNORE) control_forward = CONTROL_RELEASED;
		#endif

		#ifdef FIX_MOVE_AFTER_DRINK
		if (fixes->fix_move_after_drink && char_frame >= frame_191_drink && char_frame <= frame_205_drink)
			release_arrows();
		#endif

		#ifdef FIX_MOVE_AFTER_SHEATHE
		if (fixes->fix_move_after_sheathe &&
				Char.curr_seq >= seqtbl_offsets[seq_92_put_sword_away] &&
				Char.curr_seq < seqtbl_offsets[seq_93_put_sword_away_fast]
		)
			release_arrows();
		#endif
	}
}

// seg005:02EB
void control_crouched() {
	if (need_level1_music != 0 && current_level == /*1*/ custom->intro_music_level) {
		// Special event: music when crouching
		if (! check_sound_playing()) {
			if (need_level1_music == 1) {
				play_sound(sound_25_presentation); // presentation (level 1 start)
				need_level1_music = 2;
			} else {
#ifdef USE_REPLAY
				if (recording) special_move = MOVE_EFFECT_END;
				if (!replaying) // during replays, crouch immobilization gets cancelled in do_replay_move()
#endif
				need_level1_music = 0;
			}
		}
	} else {
		need_level1_music = 0;
		if (control_shift2 == CONTROL_HELD && check_get_item()) return;
		if (control_y != CONTROL_HELD_DOWN) {
			seqtbl_offset_char(seq_49_stand_up_from_crouch); // stand up from crouch
		} else {
			if (control_forward == CONTROL_HELD) {
				control_forward = CONTROL_IGNORE; // disable automatic repeat
				seqtbl_offset_char(seq_79_crouch_hop); // crouch-hop
			}
		}
	}
}

// seg005:0358
void control_standing() {
	if (control_shift2 == CONTROL_HELD && control_shift == CONTROL_HELD && check_get_item()) {
		return;
	}
	if (Char.charid != charid_0_kid && control_down == CONTROL_HELD && control_forward == CONTROL_HELD) {
		draw_sword();
		return;
	} //else
	if (have_sword) {
		if (offguard != 0 && control_shift >= CONTROL_RELEASED) goto loc_6213;
		if (can_guard_see_kid >= 2) {
			short distance = char_opp_dist();
			if (distance >= -10 && distance < 90) {
				holding_sword = 1;
				if ((word)distance < (word)-6) {
					if (Opp.charid == charid_1_shadow &&
						(Opp.action == actions_3_in_midair || (Opp.frame >= frame_107_fall_land_1 && Opp.frame < 118))
					) {
						offguard = 0;
					} else {
						draw_sword();
						return;
					}
				} else {
					back_pressed();
					return;
				}
			}
		} else {
			offguard = 0;
		}
	}
	if (control_shift == CONTROL_HELD) {
		if (control_backward == CONTROL_HELD) {
			back_pressed();
		} else if (control_up == CONTROL_HELD) {
			up_pressed();
		} else if (control_down == CONTROL_HELD) {
			down_pressed();
		} else if (control_x == CONTROL_HELD_FORWARD && control_forward == CONTROL_HELD) {
			safe_step();
		}
	} else loc_6213: if (control_forward == CONTROL_HELD) {
		if (is_keyboard_mode && control_up == CONTROL_HELD) {
			standing_jump();
		} else {
			forward_pressed();
		}
	} else if (control_backward == CONTROL_HELD) {
		back_pressed();
	} else if (control_up == CONTROL_HELD) {
		if (is_keyboard_mode && control_forward == CONTROL_HELD) {
			standing_jump();
		} else {
			up_pressed();
		}
	} else if (control_down == CONTROL_HELD) {
		down_pressed();
	} else if (control_x == CONTROL_HELD_FORWARD) {
		forward_pressed();
	}
}

int source_modifier;
int source_room;
int source_tilepos;

// seg005:0482
void up_pressed() {
	// If there is an open level door nearby, enter it.
	int leveldoor_tilepos = -1;
	if (get_tile_at_char() == tiles_16_level_door_left) leveldoor_tilepos = curr_tilepos;
	else if (get_tile_behind_char() == tiles_16_level_door_left) leveldoor_tilepos = curr_tilepos;
	else if (get_tile_infrontof_char() == tiles_16_level_door_left) leveldoor_tilepos = curr_tilepos;
	if ((leveldoor_tilepos != -1) &&
		level.start_room != drawn_room &&
		(
			fixes->fix_exit_door
			? curr_room_modif[leveldoor_tilepos] >= 42 // this door must be fully open
			: leveldoor_open
		)
	){
		go_up_leveldoor();
		return;
	}

#ifdef USE_TELEPORTS
	// If there is a teleport nearby, enter it.
	// (A teleport is a repurposed left half balcony with a non-zero modifier.)
	/*leveldoor_tilepos = -1;
	// This detection is not perfect...
	if (get_tile_at_char() == tiles_23_balcony_left) leveldoor_tilepos = curr_tilepos;
	else if (get_tile_behind_char() == tiles_23_balcony_left) leveldoor_tilepos = curr_tilepos;
	else if (get_tile_infrontof_char() == tiles_23_balcony_left) leveldoor_tilepos = curr_tilepos;
	if (leveldoor_tilepos != -1) {
		// We reuse pickup_obj_type for storing the identifier of the teleporter.
		pickup_obj_type = curr_room_modif[curr_tilepos];
		// Balconies with zero modifiers remain regular balconies.
		if (pickup_obj_type > 0)
		{
			source_modifier = pickup_obj_type;
			source_room = curr_room;
			source_tilepos = curr_tilepos;
			go_up_leveldoor();
			seqtbl_offset_char(seq_teleport);
			return;
		}
	}*/
#endif

	// Else just jump up.
	{
		if (control_x == CONTROL_HELD_FORWARD) {
			standing_jump();
		} else {
			check_jump_up();
		}
	}
}

// seg005:04C7
void down_pressed() {
	control_down = CONTROL_IGNORE; // disable automatic repeat
	if (! tile_is_floor(get_tile_infrontof_char()) &&
		distance_to_edge_weight() < 3
	) {
		Char.x = char_dx_forward(5);
		load_fram_det_col();
	} else {
		if (! tile_is_floor(get_tile_behind_char()) &&
			distance_to_edge_weight() >= 8
		) {
			through_tile = get_tile_behind_char();
			get_tile_at_char();
			if (can_grab() &&
				#ifdef ALLOW_CROUCH_AFTER_CLIMBING
				(!(fixes->enable_crouch_after_climbing && control_forward == CONTROL_HELD)) &&
				#endif
				(Char.direction >= dir_0_right ||
				get_tile_at_char() != tiles_4_gate ||
				curr_room_modif[curr_tilepos] >> 2 >= 6)
			) {
				Char.x = char_dx_forward(distance_to_edge_weight() - 9);
				seqtbl_offset_char(seq_68_climb_down); // climb down
			} else {
				crouch();
			}
		} else {
			crouch();
		}
	}
}

// seg005:0574
void go_up_leveldoor() {
	Char.x = x_bump[tile_col + FIRST_ONSCREEN_COLUMN] + 10;
	Char.direction = dir_FF_left; // right
	seqtbl_offset_char(seq_70_go_up_on_level_door); // go up on level door
}

// seg005:058F
void control_turning() {
	if (control_shift >= CONTROL_RELEASED && control_x == CONTROL_HELD_FORWARD && control_y >= CONTROL_RELEASED) {
#ifdef FIX_TURN_RUN_NEAR_WALL
		if (fixes->fix_turn_running_near_wall) {
			int distance = get_edge_distance();
			// the same logic as the safe-step condition in the forward_pressed() method
			if (edge_type == EDGE_TYPE_WALL && curr_tile2 != tiles_18_chomper && distance < 8) {
				control_forward = CONTROL_HELD; // ensures the value is not CONTROL_IGNORE since control_x == CONTROL_HELD_FORWARD
			} else {
				seqtbl_offset_char(seq_43_start_run_after_turn);
			}
		} else {
			seqtbl_offset_char(seq_43_start_run_after_turn);
		}
#else
		seqtbl_offset_char(seq_43_start_run_after_turn); // start run and run (after turning)
#endif
	}

	// Added:
	// When using a joystick, the kid may sometimes jump/duck/turn unintendedly after turning around.
	// To prevent this: clear the remembered controls, so that if the stick has already moved to another/neutral position,
	// the kid will not jump, duck, or turn again.
	if (is_joyst_mode) {
		if (control_up == CONTROL_HELD && control_y >= CONTROL_RELEASED) {
			control_up = CONTROL_RELEASED;
		}
		if (control_down == CONTROL_HELD && control_y <= CONTROL_RELEASED) {
			control_down = CONTROL_RELEASED;
		}
		if (control_backward == CONTROL_HELD && control_x == CONTROL_RELEASED) {
			control_backward = CONTROL_RELEASED;
		}
	}
}

// seg005:05AD
void crouch() {
	seqtbl_offset_char(seq_50_crouch); // crouch
	control_down = release_arrows();
}

// seg005:05BE
void back_pressed() {
	word seq_id;
	control_backward = release_arrows();
	// After turn, Kid will draw sword if ...
	if (have_sword == 0 || // if Kid has sword
		can_guard_see_kid < 2 || // and can see Guard
		char_opp_dist() > 0 || // and Guard was behind him
		distance_to_edge_weight() < 2
	) {
		seq_id = seq_5_turn; // turn
	} else {
		Char.sword = sword_2_drawn;
		offguard = 0;
		seq_id = seq_89_turn_draw_sword; // turn and draw sword
	}
	seqtbl_offset_char(seq_id);
}

// seg005:060F
void forward_pressed() {
	short distance;
	distance = get_edge_distance();
	#ifdef ALLOW_CROUCH_AFTER_CLIMBING
	if (fixes->enable_crouch_after_climbing && control_down == CONTROL_HELD) {
		down_pressed();
		control_forward = CONTROL_RELEASED;
		return;
	}
	#endif

	if (edge_type == EDGE_TYPE_WALL && curr_tile2 != tiles_18_chomper && distance < 8) {
		// If char is near a wall, step instead of run.
		if (control_forward == CONTROL_HELD) {
			safe_step();
		}
	} else {
		seqtbl_offset_char(seq_1_start_run); // start run and run
	}
}

// seg005:0649
void control_running() {
	if (control_x == CONTROL_RELEASED && (Char.frame == frame_7_run || Char.frame == frame_11_run)) {
		control_forward = release_arrows();
		seqtbl_offset_char(seq_13_stop_run); // stop run
	} else if (control_x == CONTROL_HELD_BACKWARD) {
		control_backward = release_arrows();
		seqtbl_offset_char(seq_6_run_turn); // run-turn
	} else if (control_y == CONTROL_HELD_UP && control_up == CONTROL_HELD) {
		run_jump();
	} else if (control_down == CONTROL_HELD) {
		control_down = CONTROL_IGNORE; // disable automatic repeat
		seqtbl_offset_char(seq_26_crouch_while_running); // crouch while running
	}
}

// seg005:06A8
void safe_step() {
	control_shift2 = CONTROL_IGNORE; // disable automatic repeat
	control_forward = CONTROL_IGNORE; // disable automatic repeat
	short distance = get_edge_distance();
	if (distance) {
		Char.repeat = 1;
		seqtbl_offset_char(distance + 28); // 29..42: safe step to edge
	} else if (edge_type != EDGE_TYPE_WALL && Char.repeat != 0) {
		Char.repeat = 0;
		seqtbl_offset_char(seq_44_step_on_edge); // step on edge
	} else {
		seqtbl_offset_char(seq_39_safe_step_11); // unsafe step (off ledge)
	}
}

// seg005:06F0
int check_get_item() {
	if (get_tile_at_char() == tiles_10_potion ||
		curr_tile2 == tiles_22_sword ||
		get_tile_at_char() == tiles_2_egg
	) {
		if (! tile_is_floor(get_tile_behind_char())) {
			return 0;
		}
		Char.x = char_dx_forward(-14);
		load_fram_det_col();
	}
	if (get_tile_infrontof_char() == tiles_10_potion ||
		curr_tile2 == tiles_22_sword ||
		(get_tile_infrontof_char() == tiles_2_egg && get_modifier_infrontof_char() == 0) // only if not already broken
	) {
		get_item();
		return 1;
	}
	return 0;
}

// seg005:073E
void get_item() {
	if (get_tile_at_char() == tiles_2_egg && get_modifier_at_char() == 0) {
		draw_sword();
		set_modifier_at_char(1);
	} else if (get_tile_infrontof_char() == tiles_2_egg && get_modifier_infrontof_char() == 0) {
		draw_sword();
		set_modifier_infrontof_char(1);
	} else if (Char.frame != frame_109_crouch) { // crouching
		short distance = get_edge_distance();
		if (edge_type != EDGE_TYPE_FLOOR) {
			Char.x = char_dx_forward(distance);
		}
		if (Char.direction >= dir_0_right) {
			Char.x = char_dx_forward((curr_tile2 == tiles_10_potion) - 2);
		}
		crouch();
	} else if (curr_tile2 == tiles_22_sword) {
		do_pickup(-1);
		seqtbl_offset_char(seq_91_get_sword); // get sword
	} else { // potion
		do_pickup(curr_room_modif[curr_tilepos] >> 3);
		seqtbl_offset_char(seq_78_drink); // drink
#ifdef USE_COPYPROT
		if (current_level == 15) {
			for (short index = 0; index < 14; ++index) {
				// remove letter on potions level
				if (copyprot_room[index] == curr_room &&
					copyprot_tile[index] == curr_tilepos
				) {
					copyprot_room[index] = 0;
					break;
				}
			}
		}
#endif
	}
}

// seg005:07FF
void control_startrun() {
	if (control_y == CONTROL_HELD_UP && control_x == CONTROL_HELD_FORWARD) {
		standing_jump();
	}
}

// seg005:0812
void control_jumpup() {
	if (control_x == CONTROL_HELD_FORWARD || control_forward == CONTROL_HELD) {
		standing_jump();
	}
}

// seg005:0825
void standing_jump() {
	control_up = control_forward = CONTROL_IGNORE; // disable automatic repeat
	seqtbl_offset_char(seq_3_standing_jump); // standing jump
}

// seg005:0836
void check_jump_up() {
	control_up = release_arrows();
	through_tile = get_tile_above_char();
	get_tile_front_above_char();
	if (can_grab()) {
		grab_up_with_floor_behind();
	} else {
		through_tile = get_tile_behind_above_char();
		get_tile_above_char();
		if (can_grab()) {
			jump_up_or_grab();
		} else {
			jump_up();
		}
	}
}

// seg005:087B
void jump_up_or_grab() {
	short distance = distance_to_edge_weight();
	if (distance < 6) {
		jump_up();
	} else if (! tile_is_floor(get_tile_behind_char())) {
		// There is not floor behind char.
		grab_up_no_floor_behind();
	} else {
		// There is floor behind char, go back a bit.
		Char.x = char_dx_forward(distance - TILE_SIZEX);
		load_fram_det_col();
		grab_up_with_floor_behind();
	}
}

// seg005:08C7
void grab_up_no_floor_behind() {
	get_tile_above_char();
	Char.x = char_dx_forward(distance_to_edge_weight() - 10);
	seqtbl_offset_char(seq_16_jump_up_and_grab); // jump up and grab (no floor behind)
}

// seg005:08E6
void jump_up() {
	word delta_x;
	control_up = release_arrows();
	short distance = get_edge_distance();
	if (distance < 4 && edge_type == EDGE_TYPE_WALL) {
		Char.x = char_dx_forward(distance - 3);
	}
	#ifdef FIX_JUMP_DISTANCE_AT_EDGE
	// When climbing up two floors, turning around and jumping upward, the kid falls down.
	// This fix makes the workaround of Trick 25 unnecessary.
	if (fixes->fix_jump_distance_at_edge && distance == 3 && edge_type == EDGE_TYPE_CLOSER) {
		Char.x = char_dx_forward(-1);
	}
	#endif
	#ifdef USE_SUPER_HIGH_JUMP
	// kid should be able to grab 2 tiles above from an edge of a floor tile
	if (is_feather_fall && !tile_is_floor(get_tile_above_char()) && curr_tile2 != tiles_20_wall) {
		delta_x = Char.direction == dir_FF_left ? 1 : 3;
	} else {
		delta_x = 0;
	}
	int char_col = get_tile_div_mod(back_delta_x(delta_x) + dx_weight() - 6);
	get_tile(Char.room, char_col, Char.curr_row - 1);
	if (curr_tile2 != tiles_20_wall && !tile_is_floor(curr_tile2)) {
		if (fixes->enable_super_high_jump && is_feather_fall) { // super high jump can only happen in feather mode
			if (curr_room == 0 && Char.curr_row == 0) { // there is no room above
				seqtbl_offset_char(seq_14_jump_up_into_ceiling);
			} else {
				get_tile(Char.room, char_col, Char.curr_row - 2); // the target top tile
				bool is_top_floor = tile_is_floor(curr_tile2) || curr_tile2 == tiles_20_wall;
				if (is_top_floor && curr_tile2 == tiles_11_loose && (curr_room_tiles[curr_tilepos] & 0x20) == 0) {
					is_top_floor = false; // a regular loose floor above should not be treated as a floor
				}
				// kid should jump slightly higher if the top tile is not a floor
				super_jump_timer = is_top_floor ? 22 : 24;
				super_jump_room = curr_room;
				super_jump_col = tile_col;
				super_jump_row = tile_row;
				seqtbl_offset_char(seq_48_super_high_jump); // jump up 2 rows with nothing above
			}
		} else {
			seqtbl_offset_char(seq_28_jump_up_with_nothing_above); // jump up with nothing above
		}
	} else {
		seqtbl_offset_char(seq_14_jump_up_into_ceiling); // jump up with wall or floor above
	}
	#else
	get_tile(Char.room, get_tile_div_mod(back_delta_x(0) + dx_weight() - 6), Char.curr_row - 1);
	if (curr_tile2 != tiles_20_wall && ! tile_is_floor(curr_tile2)) {
		seqtbl_offset_char(seq_28_jump_up_with_nothing_above); // jump up with nothing above
	} else {
		seqtbl_offset_char(seq_14_jump_up_into_ceiling); // jump up with wall or floor above
	}
	#endif
}

// seg005:0968
void control_hanging() {
	if (Char.alive < 0) {
		if (grab_timer == 0 && control_y == CONTROL_HELD) {
			can_climb_up();
#ifdef USE_SUPER_HIGH_JUMP
		} else if (control_shift == CONTROL_HELD || (fixes->enable_super_high_jump && super_jump_fall && control_y == CONTROL_HELD)) {
#else
		} else if (control_shift == CONTROL_HELD) {
#endif
			// hanging against a wall or a doortop
			if (Char.action != actions_6_hang_straight &&
				(get_tile_at_char() == tiles_20_wall ||
				(Char.direction == dir_FF_left && ( // facing left
					curr_tile2 == tiles_4_gate ||
					curr_tile2 == tiles_7_doortop_with_floor ||
					curr_tile2 == tiles_12_doortop)) ||
				(Char.direction == dir_0_right &&   // facing right
					curr_tile2 == tiles_23_left_gate))
			) {
				if (grab_timer == 0) {
					play_sound(sound_8_bumped); // touching a wall (hang against wall)
				}
				seqtbl_offset_char(seq_25_hang_against_wall); // hang against wall (straight)
			} else {
				if (! tile_is_floor(get_tile_above_char())) {
					hang_fall();
				}
			}
		} else {
			hang_fall();
		}
	} else {
		hang_fall();
	}
}

// seg005:09DF
void can_climb_up() {
	short seq_id = seq_10_climb_up; // climb up
	control_up = control_shift2 = release_arrows();
#ifdef USE_SUPER_HIGH_JUMP
	if (fixes->enable_super_high_jump) {
		super_jump_fall = 0;
	}
#endif
	get_tile_above_char();
	if (((curr_tile2 == tiles_13_mirror || curr_tile2 == tiles_18_chomper) &&
		Char.direction == dir_0_right) ||
		(curr_tile2 == tiles_4_gate && Char.direction != dir_0_right &&
		  curr_room_modif[curr_tilepos] >> 2 < 6) ||
		(curr_tile2 == tiles_23_left_gate && Char.direction != dir_FF_left &&
		  curr_room_modif[curr_tilepos] >> 2 < 6)
	) {
		seq_id = seq_73_climb_up_to_closed_gate; // climb up to closed gate and down
	}
	seqtbl_offset_char(seq_id);
}

// seg005:0A46
void hang_fall() {
	control_down = release_arrows();
#ifdef USE_SUPER_HIGH_JUMP
	if (fixes->enable_super_high_jump) {
		super_jump_fall = 0;
	}
#endif
	if (! tile_is_floor(get_tile_behind_char()) &&
		! tile_is_floor(get_tile_at_char())
	) {
		seqtbl_offset_char(seq_23_release_ledge_and_fall); // release ledge and fall
	} else {
		if		((get_tile_at_char() == tiles_20_wall ||
				(Char.direction == dir_FF_left && ( // facing left
					curr_tile2 == tiles_4_gate ||
					curr_tile2 == tiles_7_doortop_with_floor ||
					curr_tile2 == tiles_12_doortop)) ||
				(Char.direction == dir_0_right &&   // facing right
					curr_tile2 == tiles_23_left_gate))
		) {
			in_wall();
			Char.x = char_dx_forward(-7);
		}
		seqtbl_offset_char(seq_11_release_ledge_and_land); // end of climb down
	}
}

// seg005:0AA8
void grab_up_with_floor_behind() {
	short distance = distance_to_edge_weight();

	// The global variable edge_type (which we need!) gets set as a side effect of get_edge_distance()
	short edge_distance = get_edge_distance();
	//printf("Distance to edge weight: %d\tedge type: %d\tedge distance: %d\n", distance, edge_type, edge_distance);

	#ifdef FIX_EDGE_DISTANCE_CHECK_WHEN_CLIMBING
	// When climbing to a higher floor, the game unnecessarily checks how far away the edge below is;
	// This contributes to sometimes "teleporting" considerable distances when climbing from firm ground
	#define JUMP_STRAIGHT_CONDITION (fixes->fix_edge_distance_check_when_climbing)						\
									? (distance < 4 && edge_type != EDGE_TYPE_WALL)									\
									: (distance < 4 && edge_distance < 4 && edge_type != EDGE_TYPE_WALL)
	#else
	#define JUMP_STRAIGHT_CONDITION distance < 4 && edge_distance < 4 && edge_type != 1
	#endif

	if (JUMP_STRAIGHT_CONDITION) {
		Char.x = char_dx_forward(distance);
		seqtbl_offset_char(seq_8_jump_up_and_grab_straight); // jump up and grab (when?)
	} else {
		Char.x = char_dx_forward(distance - 4);
		seqtbl_offset_char(seq_24_jump_up_and_grab_forward); // jump up and grab (with floor behind)
	}
}

// seg005:0AF7
void run_jump() {
	short pos_adjustment;
	if (Char.frame >= frame_7_run) {
		// Align Kid to edge of floor.
		short xpos = char_dx_forward(4);
		short col = get_tile_div_mod_m7(xpos);
		for (short tiles_forward = 0; tiles_forward < 2; ++tiles_forward) { // Iterate through current tile and the next two tiles looking for a tile the player should jump from
			col += dir_front[Char.direction + 1];
			get_tile(Char.room, col, Char.curr_row);
			if (/*curr_tile2 == tiles_2_spike ||*/ ! tile_is_floor(curr_tile2)) {
				pos_adjustment = distance_to_edge(xpos) + TILE_SIZEX * tiles_forward - TILE_SIZEX;
				if ((word)pos_adjustment < (word)-8 || pos_adjustment >= 2) {
					if (pos_adjustment < 128) return;
					pos_adjustment = -3;
				}
				Char.x = char_dx_forward(pos_adjustment + 4);
				break;
			}
		}
		control_up = release_arrows(); // disable automatic repeat
		seqtbl_offset_char(seq_4_run_jump); // run-jump
	}
}

// sseg005:0BB5
void back_with_sword() {
	short frame = Char.frame;
	if (frame == frame_158_stand_with_sword || frame == frame_170_stand_with_sword || frame == frame_171_stand_with_sword) {
		control_backward = CONTROL_IGNORE; // disable automatic repeat
		seqtbl_offset_char(seq_57_back_with_sword); // back with sword
	}
}

// seg005:0BE3
void forward_with_sword() {
	short frame = Char.frame;
	if (frame == frame_158_stand_with_sword || frame == frame_170_stand_with_sword || frame == frame_171_stand_with_sword) {
		control_forward = CONTROL_IGNORE; // disable automatic repeat
		if (Char.charid != charid_0_kid) {
			seqtbl_offset_char(seq_56_guard_forward_with_sword); // forward with sword (Guard)
		} else {
			seqtbl_offset_char(seq_86_forward_with_sword); // forward with sword (Kid)
		}
	}
}

// seg005:0C1D
void draw_sword() {
	word seq_id = seq_55_draw_sword; // draw sword
	control_forward = control_shift2 = release_arrows();
#ifdef FIX_UNINTENDED_SWORD_STRIKE
	if (fixes->fix_unintended_sword_strike) {
		ctrl1_shift2 = CONTROL_IGNORE; // prevent restoring control_shift2 to CONTROL_HELD in rest_ctrl_1()
	}
#endif
	if (Char.charid == charid_0_kid) {
		play_sound(sound_19_draw_sword); // taking out the sword
		offguard = 0;
	} else if (Char.charid != charid_1_shadow) {
		seq_id = seq_90_en_garde; // stand active
	}
	Char.sword = sword_2_drawn;
	seqtbl_offset_char(seq_id);
}

// seg005:0C67
void control_with_sword() {
	if (Char.action < actions_2_hang_climb) {
		if (get_tile_at_char() == tiles_11_loose || can_guard_see_kid >= 2) {
			short distance = char_opp_dist();
			if ((word)distance < (word)90) {
				swordfight();
				return;
			} else if (distance < 0) {
				if ((word)distance < (word)-4) {
					seqtbl_offset_char(seq_60_turn_with_sword); // turn with sword (after switching places)
					return;
				} else {
					swordfight();
					return;
				}
			}
		} /*else*/ {
			if (Char.charid == charid_0_kid && Char.alive < 0) {
				holding_sword = 0;
			}
			if (Char.charid < charid_2_guard) {
				// frame 171: stand with sword
				if (Char.frame == frame_171_stand_with_sword) {
					Char.sword = sword_0_sheathed;
					seqtbl_offset_char(seq_92_put_sword_away); // put sword away (Guard died)
				}
			} else {
				swordfight();
			}
		}
	}
}

// seg005:0CDB
void swordfight() {
	short seq_id;
	short frame = Char.frame;
	short charid = Char.charid;
	// frame 161: parry
	if (frame == frame_161_parry && control_shift2 >= 0) {
		seqtbl_offset_char(seq_57_back_with_sword); // back with sword (when parrying)
		return;
	} else if (control_shift2 == CONTROL_HELD) {
		if (charid == charid_0_kid) {
			kid_sword_strike = 15;
		}
		sword_strike();
		if (control_shift2 == CONTROL_IGNORE) return;
	}
	if (control_down == CONTROL_HELD) {
		if (frame == frame_158_stand_with_sword || frame == frame_170_stand_with_sword || frame == frame_171_stand_with_sword) {
			control_down = CONTROL_IGNORE; // disable automatic repeat
			Char.sword = sword_0_sheathed;
			if (charid == charid_0_kid) {
				offguard = 1;
				guard_refrac = 9;
				holding_sword = 0;
				seq_id = seq_93_put_sword_away_fast; // put sword away fast (down pressed)
			} else if (charid == charid_1_shadow) {
				seq_id = seq_92_put_sword_away; // put sword away
			} else {
				seq_id = seq_87_guard_become_inactive; // stand inactive (when Kid leaves sight)
			}
			seqtbl_offset_char(seq_id);
		}
	} else if (control_up == CONTROL_HELD) {
		parry();
	} else if (control_forward == CONTROL_HELD) {
		forward_with_sword();
	} else if (control_backward == CONTROL_HELD) {
		back_with_sword();
	}
}

// seg005:0DB0
void sword_strike() {
	short frame;
	short seq_id;
	frame = Char.frame;
	if (frame == frame_157_walk_with_sword || // walk with sword
		frame == frame_158_stand_with_sword || // stand with sword
		frame == frame_170_stand_with_sword || // stand with sword
		frame == frame_171_stand_with_sword || // stand with sword
		frame == frame_165_walk_with_sword // walk with sword
	) {
		if (Char.charid == charid_0_kid) {
			seq_id = seq_75_strike; // strike with sword (Kid)
		} else {
			seq_id = seq_58_guard_strike; // strike with sword (Guard)
		}
	} else if (frame == frame_150_parry || frame == frame_161_parry) { // parry
		seq_id = seq_66_strike_after_parry; // strike with sword after parrying
	} else {
		return;
	}
	control_shift2 = CONTROL_IGNORE; // disable automatic repeat
	seqtbl_offset_char(seq_id);
}

// seg005:0E0F
void parry() {
	short char_frame = Char.frame;
	short opp_frame = Opp.frame;
	short char_charid = Char.charid;
	short seq_id = seq_62_parry; // defend (parry) with sword
	short do_play_seq = 0;
	if (
		char_frame == frame_158_stand_with_sword || // stand with sword
		char_frame == frame_170_stand_with_sword || // stand with sword
		char_frame == frame_171_stand_with_sword || // stand with sword
		char_frame == frame_168_back || // back?
		char_frame == frame_165_walk_with_sword // walk with sword
	) {
		if (char_opp_dist() >= 32 && char_charid != charid_0_kid) {
			back_with_sword();
			return;
		} else if (char_charid == charid_0_kid) {
			if (opp_frame == frame_168_back) return;
			if (opp_frame != frame_151_strike_1 &&
				opp_frame != frame_152_strike_2 &&
				opp_frame != frame_162_block_to_strike
			) {
				if (opp_frame == frame_153_strike_3) { // strike
					do_play_seq = 1;
				} else
				if (char_charid != charid_0_kid) {
					back_with_sword();
					return;
				}
			}
		} else {
			if (opp_frame != frame_152_strike_2) return;
		}
	} else {
		if (char_frame != frame_167_blocked) return;
		seq_id = seq_61_parry_after_strike; // parry after striking with sword
	}
	control_up = CONTROL_IGNORE; // disable automatic repeat
	seqtbl_offset_char(seq_id);
	if (do_play_seq) {
		play_seq();
	}
}

#ifdef USE_TELEPORTS
void teleport() {
	// Ideally these variables should be global and be initialized in up_pressed().
	//int source_modifier = pickup_obj_type;
	//int source_room = Char.room;
	//int source_tilepos = Char.curr_row * 10 + Char.curr_col - 1;

	bool found = false;
	int dest_room, dest_tilepos;

	// Find the pair of the teleport which the prince entered.
	for (dest_room = 1; dest_room <= 24; dest_room++) {
		// It must be in a different room.
		//if (dest_room == source_room) continue;

		get_room_address(dest_room);

		for (dest_tilepos = 0; dest_tilepos < 30; dest_tilepos++) {
			// Skip over the source teleport.
			if (dest_room == source_room && dest_tilepos == source_tilepos) continue;

			// The pair is a balcony tile with the same modifier.
			/*if (get_curr_tile(dest_tilepos) == tiles_23_balcony_left && curr_modifier == source_modifier) {
				found = true;
				goto exit;
			}*/ // commented out for tiles_23_balcony_left
		}
	}
	exit:

	if (found) {
		// We found a pair. Put the kid there.
		// Based on do_startpos().
		Char.room = dest_room;
		Char.curr_col = dest_tilepos % 10;
		Char.curr_row = dest_tilepos / 10;
		Char.x = x_bump[Char.curr_col + 5] + 14 + 7; // Center on the destination teleport.
		Char.y = y_land[Char.curr_row + 1];
		next_room = Char.room;
		clear_coll_rooms(); // Without this, the prince will sometimes end up at the wrong place.
#ifdef FIX_DISAPPEARING_GUARD_B
		if (next_room != drawn_room)
#endif
		{
			leave_guard();
		}
#ifdef FIX_DISAPPEARING_GUARD_A
		if (next_room == drawn_room) drawn_room = 0;
#endif
		seqtbl_offset_char(seq_5_turn);
		play_sound(sound_45_jump_through_mirror);
	} else {
		// No pair found.
		//show_dialog("Error: This teleport has no pair.");
		char message[80];
		snprintf(message, sizeof(message), "Error: There is no other teleport with modifier %d.", pickup_obj_type);
		show_dialog(message);
		Char.x = x_bump[Char.curr_col + 5] + 14;
		Char.y = y_land[Char.curr_row + 1];
		seqtbl_offset_char(seq_17_soft_land);
		play_sound(sound_0_fell_to_death);
	}
}
#endif

