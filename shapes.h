#pragma once

#include "main.h"
#include <windows.h>
#include <GL/glu.h>
#include "glut.h"
#include "models.h"
#include "materials.h"

void ghost(float x, float z);
void pacman(float x, float z, GameState & gs);
void text(float x, float y, char * str);
void hud(float x, float y, GameState & gs);
