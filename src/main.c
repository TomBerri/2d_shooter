#include "main.h"
#include "single.h"
#include "multi.h"
#include "settings.h"

//Main Menu selection rectangle
int mode_recX = 0;
int mode_recY = SCREEN_H - 110;
int mode_recW = 140;
int mode_recH = 28;

//Input frame count
int frame_count = 0;

//Start drawing function
void vita2d_start() {
	vita2d_start_drawing();
	vita2d_clear_screen();
}

//End drawing function
void vita2d_end() {
	vita2d_end_drawing();
	vita2d_swap_buffers();
	sceDisplayWaitVblankStart();
}

void analogUpdate(SceCtrlData *ctrl, int *X, int *Y) {
	//Control square with left analog stick
	double pi = 3.14159;
	double tx, ty, angle;
	tx = 127.5 - ctrl->lx; //Center of joystick to actual joystick pos
	ty = 127.5 - ctrl->ly; //same as above but for y
	angle = atan2(-ty, -tx) * 180 / pi; //Angle for movement

	//Thresholding analog stick
	if (tx < -20 || tx > 20) {
		X += (int) (SPEED*(cos(angle*pi / 180))); //Move X 
	}
	if (ty < -20 || ty > 20) {
		Y += (int) (SPEED*(sin(angle*pi / 180))); //Move Y
	}
}

void boundaryCheck(int *X, int *Y, int W, int H) {
	//Boundary checking
	if (X <= boundaryXLeft) {
		X = 0;
	}
	if (X >= boundaryXRight - W) {
		X = SCREEN_W - W;
	}
	if (Y <= boundaryYUp) {
		Y = 0;
	}
	if (Y >= boundaryYDown - H) {
		Y = SCREEN_H - H;
	}
}

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
		vita2d_start();

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

			//Enter selected mode
			vita2d_end();

			switch (mode) {
				case 0:
					start_single(pgf, &pad);
					break;

				case 1:
					start_multi(pgf, &pad);
					break;

				case 2:
					start_settings(pgf, &pad);
					break;

				default:
					break;
			}
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
		vita2d_end();
	}

	vita2d_fini();
	vita2d_free_pgf(pgf);
	sceKernelExitProcess(0);
	return 0;
}