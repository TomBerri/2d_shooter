#ifndef mechanics_h
#define mechanics_h

#include "main.h"

//Colours
#define BLACK RGBA8(0, 0, 0, 255)
#define GREEN RGBA8(0, 255, 0, 255)
#define RED RGBA8(255, 0, 0, 255)
#define BLUE RGBA8(0, 0, 255, 255)
#define WHITE RGBA8(255, 255, 255, 255)

//Screen dimensions
#define SCREEN_W 960
#define SCREEN_H 544

//Boundaries
#define boundaryXLeft 0
#define boundaryXRight SCREEN_W
#define boundaryYUp 0
#define boundaryYDown SCREEN_H

//Game constants
#define P1MAXHP 5
#define SPEED 5
#define PROJECTILE_SPEED 10
#define MAX_PROJECTILES 200
#define PI 3.14159
#define BULL_W 5
#define BULL_H 5

//Projectile type
typedef struct Projectiles{
	int active; //0 = not on screen, 1 = on screen
	int X; //Position of projectile on screen
	int Y;
	int W;
	int H;
	int mov_X; //Movement vector of projectile
	int mov_Y;
} Projectile;

//Player type
typedef struct Players {
	int HP;
	int X;
	int Y;
	int W;
	int H;
	int i_frames;
} Player;

//Enemy type
typedef struct Enemies {
	int HP;
	int X; //Position of projectile on screen
	int Y;
	int W;
	int H;
	int mov_X; //Movement vector of projectile
	int mov_Y;
} Enemy;

//Enemy constants
#define ENEMY_SPEED 4
#define MAX_ENEMIES 10
#define ENEMY_W 20
#define ENEMY_H 20

//Drawing starting and ending
void vita2d_start();
void vita2d_end();

//Player updaters
void leftAnalogUpdate(SceCtrlData *ctrl, int *X, int *Y);
void boundaryCheck(Player *p);
int checkPlayerHP(Player *p, Enemy *enemies);

//Projectile methods
void updatePlayerBullets(SceCtrlData *ctrl, Projectile *projectiles, int char_X, int char_Y);

#endif