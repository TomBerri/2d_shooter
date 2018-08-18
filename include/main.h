#ifndef main_h
#define main_h

#include <psp2/display.h>
#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/threadmgr.h>

#include <vita2d.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

//Speed
#define SPEED 3

//Drawing starting and ending
void vita2d_start();
void vita2d_end();

//Control updaters
void analogUpdate(SceCtrlData *ctrl, int *X, int *Y);
void boundaryCheck(int *X, int *Y, int W, int H);

#endif