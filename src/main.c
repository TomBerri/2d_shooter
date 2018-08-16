#include <psp2/display.h>
#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>

#include <vita2d.h>

#include <stdio.h>
#include <stdlib.h>

//Colours
#define BLACK RGBA8(0, 0, 0, 255)
#define GREEN RGBA8(0, 255, 0, 255)
#define RED RGBA8(255, 0, 0, 255)
#define BLUE RGBA8(0, 0, 255, 255)
#define WHITE RGBA8(255, 255, 255, 255)

//Screen Dimensions
#define SCREEN_W 960
#define SCREEN_H 544

//Boundaries
#define boundaryXLeft 0
#define boundaryXRight SCREEN_W
#define boundaryYUp 0
#define boundaryYDown SCREEN_H

//Main Menu selection rectangle
int mode_recX = 0;
int mode_recY = SCREEN_H - 110;
int mode_recW = 140;
int mode_recH = 28;

//Input frame count
int frame_count = 0;

int main(int argc, char *argv[]) {
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
		vita2d_start_drawing();
		vita2d_clear_screen();

		sceCtrlPeekBufferPositive(0, &pad, 1);

		//Draw mode rectangle
		vita2d_draw_rectangle(mode_recX, mode_recY, mode_recW, mode_recH, GREEN);

		//Main Menu
		vita2d_pgf_draw_text(pgf, 215, SCREEN_H / 2, BLUE, 3.0f, "2D Shooter Alpha");
		vita2d_pgf_draw_text(pgf, 10, SCREEN_H - 90, RED, 1.0f, "Single-player");
		vita2d_pgf_draw_text(pgf, 10, SCREEN_H - 60, RED, 1.0f, "Multi-player");
		vita2d_pgf_draw_text(pgf, 10, SCREEN_H - 30, RED, 1.0f, "Settings");

		//Main Menu controls
		if (pad.buttons & SCE_CTRL_CROSS) {
			vita2d_clear_screen();
			break;
		}
		
		if (pad.buttons & SCE_CTRL_DOWN) {
			if (mode < 2 && frame_count == 0) {
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
		vita2d_end_drawing();
		vita2d_swap_buffers();
		sceDisplayWaitVblankStart();
	}

	vita2d_fini();
	vita2d_free_pgf(pgf);
	sceKernelExitProcess(0);
	return 0;
}