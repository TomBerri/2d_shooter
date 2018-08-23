#include "enemy.h"

static void enemyPathing(Enemy *e, int p1X, int p1Y) {
	int diff_X = e->X - p1X;
	int diff_Y = e->Y - p1Y;

	if ((e->X < boundaryXLeft) || (e->X > boundaryXRight) || 
		(e->Y <= boundaryYUp) || (e->Y >= boundaryYDown) ||
		(abs(diff_X) > 150 && abs(diff_Y) > 150)) {
		
		double angle = atan2(-diff_Y, -diff_X) * 180 / PI;
		e->mov_X = (int)(ENEMY_SPEED*(cos(angle*PI / 180))); //Move X 
		e->mov_Y = (int)(ENEMY_SPEED*(sin(angle*PI / 180))); //Move Y
	}

	e->X += e->mov_X;
	e->Y += e->mov_Y;
}

void updateEnemies(Enemy *enemies, int p1X, int p1Y) {
	for (int i = 0; i < MAX_ENEMIES; i++) {
		if (enemies[i].HP > 0) {
			enemyPathing(&enemies[i], p1X, p1Y);
		}
	}
}