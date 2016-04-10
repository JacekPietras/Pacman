#include "draw_scene.h"


int mapWidth = 20;
int mapHeight = 20;

void drawScene(GLUquadricObj *obiekt) {
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
	for (int i = 0; i < mapWidth; i++) {
		for (int j = 0; j < mapHeight; j++) {
			gluSphere(obiekt, 1, 50, 50);
			glTranslatef(spacing, 0, 0);
		}
		glTranslatef(-mapWidth* spacing, 0, spacing);
	}
	glPopMatrix();
}

