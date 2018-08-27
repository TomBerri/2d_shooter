#include "settings.h"

int start_settings(vita2d_pgf *pgf, SceCtrlData *pad) {

	//Main Menu selection rectangle
	int mode_recX = 0;
	int mode_recY = 10;
	int mode_recW = 140;
	int mode_recH = 28;

	//Input frame count
	int frame_count = 0;

	//Mode enum
	int mode = 0;

	//Settings and Cheats values loaded in from config.txt
	int swapAnalogSticks;
	int infiniteHealth;

	SceUID config = sceIoOpen("ux0:/data/TOMB00004/config.txt", 0777, SCE_O_RDWR);
	if (config < 0) {
		config = sceIoOpen("ux0:/data/TOMB00004/config.txt", 0777, SCE_O_CREAT);
		int swapAnalogSticks = 0;
		int infiniteHealth = 0;
	}
	else {
		//Read in from file
	}

	while (1) {
		vita2d_start();

		sceCtrlPeekBufferPositive(0, pad, 1);

		//Draw mode rectangle
		vita2d_draw_rectangle(mode_recX, mode_recY, mode_recW, mode_recH, GREEN);

		//Settings Menu
		vita2d_pgf_draw_text(pgf, 10, 30, RED, 1.0f, "Settings:");
		vita2d_pgf_draw_text(pgf, 40, 60, RED, 1.0f, "Swap Analog Sticks");
		vita2d_pgf_draw_text(pgf, 10, 90, RED, 1.0f, "Cheat Codes:");
		vita2d_pgf_draw_text(pgf, 40, 120, RED, 1.0f, "Infinite Health");

		//Settings Menu controls
		if (pad->buttons & SCE_CTRL_CROSS) {

			switch (mode) {
				case 0:
					if (swapAnalogSticks == 0) {
						swapAnalogSticks = 1;
					}
					else {
						swapAnalogSticks = 0;
					}
					break;

				case 1:
					if (infiniteHealth == 0) {
						infiniteHealth = 1;
					}
					else {
						infiniteHealth = 0;
					}
					break;

				default:
					break;
			}
		}

		if (pad->buttons & SCE_CTRL_DOWN) {
			if (mode < 1 && frame_count == 0) {
				mode++;
				mode_recY += 60;
				frame_count++;
			}
		}

		if (pad->buttons & SCE_CTRL_UP) {
			if (mode > 0 && frame_count == 0) {
				mode--;
				mode_recY -= 60;
				frame_count++;
			}
		}

		if (pad->buttons & SCE_CTRL_START) {
			break;
		}

		//Increment frame counter
		if (frame_count > 10) {
			frame_count = 0;
		}
		else if (frame_count != 0) {
			frame_count++;
		}

		vita2d_end();
	}

	//Write changes back to file

	return 0;
}