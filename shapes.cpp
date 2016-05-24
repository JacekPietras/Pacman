#include "shapes.h"

void ghost(float x, float z) {
	setPacmanMaterial();
	glTranslatef(x*spacing, -1, z*spacing);
	glRotatef(180, 0, 1, 0);
	glScalef(.15f, .15f, .15f);
	rysujModel("ghost");
}

float pacmanRot = 0, pacmanRotDelta = 1;
void pacman(float x, float z, GameState & gs) {
	setPacmanMaterial();
	glTranslatef(x*spacing, 0, z*spacing);
	glScalef(.2f, .2f, .15f);
	glRotatef(gs.pacmanAngle, 0, 1, 0);
	glPushMatrix();
		glRotatef(-pacmanRot, 0, 0, 1);
		rysujModel("pacman");
	glPopMatrix();
	glRotatef(pacmanRot, 0, 0, 1);
	rysujModel("pacman2");

	pacmanRot += pacmanRotDelta;
	if (pacmanRot > 15 || pacmanRot < 0)
		pacmanRotDelta = -pacmanRotDelta;
}

void text(float x, float y, char *str) {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, oknoSzerkosc, 0, oknoWysokosc);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);


	glRasterPos2f(x, y);

	glColor3f(1, 1, 1);
	for (int i = 0; i < strlen(str); ++i) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	}

	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void hud(float x, float y, GameState & gs) {
	char points[4];
	itoa(gs.points, points, 10);
	char score[13] = "Points : ";
	strcat(score, points);
	text(x, y, score);
}
