#include "single.h"

int start_single(vita2d_pgf *pgf, SceCtrlData *pad) {

	//Character X, Y, W, H
	int p1X = 420;
	int p1Y = SCREEN_H / 2;
	int p1W = 50;
	int p1H = 50;

	//Projectiles
	Projectile projectiles[MAX_PROJECTILES];
	for(int i = 0; i < MAX_PROJECTILES; i++) {
		projectiles[i].active = 0; 
	}

	while (1) {
		vita2d_start();

		//Control update
		sceCtrlPeekBufferPositive(0, pad, 1);
		leftAnalogUpdate(pad, &p1X, &p1Y);
		boundaryCheck(&p1X, &p1Y, p1W, p1H);

		//Shoot?
		updateProjectiles(pad, projectiles, p1X, p1Y);

		//Exit to main menu
		if (pad->buttons & SCE_CTRL_START) {
			break;
		}

		//Draw the character hitbox
		vita2d_draw_rectangle(p1X, p1Y, p1W, p1H, BLUE);

		//Draw projectiles
		for (int i = 0; i < MAX_PROJECTILES; i++) {
			if(projectiles[i].active != 0) {
				vita2d_draw_rectangle(projectiles[i].X, projectiles[i].Y, projectiles[i].W, projectiles[i].H, WHITE);
			}
		}
	
		vita2d_end();
	}

	return 0;
}