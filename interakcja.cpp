#include "interakcja.h"

// Kamera
int pozycjaMyszyX;						// na ekranie
int pozycjaMyszyY;
double kameraX;
double kameraY;
double kameraZ;
double kameraPunktY;
double kameraPredkoscPunktY;
double kameraPredkosc;
bool kameraPrzemieszczanie;		// przemieszczanie lub rozgl¹danie
double kameraKat;				// kat patrzenia
double kameraPredkoscObrotu;
double obszarKamery = 0;

enum Direction { Forward, Right, Back, Left };
bool movementKeysState[4];

void SzablonPrzyciskMyszyWcisniety(int button, int state, int x, int y)
{
	switch (state)
	{
	case GLUT_UP:
		kameraPredkosc = 0;
		kameraPredkoscObrotu = 0;
		kameraPredkoscPunktY = 0;
		break;
	case GLUT_DOWN:
		pozycjaMyszyX = x;
		pozycjaMyszyY = y;
		if (button == GLUT_LEFT_BUTTON)
			kameraPrzemieszczanie = true;
		else
			kameraPrzemieszczanie = false;
		break;
	}
}

void SzablonRuchKursoraMyszy(int x, int y)
{
	kameraPredkoscObrotu = -(pozycjaMyszyX - x) * 0.001;
	if (kameraPrzemieszczanie)
	{
		kameraPredkosc = (pozycjaMyszyY - y) * 0.02;
		kameraPredkoscPunktY = 0;
	}
	else {
		kameraPredkoscPunktY = (pozycjaMyszyY - y) * 0.06;
		kameraPredkosc = 0;
	}
}

void SzablonKlawiszKlawiaturyWcisniety(GLubyte key, int x, int y)
{
	switch (key) {
	case 27:
		exit(1);
		break;
	}

}

/******************* SZABLON **************************/

// DEFINICJE FUNKCJI OBS£UGUJ¥CYCH ZDARZENIA MYSZY I KLAWIATURY	

void PrzyciskMyszyWcisniety(int button, int state, int x, int y)
{
	SzablonPrzyciskMyszyWcisniety(button, state, x, y); // wywolanie standardowej obslugi zdarzen szablonu 


	//*************************************************************
	// tu mo¿na umieœciæ kod obs³uguj¹cy wciœniêcie przycisku myszy



}

void RuchKursoraMyszy(int x, int y)
{
	SzablonRuchKursoraMyszy(x, y); // wywolanie standardowej obslugi zdarzen szablonu 

	//****************************************************
	//tu mo¿na umieœciæ kod obs³uguj¹cy ruch kursora myszy

}

void onKeyDown(GLubyte key, int x, int y)
{
	SzablonKlawiszKlawiaturyWcisniety(key, x, y);	// wywolanie standardowej obslugi zdarzen szablonu 

	//*******************************************************************************
	// tu mo¿na umieœciæ kod obs³uguj¹cy wciœniêcie klawisza klawiatury, przyk³adowo:

	switch (key)
	{
	case 'e':
		glEnable(GL_FOG);
		break;
	case 'q':
		glDisable(GL_FOG);
		break;
	case 'w':
		movementKeysState[Forward] = true;
		break;
	case 's':
		movementKeysState[Back] = true;
		break;
	case 'a':
		movementKeysState[Left] = true;
		break;
	case 'd':
		movementKeysState[Right] = true;
		break;
	}
}

void onKeyUp(GLubyte key, int x, int y) {
	switch (key)
	{
	case 'w':
		movementKeysState[Forward] = false;
		break;
	case 's':
		movementKeysState[Back] = false;
		break;
	case 'a':
		movementKeysState[Left] = false;
		break;
	case 'd':
		movementKeysState[Right] = false;
		break;
	}
}

//Called each frame
void move(bool key, GameState &gs, float dx, float dz, int rotation) {
	if (key) {
		int x = gs.pacmanPosX + dx;
		int z = gs.pacmanPosZ + dz ;

		int nextTile = gs.map[x][z];
		if (nextTile == 2 || nextTile == 3) {
			gs.pacmanLastX = gs.pacmanPosX;
			gs.pacmanLastZ = gs.pacmanPosZ;
			gs.pacmanPosX = x;
			gs.pacmanPosZ = z;
			gs.pacmanAngle = rotation;
			if (nextTile == 3) {
				gs.map[x][z] = 2;
				gs.points++;
			}
		}
	}
}
void handleMovement(GameState &gs) {
	move(movementKeysState[Forward], gs, 1, 0, 0);
	move(movementKeysState[Back], gs, -1, 0,180);
	move(movementKeysState[Right], gs, 0, 1,-90);
	move(movementKeysState[Left], gs, 0, -1,90);
}

void KlawiszSpecjalnyWcisniety(GLint key, int x, int y)
{
	//*******************************************************************************
	// tu mo¿na umieœciæ kod obs³uguj¹cy wciœniêcie specjalnego klawisza klawiatury, przyk³adowo:

	switch (key)
	{
	case GLUT_KEY_LEFT:

		break;
	case GLUT_KEY_RIGHT:

		break;
	case GLUT_KEY_UP:

		break;
	case GLUT_KEY_DOWN:

		break;

	}
}
