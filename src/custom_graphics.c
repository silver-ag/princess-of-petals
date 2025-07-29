#include "common.h"

typedef struct petal_t {
	int x;
	int y;
	int type;
} petal_t;

petal_t petals[5];

void start_death_flash(int frames) {
	stored_colour = bg_colour;
	death_flash_frames = frames;
}

void death_flash() {
	if (death_flash_frames > 1 || (Kid.alive < 0 && death_flash_frames == 1)) { // final frame only resets if kid is alive
		death_flash_frames--;
		if (death_flash_frames % 2) {
			bg_colour = (rgb_type){255,0,0};
			silhouette_mode = true;
		} else {
			bg_colour = stored_colour;
			if (current_level != 9) { // while in shadow world, don't flash regular
				silhouette_mode = false;
			}
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

image_type* silhouette_of(image_type* image) {
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
	uint32_t rgb_colour = SDL_MapRGB(coloured_image->format, 0, 0, 0) & 0xFFFFFF;
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
