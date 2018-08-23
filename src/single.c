#include "single.h"

int start_single(vita2d_pgf *pgf, SceCtrlData *pad) {

	//Character X, Y, W, H
	int p1X = 420;
	int p1Y = SCREEN_H / 2;
	int p1W = 50;
	int p1H = 50;

	//Player 1 Projectiles
	Projectile p1_bullets[MAX_PROJECTILES];
	for(int i = 0; i < MAX_PROJECTILES; i++) {
		p1_bullets[i].active = 0; 
	}

	//Enemies
	Enemy enemies[MAX_ENEMIES];
	for (int i = 0; i < MAX_ENEMIES; i++) {
		enemies[i].X = SCREEN_W / 2;
		enemies[i].Y = SCREEN_H / 2;
		enemies[i].W = 20;
		enemies[i].H = 20;
		enemies[i].H = 20;
		enemies[i].mov_X = 5;
		enemies[i].mov_Y = 5;
		enemies[i].HP = 1;
	}

	//Enemy Projectiles
/*	Projectile enemy_bullets[MAX_PROJECTILES];
	for (int i = 0; i < MAX_PROJECTILES; i++) {
		enemy_bullets[i].active = 0;
	}*/


	while (1) {
		vita2d_start();

		//Control update
		sceCtrlPeekBufferPositive(0, pad, 1);
		leftAnalogUpdate(pad, &p1X, &p1Y);
		boundaryCheck(&p1X, &p1Y, p1W, p1H);

		//P1 Shoot?
		updateP1Bullets(pad, p1_bullets, p1X, p1Y);

		//Enemies update
		updateEnemies(enemies, p1X, p1Y);

		//Exit to main menu
		if (pad->buttons & SCE_CTRL_START) {
			break;
		}

		//Draw the character hitbox
		vita2d_draw_rectangle(p1X, p1Y, p1W, p1H, BLUE);

		//Draw projectiles
		for (int i = 0; i < MAX_PROJECTILES; i++) {
			if(p1_bullets[i].active != 0) {
				vita2d_draw_rectangle(p1_bullets[i].X, p1_bullets[i].Y, p1_bullets[i].W, p1_bullets[i].H, WHITE);
			}
		}

		for (int i = 0; i < MAX_ENEMIES; i++) {
			if (enemies[i].HP >= 0) {
				vita2d_draw_rectangle(enemies[i].X, enemies[i].Y, enemies[i].W, enemies[i].H, RED);
			}
		}

		vita2d_end();
	}

	return 0;
}