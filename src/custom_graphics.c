#include "common.h"


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
