#ifndef DRAW_SCENE_H
#define DRAW_SCENE_H
#include <windows.h>
#include <GL/glu.h>
#include "glut.h"
#include "map_planner.h"
#include <stdio.h>
#include <stdlib.h> 
#include "main.h"

void drawInit();
void drawScene(GameState &gs);

#endif