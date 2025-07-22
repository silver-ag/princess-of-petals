#include "common.h"

typedef struct petal_t {
	int x;
	int y;
	int type;
} petal_t;

petal_t petals[5];

void death_flash() {
	if (death_flash_frames > 1 || (Kid.alive < 0 && death_flash_frames == 1)) { // final frame only resets if kid is alive
		death_flash_frames--;
		if (death_flash_frames % 2) {
			stored_colour = bg_colour;
			bg_colour = (rgb_type){255,0,0};
		} else {
			bg_colour = stored_colour;
		}
		need_full_redraw = 1;
	}
}

void start_drawing_petals(int x, int y) {
	drawing_petals = true;
	for (int i = 0; i < 5; i++) {
		petals[i].x = x+20;
		petals[i].y = y-25;
	}
}

void draw_petals(SDL_Surface* sfc) {
	if (drawing_petals) {
		for (int i = 0; i < 5; i++) {
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
