#include "enemy.h"

//Adds enemies to the game
void addEnemies(Enemy *enemies) {
	//For each enemy until one is dead...
	for (int i = 0; i < MAX_ENEMIES; i++) {
		if (enemies[i].HP <= 0) {
			enemies[i].HP = 5;
			enemies[i].W = ENEMY_W;
			enemies[i].H = ENEMY_H;
			enemies[i].shoot = 180 + (rand() % 180); //Random time between 3 - 6 seconds

			//Randomise starting position (X and Y)
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
	for (int i = 0; i < MAX_PROJECTILES; i++) {
		if (p1_b[i].active != 0) {
			int diffX = p1_b[i].X - e->X;
			int diffY = p1_b[i].Y - e->Y;

			if ((diffX <= e->W) && (diffY <= e->H) && (diffX >= -p1_b[i].W) && (diffY >= -p1_b[i].H)) {
				e->HP--;
				p1_b[i].active = 0;
				if (e->HP <= 0) {
					return 1;
				}
			}
		}
	}

	return 0;
}

//Updates the enemies array (movement, projectiles and adding)
int updateEnemies(Enemy *enemies, int p1X, int p1Y, Projectile *p1_b, Projectile *e_b) {
	int score = 0;

	//Enemy movement and HP checking
	for (int i = 0; i < MAX_ENEMIES; i++) {
		if (enemies[i].HP > 0) {
			//Adjust movement of enemy
			enemyPathing(&enemies[i], p1X, p1Y);
			//Enemy defeated / add to score
			score += enemyHPCheck(&enemies[i], p1_b);
			//Does the enemy shoot?
			if (enemies[i].shoot <= 0) {
				double angle = atan2(enemies[i].mov_Y, enemies[i].mov_X) * 180 / PI;
				int mov_X = (int)(PROJECTILE_SPEED*(cos(angle*PI / 180))); //Move X 
				int mov_Y = (int)(PROJECTILE_SPEED*(sin(angle*PI / 180))); //Move Y
				addBullet(e_b, (enemies[i].X + (enemies[i].W / 2)), (enemies[i].Y + (enemies[i].H / 2)), mov_X, mov_Y);
				enemies[i].shoot = 180 + (rand() % 180); //Random time between 3 - 6 seconds
			}
			else {
				enemies[i].shoot--;
			}
		}
	}

	//Move enemy bullets
	moveBullets(e_b);

	return score;
}