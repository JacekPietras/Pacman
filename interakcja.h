#pragma once

#include "glut.h"
#include "main.h"

// Kamera
extern int pozycjaMyszyX;						// na ekranie
extern int pozycjaMyszyY;
extern double kameraX;
extern double kameraY;
extern double kameraZ;
extern double kameraPunktY;
extern double kameraPredkoscPunktY;
extern double kameraPredkosc;
extern bool kameraPrzemieszczanie;		// przemieszczanie lub rozgl¹danie
extern double kameraKat;				// kat patrzenia
extern double kameraPredkoscObrotu;
#define MIN_DYSTANS 0.5			// minimalny dystans od brzegu obszaru ograniczenia kamery
extern double obszarKamery;

void handleMovement(GameState &gs);
void onKeyDown(GLubyte key, int x, int y);
void onKeyUp(GLubyte key, int x, int y);
void KlawiszSpecjalnyWcisniety(GLint key, int x, int y);

void RuchKursoraMyszy(int x, int y);
void PrzyciskMyszyWcisniety(int button, int state, int x, int y);
