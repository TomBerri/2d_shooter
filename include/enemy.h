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

#define ENEMY_SPEED 5

void updateEnemies(Enemy *enemies, int p1X, int p1Y);

#endif