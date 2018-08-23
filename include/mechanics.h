#ifndef mechanics_h
#define mechanics_h

#include "main.h"

//Colours
#define BLACK RGBA8(0, 0, 0, 255)
#define GREEN RGBA8(0, 255, 0, 255)
#define RED RGBA8(255, 0, 0, 255)
#define BLUE RGBA8(0, 0, 255, 255)
#define WHITE RGBA8(255, 255, 255, 255)

//Screen Dimensions
#define SCREEN_W 960
#define SCREEN_H 544

//Boundaries
#define boundaryXLeft 0
#define boundaryXRight SCREEN_W
#define boundaryYUp 0
#define boundaryYDown SCREEN_H

//Game variables
#define SPEED 5
#define PROJECTILE_SPEED 10
#define MAX_PROJECTILES 200
#define MAX_ENEMIES 1
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

//Drawing starting and ending
void vita2d_start();
void vita2d_end();

//Control updaters
void leftAnalogUpdate(SceCtrlData *ctrl, int *X, int *Y);
void boundaryCheck(int *X, int *Y, int W, int H);

//Projectile methods
void updateP1Bullets(SceCtrlData *ctrl, Projectile *projectiles, int char_X, int char_Y);

#endif