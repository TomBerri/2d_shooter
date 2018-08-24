#ifndef multi_h
#define multi_h

#include "main.h"
#include "mechanics.h"

typedef struct Enemies{
	int HP;
	int X; //Position of projectile on screen
	int Y;
	int W;
	int H;
	int mov_X; //Movement vector of projectile
	int mov_Y;
} Enemy;

#define ENEMY_SPEED 4
#define MAX_ENEMIES 10
#define ENEMY_W 20
#define ENEMY_H 20

int updateEnemies(Enemy *enemies, int p1X, int p1Y, Projectile *p1_b);
void addEnemies(Enemy *enemies);

#endif