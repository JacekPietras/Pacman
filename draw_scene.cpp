#include "draw_scene.h"

int mapWidth = 20;
int mapHeight = 20;
MapPlanner planner(mapWidth, mapHeight);
int **map;

// Function fired on start
void drawInit() {
	planner.printSTD();
	map = planner.getArray();
	mapWidth = planner.getWidth();
	mapHeight = planner.getHeight();
}

// Function fired every frame
void drawScene() {
	GLUquadricObj *obiekt = gluNewQuadric();
	gluQuadricOrientation(obiekt, GLU_OUTSIDE);
	gluQuadricDrawStyle(obiekt, GLU_FILL);

	glPushMatrix();
	GLfloat  matSpecular[4] = { 1,1,1,1 };
	GLfloat  matAmbient[4] = { 0.2,0.2,0.2,1 };
	GLfloat  matDiffuse[4] = { .5,.5,.5,1 };
	GLfloat  matEmission[4] = { 0,0,0,1 };
	GLfloat  matShininess = 50;

	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
	glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
	glMateriali(GL_FRONT, GL_SHININESS, matShininess);

	double spacing = 2.0;

	glTranslatef(-mapWidth / 2 * spacing, 0, -50 - mapHeight / 2 * spacing);
	for (int j = 0; j<mapHeight; ++j) {
		for (int i = 0; i<mapWidth; ++i) {
			if (map[i][j] == 3) {
				gluSphere(obiekt, .3f, 50, 50);
			}
			else if (map[i][j] == 1) {
				glutSolidCube(spacing);
			}
			glTranslatef(spacing, 0, 0);
		}
		glTranslatef(-mapWidth* spacing, 0, spacing);
	}
	glPopMatrix();
}

