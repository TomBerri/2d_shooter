#include "enemy.h"

static void enemyPathing(Enemy *e, int p1X, int p1Y) {
	if ((e->X < boundaryXLeft) || (e->X > boundaryXRight) || (e->Y <= boundaryYUp) || (e->Y >= boundaryYDown)) {
		int diff_X = e->X - p1X;
		int diff_Y = e->Y - p1Y;

	}
	else {
		e->X += e->mov_X;
		e->Y += e->mov_Y;
	}
}

void updateEnemies(Enemy *enemies, int p1X, int p1Y) {

}