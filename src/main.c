#include "main.h"
#include "single.h"
#include "enemy.h"
#include "settings.h"

//Testing the branching stuff
//Hopefully works
int main(int argc, char *argv[]) {

	//Main Menu selection rectangle
	int mode_recX = 0;
	int mode_recY = SCREEN_H - 80;
	int mode_recW = 140;
	int mode_recH = 28;

	//Input frame count
	int frame_count = 0;

	vita2d_pgf *pgf;

	vita2d_init();
	vita2d_set_clear_color(BLACK);

	pgf = vita2d_load_default_pgf();

	SceCtrlData pad;

	//Enable analog sampling
	sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);

	//Mode enum
	int mode = 0;

	while (1) {
		vita2d_start();

		sceCtrlPeekBufferPositive(0, &pad, 1);

		//Draw mode rectangle
		vita2d_draw_rectangle(mode_recX, mode_recY, mode_recW, mode_recH, GREEN);

		//Main Menu
		vita2d_pgf_draw_text(pgf, 215, SCREEN_H / 2, BLUE, 3.0f, "2D Shooter Alpha");
		vita2d_pgf_draw_text(pgf, 10, SCREEN_H - 60, RED, 1.0f, "Play Game");
		vita2d_pgf_draw_text(pgf, 10, SCREEN_H - 30, RED, 1.0f, "Settings and Cheats");

		//Main Menu controls
		if (pad.buttons & SCE_CTRL_CROSS) {

			//Enter selected mode
			vita2d_end();

			switch (mode) {
				case 0:
					start_single(pgf, &pad);
					break;

				case 1:
					start_settings(pgf, &pad);
					break;

				default:
					break;
			}
		}
		
		if (pad.buttons & SCE_CTRL_DOWN) {
			if (mode < 1 && frame_count == 0) {
				mode++;
				mode_recY += 30;
				frame_count++;
			}
		}

		if (pad.buttons & SCE_CTRL_UP) {
			if (mode > 0 && frame_count == 0) {
				mode--;
				mode_recY -= 30;
				frame_count++;
			}
		}

		//Increment frame counter
		if (frame_count > 10) {
			frame_count = 0;
		}
		else if (frame_count != 0) {
			frame_count++;
		}

		//End initial drawing and swap buffers
		vita2d_end();
	}

	vita2d_fini();
	vita2d_free_pgf(pgf);
	sceKernelExitProcess(0);
	return 0;
}