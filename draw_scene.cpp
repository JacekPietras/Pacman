#include "draw_scene.h"
#include "tekstura.h"

int mapWidth = 20;
int mapHeight = 20;
MapPlanner planner(mapWidth, mapHeight);
int **map;
double spacing = 2.0;

int tex_id1;

void setGreyMaterial() {
	glDisable(GL_BLEND);
	GLfloat  matSpecular[4] = { 0,0,0,1 };
	GLfloat  matAmbient[4] = { 0.2,0.2,0.2,1 };
	GLfloat  matDiffuse[4] = { 1,1,1,1 };
	GLfloat  matEmission[4] = { 0,0,0,1 };
	GLfloat  matShininess = 10;

	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
	glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
	glMateriali(GL_FRONT, GL_SHININESS, matShininess);
}

void setPacmanMaterial() {
	glDisable(GL_BLEND);
	GLfloat  matSpecular[4] = { 1,1,1,1 };
	GLfloat  matAmbient[4] = { 0.2,0.2,0.2,1 };
	GLfloat  matDiffuse[4] = { .9,.9,.1,1 };
	GLfloat  matEmission[4] = { 0,0,0,1 };
	GLfloat  matShininess = 50;

	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
	glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
	glMateriali(GL_FRONT, GL_SHININESS, matShininess);
}

void setShinyMaterial() {
	GLfloat  matSpecular[4] = { 1,1,.3,1 };
	GLfloat  matAmbient[4] = { 1,1,0,1 };
	GLfloat  matDiffuse[4] = { .5,.5,.4,.3 };
	GLfloat  matEmission[4] = { 0,0,0,1 };
	GLfloat  matShininess = 30;

	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);  // w³¹czenie trybu koloryzacji materia³ów
	//glEnable(GL_COLOR_MATERIAL); // teraz zmiana koloru materia³u nastêpuje poprzez zwykly glColor*()


	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
	glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
	glMateriali(GL_FRONT, GL_SHININESS, matShininess);

	// pierwszy parametr:GL_ZERO, GL_ONE, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_SRC_ALPHA_SATURATE.
	// drugi parametr:GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA

	//glEnable(GL_BLEND);
	//glDepthMask(GL_FALSE);
	//glBlendFunc(GL_ONE, GL_ONE);
	//glDisable(GL_COLOR_MATERIAL);
}


// Function fired on start
void drawInit() {
	planner.printSTD();
	map = planner.getArray();
	mapWidth = planner.getWidth();
	mapHeight = planner.getHeight();
	tex_id1 = WczytajTeksture("szablon1.bmp");
}

void drawRoof(int x, int y, int z) {
	setGreyMaterial();
	glMatrixMode(GL_TEXTURE);
	glScalef(1 / spacing, 1 / spacing, 1 / spacing);
	glRotatef(90, 1, 0, 0);
	glTranslatef(spacing / 2, 0, spacing/2);

	glBindTexture(GL_TEXTURE_2D, tex_id1);

	glBegin(GL_QUADS);
	glTexCoord3f(x, z, y);
	glVertex3f(x, z, y);

	glTexCoord3f(x, z, y + spacing);
	glVertex3f(x, z, y + spacing);

	glTexCoord3f(x+spacing, z, y + spacing);
	glVertex3f(x+spacing, z, y+spacing);

	glTexCoord3f(x+spacing, z, y);
	glVertex3f(x+spacing, z, y);
	glEnd();

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
}

// Function fired every frame
void drawScene() {
	GLUquadricObj *obiekt = gluNewQuadric();
	gluQuadricOrientation(obiekt, GLU_OUTSIDE);
	gluQuadricDrawStyle(obiekt, GLU_FILL);


	// Shift for all map
	glTranslatef(0, 0, -50);





	// Labirynth
	glPushMatrix();
	glTranslatef(-mapWidth / 2 * spacing, 0, - mapHeight / 2 * spacing);
	
	for (int j = 0; j<mapHeight; ++j) {
		for (int i = 0; i<mapWidth; ++i) {
			if (map[i][j] == 3) {
				setShinyMaterial();
				gluSphere(obiekt, .3f, 50, 50);
			}
			else if (map[i][j] == 1) {
				setGreyMaterial();
				//glutSolidCube(spacing);
			}

			glTranslatef(0, -spacing, 0);
				setGreyMaterial();
				//glutSolidCube(spacing);

			glTranslatef(spacing, spacing, 0);
		}
		glTranslatef(-mapWidth* spacing, 0, spacing);
	}
	glPopMatrix();

	//Pacman
	glPushMatrix();
		setPacmanMaterial();
		gluSphere(obiekt, .8, 50, 50);
	glPopMatrix();



	setGreyMaterial();
	for (int j = 0; j<mapHeight; ++j) {
		for (int i = 0; i<mapWidth; ++i) {
			int x = (i - (mapWidth / 2))*spacing - spacing / 2;
			int y = (j - (mapHeight / 2))*spacing - spacing / 2;
			int z = map[i][j] == 1 ? spacing / 2 : -spacing / 2;
			drawRoof(x, y, z);
		}
	}
}

