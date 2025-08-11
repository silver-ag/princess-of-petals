#include "common.h"

typedef struct petal_t {
	int x;
	int y;
	int type;
} petal_t;

petal_t petals[50];

void manage_custom_graphics() {
	manage_death_flash();
	manage_pause_controls();
	manage_face_turn();
	if (touga_entered && touga_enter_count < 100) {
		manage_touga_enter();
	}
}

void start_death_flash(int frames) {
	stored_colour = bg_colour;
	death_flash_frames = frames;
}

int room_change_counter = 0;

void manage_death_flash() {
	if (death_flash_frames > 1 || (Kid.alive < 0 && death_flash_frames == 1)) { // final frame only resets if kid is alive
		death_flash_frames--;
		if (death_flash_frames % 2) {
			bg_colour = (rgb_type){255,0,0};
			silhouette_mode = true;
		} else {
			bg_colour = stored_colour;
			silhouette_mode = false;
		}
		if (death_flash_frames == 0) {
			need_full_redraw = 1;
		}
	}
}

void start_drawing_petals(int x, int y) {
	drawing_petals = true;
	for (int i = 0; i < 5; i++) {
		petals[i].x = x+20;
		petals[i].y = y-25;
	}
	petals[5].x = 0;
	petals[5].y = 0;
}

void start_drawing_lots_of_petals(int x, int y) {
	drawing_petals = true;
	for (int i = 0; i < 50; i++) {
		petals[i].x = x+20+prandom(10);
		petals[i].y = y-25+prandom(20);
	}
}

void draw_petals(SDL_Surface* sfc) {
	if (drawing_petals) {
		for (int i = 0; i < 50; i++) {
			if (petals[i].x == 0 && petals[i].y == 0) {
				break;
			}
			// animate
			int move_dir = rand() % 9;
			if (move_dir < 3) {
				petals[i].x += 1;
			} else if (move_dir < 5) {
				petals[i].x += 1;
				petals[i].y += 1;
			} else if (move_dir == 5) {
				petals[i].y += 1;
			} else if (move_dir == 6) {
				petals[i].x -= 1;
				petals[i].y += 1;
			} else if (move_dir == 7) {
				petals[i].x -= 1;
			} else {
				petals[i].x += 1;
				petals[i].x -= 1;
			}
			if (rand()%10) {
				petals[i].type = rand() % 4;
			}
			// draw
			image_type* petal_img = get_image(id_chtab_5_guard, 34 + petals[i].type);
			if (petal_img) {
				method_1_blit_rect(sfc, petal_img, &(rect_type){petals[i].y,petals[i].x,2,2}, &(rect_type){0,0,2,2}, blitters_10h_transp);
			}
		}
	}
}

image_type* silhouette_of(image_type* image, rgb_type colour) {
	if (image == NULL) {
		return SDL_CreateRGBSurface(0,1,1,32,Rmsk,Gmsk,Bmsk,Amsk);
	}
        int w = image->w;
        int h = image->h;
        if (SDL_SetColorKey(image, SDL_FALSE, 0) != 0) {
                sdlperror("silhouette_of: SDL_SetColorKey");
                quit(1);
        }
        SDL_Surface* coloured_image = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_ARGB8888, 0);

        SDL_SetSurfaceBlendMode(coloured_image, SDL_BLENDMODE_NONE);

        if (SDL_LockSurface(coloured_image) != 0) {
                sdlperror("silhouette_of_mono: SDL_LockSurface");
                quit(1);
        }
	uint32_t rgb_colour = SDL_MapRGB(coloured_image->format, colour.r, colour.g, colour.b) & 0xFFFFFF;
        int stride = coloured_image->pitch;
        for (int y = 0; y < h; ++y) {
                uint32_t* pixel_ptr = (uint32_t*) ((byte*)coloured_image->pixels + stride * y);
                for (int x = 0; x < w; ++x) {
                        // set RGB but leave alpha
                        *pixel_ptr = (*pixel_ptr & 0xFF000000) | rgb_colour;
                        ++pixel_ptr;
                }
        }
        SDL_UnlockSurface(coloured_image);
	return coloured_image;
}

int pause_timer = 0;

void pause_controls(int frames) {
	// for in-game cutscenes at the start of duels
	pause_timer = frames;
	controls_paused = true;
}

void manage_pause_controls() {
	if (pause_timer <= 0) {
		controls_paused = false;
	} else {
		pause_timer--;
	}
}

int touga_face_turn = 0;
int touga_face_turn_counter = 0;

void draw_background(SDL_Surface* surface) {
	if (current_level == 14 && drawn_room < 6) {
		method_1_blit_rect(surface, get_image(id_chtab_6_environment, 184 + touga_face_turn), &rect_top, &rect_top, blitters_0_no_transp);
	} else {
		draw_rect_rgb_to(surface, &rect_top, bg_colour);
	}
}

void start_face_turn() {
	if (touga_face_turn == 0) {
		touga_face_turn = 1;
	}
}

void manage_face_turn() {
	if (touga_face_turn > 0 && touga_face_turn < 4) {
		if (touga_face_turn_counter < 3) {
			touga_face_turn_counter++;
		} else {
			touga_face_turn_counter = 0;
			touga_face_turn++;
		}
	}
}

image_type* make_greenscreen_transparent(image_type* image) {
        SDL_Surface* modified_image = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_ARGB8888, 0);
        if (SDL_SetColorKey(modified_image, SDL_TRUE, 0xFF00FF00) != 0) {
                sdlperror("make_greenscreen_transparent: SDL_SetColorKey");
                quit(1);
        }
	return modified_image;
}

int smoke_tick = 0;

void manage_smoke_cloud() {
	smoke_tick = (smoke_tick + 1) % 8;
	if (draw_smoke && smoke_tick==0) {
		smoke_cloud_base = chtab_title50->images[5];
		int motion_x_a = prandom(1);
		int motion_x_b = prandom(20) - 9;
		SDL_FreeSurface(smoke_cloud_helper_surface);
		smoke_cloud_helper_surface = SDL_CreateRGBSurface(0,320,200,32,Rmsk,Gmsk,Bmsk,Amsk);
		SDL_SetSurfaceAlphaMod(smoke_cloud_helper_surface, 250);
		if (smoke_cloud_surface == NULL) {
			smoke_cloud_surface = SDL_CreateRGBSurface(0,320,200,32,Rmsk,Gmsk,Bmsk,Amsk);
		}
		SDL_SetColorKey(smoke_cloud_base, SDL_FALSE, 0);
		SDL_SetColorKey(smoke_cloud_surface, SDL_FALSE, 0);
		SDL_SetColorKey(smoke_cloud_helper_surface, SDL_FALSE, 0);
		method_1_blit_rect(smoke_cloud_helper_surface, smoke_cloud_surface, &(rect_type){-1,motion_x_a,200-3,320+motion_x_a}, &(rect_type){0,0,200,320}, blitters_10h_transp);
		method_1_blit_rect(smoke_cloud_helper_surface, smoke_cloud_base, &(rect_type){130,195+motion_x_b,smoke_cloud_base->h,smoke_cloud_base->w+motion_x_b}, &(rect_type){0,0,smoke_cloud_base->h,smoke_cloud_base->w}, blitters_10h_transp);
		SDL_FreeSurface(smoke_cloud_surface);
		smoke_cloud_surface = SDL_CreateRGBSurface(0,320,200,32,Rmsk,Gmsk,Bmsk,Amsk);
		method_1_blit_rect(smoke_cloud_surface, smoke_cloud_helper_surface, &rect_top, &rect_top, blitters_10h_transp);
	}
}

void manage_touga_enter() {
	touga_enter_count++;
	if (touga_enter_count == 100) {
		level.guards_tile[5] = Kid.curr_col+2;
		level.guards_dir[5] = dir_FF_left;
		level.guards_skill[5] = 6;
		pos_guards();
		enter_guard();
	}
}

int princess_text_frames = 0;
char* princess_text = "";

void add_princess_text(const char* text, int frames) {
	princess_text_frames = frames;
	princess_text = (char*)text;
}

void draw_princess_text() {
	show_text(&(rect_type){0,0,190,320}, 0, 1, princess_text);
}

void manage_princess_text() {
	if (princess_text_frames > 0) {
		princess_text_frames--;
		memset(table_counts, 0, sizeof(table_counts));
		add_foretable(id_chtab_8_princessroom, 2, 0, 0, 192, blitters_0_no_transp, 0); // text box, draw_princess_text is called from draw_back_fore
		draw_tables();
	}
}

int a_ko_frame = 0;
int b_ko_frame = 0;
int a_ko_animation = 0;
int b_ko_animation = 0;

int animation_0_standing[] = {0};
int animation_1_squatting[] = {0, 1, 2, 3, 3, 3, 2, 1, 0, 0};

int* animations[] = {animation_0_standing, animation_1_squatting};
int animation_lengths[] = {1, 10}; // silly, i know

void manage_kashira() {
	a_ko_frame = (a_ko_frame + 1) % animation_lengths[a_ko_animation];
	b_ko_frame = (b_ko_frame + 1) % animation_lengths[b_ko_animation];

	memset(table_counts, 0, sizeof(table_counts));
	add_foretable(id_chtab_8_princessroom, 1, 0, 0, 200, blitters_0_no_transp, 0);
	add_foretable(id_chtab_3_princessinstory, animations[a_ko_animation][a_ko_frame]+1, 5, 0, 180, blitters_10h_transp, 0);
	add_foretable(id_chtab_4_jaffarinstory_princessincutscenes, animations[b_ko_animation][b_ko_frame]+1, 20, 0, 180, blitters_10h_transp, 0);
	draw_tables();
	manage_princess_text();
}

void set_kashira_animations(int a_ko, int b_ko) {
	if (a_ko >= 0) {
		a_ko_animation = a_ko;
		a_ko_frame = 0;
	}
	if (b_ko >= 0) {
		b_ko_animation = b_ko;
		b_ko_frame = 0;
	}
}
