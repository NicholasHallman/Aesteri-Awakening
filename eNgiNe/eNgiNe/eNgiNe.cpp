#include "eNgiNe.h"

Stage * stageback;
Stage * eNgiNe_init(int w, int h, int fps) {

	allegro_init();
	install_keyboard();
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, "");
	set_color_depth(32);
	stageback = new Stage(w,h);
	stageback->setFPS(fps);
	int ret = 0; 	
	ret = set_gfx_mode(GFX_SAFE, w, h, 0, 0);
	if (ret != 0) {
		allegro_message(allegro_error);
	}
	return stageback;
}

