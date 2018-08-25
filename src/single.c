#include "single.h"

int start_single(vita2d_pgf *pgf, SceCtrlData *pad) {

	//Player HP, X, Y, W and H
	Player p1;
	p1.X = 420;
	p1.Y = SCREEN_H / 2;
	p1.W = 50;
	p1.H = 50;
	p1.HP = 5;
	p1.i_frames = 0;

	//Total Score
	int total_score = 0;

	//Time for enemies
	int init_time = 300;
	int decrease_time = 10;
	int timer = init_time;

	//Player 1 Projectiles
	Projectile p1_bullets[MAX_PROJECTILES];
	for(int i = 0; i < MAX_PROJECTILES; i++) {
		p1_bullets[i].active = 0; 
	}

	//Enemies
	Enemy enemies[MAX_ENEMIES];
	for (int i = 0; i < MAX_ENEMIES; i++) {
		enemies[i].HP = 0;
	}

	//Enemy Projectiles
/*	Projectile enemy_bullets[MAX_PROJECTILES];
	for (int i = 0; i < MAX_PROJECTILES; i++) {
		enemy_bullets[i].active = 0;
	}*/

	//Random seed
	srand(time(NULL));

	while (1) {
		vita2d_start();

		//Control update
		sceCtrlPeekBufferPositive(0, pad, 1);
		leftAnalogUpdate(pad, &p1.X, &p1.Y);
		boundaryCheck(&p1);

		//P1 Shoot?
		updatePlayerBullets(pad, p1_bullets, p1.X, p1.Y);

		//Enemies update
		total_score += updateEnemies(enemies, p1.X, p1.Y, p1_bullets);

		//Add enemies?
		if (timer <= 0) {
			//Add an enemy if slot available
			addEnemies(enemies);

			//Reset timer accordinglyfornext new enemy
			if (init_time > 30) {
				init_time -= decrease_time;
			}
			timer = init_time;
		}
		//Wait
		else {
			timer--;
		}

		//Check P1 HP and invincibility frames
		if ((checkPlayerHP(&p1, enemies) == -1) && (p1.i_frames <= 0)) {
			p1.HP--;
			p1.i_frames = 120;
		} 
		else {
			p1.i_frames--;
		}

		//Exit to main menu
		if ((pad->buttons & SCE_CTRL_START) || (p1.HP <= 0)) {
			break;
		}

		//Draw the character hitbox
		vita2d_draw_rectangle(p1.X, p1.Y, p1.W, p1.H, BLUE);

		//Draw projectiles
		for (int i = 0; i < MAX_PROJECTILES; i++) {
			if(p1_bullets[i].active != 0) {
				vita2d_draw_rectangle(p1_bullets[i].X, p1_bullets[i].Y, p1_bullets[i].W, p1_bullets[i].H, WHITE);
			}
		}

		//Draw enemies
		for (int i = 0; i < MAX_ENEMIES; i++) {
			if (enemies[i].HP > 0) {
				vita2d_draw_rectangle(enemies[i].X, enemies[i].Y, enemies[i].W, enemies[i].H, RED);
			}
		}

		//Draw Score
		char *score_str = (char *) malloc(sizeof(char) * 70);
		sprintf(score_str, "Score: %d", total_score);
		vita2d_pgf_draw_text(pgf, 0, 20, WHITE, 1.0f, score_str);

		//Draw P1 HP
		vita2d_pgf_draw_text(pgf, 0, SCREEN_H - 40, WHITE, 1.0f, "HP");
		int HP_rect_X = 0;
		//Draws P1 remaining green HP
		for (int i = 0; i < p1.HP; i++) {
			vita2d_draw_rectangle(HP_rect_X, SCREEN_H - 30, 40, 30, GREEN);
			HP_rect_X += 50;
		}
		//Draws P1 lost red HP
		for (int i = 0; i < (P1MAXHP - p1.HP); i++) {
			vita2d_draw_rectangle(HP_rect_X, SCREEN_H - 30, 40, 30, RED);
			HP_rect_X += 50;
		}

		vita2d_end();
	}

	return 0;
}