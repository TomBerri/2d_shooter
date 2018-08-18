#include "single.h"

int start_single(vita2d_pgf *pgf, SceCtrlData *pad) {

	//Character X, Y, W, H
	int p1X = 420;
	int p1Y = SCREEN_H / 2;
	int p1W = 50;
	int p1H = 50;

	while (1) {
		vita2d_start();

		//Control update
		sceCtrlPeekBufferPositive(0, pad, 1);
		analogUpdate(pad, &p1X, &p1Y);
		boundaryCheck(&p1X, &p1Y, p1W, p1H);

		//Exit to main menu
		if (pad->buttons & SCE_CTRL_START) {
			break;
		}

		//Draw the character
		vita2d_draw_rectangle(p1X, p1Y, p1W, p1H, BLUE);
	
		vita2d_end();
	}

	return 0;
}