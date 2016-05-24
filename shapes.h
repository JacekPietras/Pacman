#pragma once

#include "main.h"
#include <windows.h>
#include <GL/glu.h>
#include "glut.h"
#include "models.h"
#include "textures.h"
#include "materials.h"

#define BLACK 0
#define BLUE 1

void ghost(float x, float z);
void pacman(float x, float z, GameState & gs);
void text(float x, float y, char * str);
void hud(float x, float y, GameState & gs);
void points(int ** map);
