#include "enemy.h"

//Adds enemies to the game
static void addEnemies(Enemy *enemies) {
	static int init_time = 300;
	static int decrease_time = 10;
	static int timer = 300;

	if (timer <= 0) {

		for (int i = 0; i < MAX_ENEMIES; i++) {
			if (enemies[i].HP <= 0) {
				enemies[i].HP = 5;
				enemies[i].W = ENEMY_W;
				enemies[i].H = ENEMY_H;

				//Randomise starting position
				int rand_pos = rand() % 4;
				switch(rand_pos) {
					case(0):
						enemies[i].X = 0;
						break;
					case(1):
						enemies[i].X = SCREEN_W;
						break;
					case(2):
						enemies[i].Y = 0;
						break;
					case(3):
						enemies[i].Y = SCREEN_H;
						break;	
					default:
						enemies[i].Y = SCREEN_H;
				}

				if (rand_pos == 0 || rand_pos == 1) {
					enemies[i].Y = rand() % SCREEN_H + 1;
				}
				else {
					enemies[i].X = rand() % SCREEN_W + 1;
				}

				break;		
			}
		}

		//Reset timer
		if (init_time > 30) {
			init_time -= decrease_time;
		}
		timer = init_time;
	}

	else {
		timer--;
	}
}

//Configures the movement vector of the inputted enemy based on player position
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

//Checks whether a P1 bullet has hit an enemy
static int enemyHPCheck(Enemy *e, Projectile *p1_b) {
	//Check enemy against all P1 projectiles
	int score = 0;
	for (int i = 0; i < MAX_PROJECTILES; i++) {
		int diffX = e->X - p1_b[i].X;
		int diffY = e->Y - p1_b[i].Y;

		if ((diffX < e->W) && (diffY < e->H) && (diffX >= 0) && (diffY >= 0)) {
			e->HP--;
			if (e->HP <= 0) {
				score += 1;
			}
		}
	}

	return score;
}

//Updates the enemies array (movement, projectiles and adding)
int updateEnemies(Enemy *enemies, int p1X, int p1Y, Projectile *p1_b) {
	int total_score = 0;

	//Add Enemies
	addEnemies(enemies);

	//Enemy movement and HP checking
	for (int i = 0; i < MAX_ENEMIES; i++) {
		//Movement
		if (enemies[i].HP > 0) {
			enemyPathing(&enemies[i], p1X, p1Y);
		}
		//Enemy defeated / add to score
		total_score += enemyHPCheck(&enemies[i], p1_b);
	}

	return total_score;
}