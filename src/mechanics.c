#include "mechanics.h"

//Start drawing function
void vita2d_start() {
	vita2d_start_drawing();
	vita2d_clear_screen();
}

//End drawing function
void vita2d_end() {
	vita2d_end_drawing();
	vita2d_swap_buffers();
	sceDisplayWaitVblankStart();
}

//Updates movement of player from left analog stick
void leftAnalogUpdate(SceCtrlData *ctrl, int *X, int *Y) {
	//Control square with left analog stick
	double tx, ty, angle;
	tx = 127.5 - ctrl->lx; //Center of joystick to actual joystick pos
	ty = 127.5 - ctrl->ly; //same as above but for y
	angle = atan2(-ty, -tx) * 180 / PI; //Angle for movement

	//Thresholding analog stick
	if (tx < -20 || tx > 20) {
		*X += (int) (SPEED*(cos(angle*PI / 180))); //Move X 
	}
	if (ty < -20 || ty > 20) {
		*Y += (int) (SPEED*(sin(angle*PI / 180))); //Move Y
	}
}

//Checks whether the coords are of the screen
void boundaryCheck(Player *p) {
	//Boundary checking
	if (p->X <= boundaryXLeft) {
		p->X = 0;
	}
	if (p->X >= boundaryXRight - p->W) {
		p->X = SCREEN_W - p->W;
	}
	if (p->Y <= boundaryYUp) {
		p->Y = 0;
	}
	if (p->Y >= boundaryYDown - p->H) {
		p->Y = SCREEN_H - p->H;
	}
}

//Checks whether any alive enemies are touching player
int checkPlayerHP(Player *p, Enemy *enemies, Projectile *e_b) {
	for (int i = 0; i < MAX_ENEMIES; i++) {
		if (enemies[i].HP > 0) {
			int diffX = enemies[i].X - p->X;
			int diffY = enemies[i].Y - p->Y;

			if ((diffX <= p->W) && (diffY <= p->H) && (diffX >= -enemies[i].W) && (diffY >= -enemies[i].H)) {
				return -1;
			}
		}
	}

	for (int i = 0; i < MAX_PROJECTILES; i++) {
		if (e_b[i].active != 0) {
			int diffX = e_b[i].X - p->X;
			int diffY = e_b[i].Y - p->Y;

			if ((diffX <= p->W) && (diffY <= p->H) && (diffX >= -e_b[i].W) && (diffY >= -e_b[i].H)) {
				return -1;
			}
		}
	}

	return 0;
}

//Adds a bullet to the inputted projectiles array if there is space available
void addBullet(Projectile *projectiles, int init_X, int init_Y, int v_X, int v_Y) {
	for(int i = 0; i < MAX_PROJECTILES; i++){
		if (projectiles[i].active == 0) {
			projectiles[i].active = 1;
			projectiles[i].X = init_X;
			projectiles[i].Y = init_Y;
			projectiles[i].W = BULL_W;
			projectiles[i].H = BULL_H;
			projectiles[i].mov_X = v_X;
			projectiles[i].mov_Y = v_Y;
			break;
		}
	}
}

//Moves each bullet in the inputted projectile array
void moveBullets(Projectile *projectiles) {
	for(int i = 0; i < MAX_PROJECTILES; i++){
		if (projectiles[i].active != 0) {
			projectiles[i].X += projectiles[i].mov_X;
			projectiles[i].Y += projectiles[i].mov_Y;

			//Check bullet is out of bounds
			if (projectiles[i].X <= boundaryXLeft || projectiles[i].X >= boundaryXRight - BULL_W 
				|| projectiles[i].Y <= boundaryYUp || projectiles[i].Y >= boundaryYDown - BULL_H) {
				projectiles[i].active = 0;
			}
		}
	}
}

//Updates the inputted projectiles array (moves and adds bullets)
void updatePlayerBullets(SceCtrlData *ctrl, Projectile *projectiles, Player *p) {
	double tx, ty, angle;
	int mov_X = 0; 
	int mov_Y = 0;
	tx = 127.5 - ctrl->rx; //Center of joystick to actual joystick pos
	ty = 127.5 - ctrl->ry; //same as above but for y
	angle = atan2(-ty, -tx) * 180 / PI; //Angle for movement

	//Thresholding analog stick
	if (tx < -40 || tx > 40) {
		mov_X = (int) (PROJECTILE_SPEED*(cos(angle*PI / 180))); //Move X 
	}
	if (ty < -40 || ty > 40) {
		mov_Y = (int) (PROJECTILE_SPEED*(sin(angle*PI / 180))); //Move Y
	}

	//Check the right analog stick has been moved
	if (mov_X != 0 || mov_Y != 0) {
		//Use mid-point of player for bullet origin
		addBullet(projectiles, (p->X + (p->W / 2)), (p->Y + (p->H / 2)), mov_X, mov_Y);
	}

	//Update movement of projectiles
	moveBullets(projectiles);
}