#include "draw_scene.h"
#include "tekstura.h"
#include <math.h>

#define M_PI 3.14159265358979323846
int mapWidth = 20;
int mapHeight = 20;
MapPlanner planner(mapWidth, mapHeight);
int **map;
double spacing = 2.0;

int tex_id0;
int tex_id1;
int tex_id2;
int tex_id3;
int tex_id4;
int tex_id_side;



void setGreyMaterial() {
	glDisable(GL_BLEND);
	GLfloat  matSpecular[4] = { 0,0,0,1 };
	GLfloat  matAmbient[4] = { 0.5,0.5,0.5,1 };
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

	tex_id0 = WczytajTeksture("szablon0.bmp");
	tex_id1 = WczytajTeksture("szablon1.bmp");
	tex_id2 = WczytajTeksture("szablon2.bmp");
	tex_id3 = WczytajTeksture("szablon3.bmp");
	tex_id4 = WczytajTeksture("szablon4.bmp");
	tex_id_side = WczytajTeksture("szablonside.bmp");
}


void drawCluster(double x, double y, double z, int how, int rot) {
	double s = spacing / 2;
	double shift = -0.005;
	glMatrixMode(GL_TEXTURE);
	glScalef(1 / s, 1 / s, 1 / s);
	glRotatef(90, 1, 0, 0);
	glTranslatef(shift, 0, shift);
	glRotatef(rot, 0, 1, 0);


	switch (how) {
	case 0:
		glBindTexture(GL_TEXTURE_2D, tex_id0);
		break;
	case 1:
		glBindTexture(GL_TEXTURE_2D, tex_id1);
		break;
	case 2:
	case 3:
		glBindTexture(GL_TEXTURE_2D, tex_id2);
		break;
	case 4:
	case 5:
		glBindTexture(GL_TEXTURE_2D, tex_id3);
		break;
	default:
		glBindTexture(GL_TEXTURE_2D, tex_id4);
	}

	glBegin(GL_QUADS);
	glTexCoord3f(x, z, y);
	glVertex3f(x, z, y);

	glTexCoord3f(x, z, y + s);
	glVertex3f(x, z, y + s);

	glTexCoord3f(x + s, z, y + s);
	glVertex3f(x + s, z, y + s);

	glTexCoord3f(x + s, z, y);
	glVertex3f(x + s, z, y);
	glEnd();

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
}


void drawSide(double x, double y, double z, int rot) {
	double shift = -0.005;
	glMatrixMode(GL_TEXTURE);
	glScalef(1/ spacing, 1 / spacing, 1 / spacing);
	glRotatef(0, 1, 0, 0);
	glTranslatef(spacing / 2, spacing / 2, 0);
	glRotatef(270+rot, 0, 1, 0);

	double sr = spacing*sin(rot*M_PI/180);
	double cr = spacing *cos(rot*M_PI / 180);

	glBindTexture(GL_TEXTURE_2D, tex_id_side);

	glBegin(GL_QUADS);
	glTexCoord3f(x, z, y);
	glVertex3f(x, z, y);

	glTexCoord3f(x, z + spacing, y);
	glVertex3f(x, z + spacing, y);

	glTexCoord3f(x + sr, z + spacing, y+cr);
	glVertex3f(x + sr, z + spacing, y+cr);

	glTexCoord3f(x + sr, z, y+cr);
	glVertex3f(x + sr, z, y+cr);
	glEnd();

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

}

void drawRoof(int i, int j) {
	double s = spacing / 2;
	double x = (i - (mapWidth / 2))*spacing - s;
	double y = (j - (mapHeight / 2))*spacing - s;
	double z = s;
	int rot = 0;

	if (map[i][j] != 1) {
		z = -s;
		int how = 0;

		how = 0;
		rot = 0;
		if (map[i-1][j-1] == 1)
			how += 1;
		if (map[ i ][j-1] == 1)
			how += 2;
		if (map[i-1][ j ] == 1)
			how += 4;
		drawCluster(x, y, z, how, rot);

		how = 0;
		rot = 90;
		if (map[i+1][j-1] == 1)
			how += 1;
		if (map[ i ][j-1] == 1)
			how += 4;
		if (map[i+1][ j ] == 1)
			how += 2;
		drawCluster(x + spacing - s, y, z, how, rot);

		how = 0;
		rot = 270;
		if (map[i-1][j+1] == 1)
			how += 1;
		if (map[ i ][j+1] == 1)
			how += 4;
		if (map[i-1][ j ] == 1)
			how += 2;
		drawCluster(x, y + spacing - s, z, how, rot);

		how = 0;
		rot = 180;
		if (map[i+1][j+1] == 1)
			how += 1;
		if (map[ i ][j+1] == 1)
			how += 2;
		if (map[i+1][ j ] == 1)
			how += 4;
		drawCluster(x + spacing - s, y + spacing - s, z, how, rot);
	} else {
		drawCluster(x, y, z, 0, 0);
		drawCluster(x + spacing - s, y, z, 0, 0);
		drawCluster(x, y + spacing - s, z, 0, 0);
		drawCluster(x + spacing - s, y + spacing - s, z, 0, 0);
		if(j==0 || map[i][j-1]!=1)
			drawSide(x, y, -z,90);

		if (j == mapHeight -1 || map[i][j + 1] != 1)
			drawSide(x, y+spacing, -z,90);

		if (i == 0 || map[i - 1][j] != 1)
		drawSide(x, y, -z, 0);

		if (i == mapWidth -1 || map[i+1][j] != 1)
			drawSide(x + spacing, y, -z,0);
	}
}

// Function fired every frame
void drawScene() {
	GLUquadricObj *obiekt = gluNewQuadric();
	gluQuadricOrientation(obiekt, GLU_OUTSIDE);
	gluQuadricDrawStyle(obiekt, GLU_FILL);


	// Shift for all map
	glTranslatef(0, 0, -30);

	// Labirynth
	glPushMatrix();
	glTranslatef(-mapWidth / 2 * spacing, 0, - mapHeight / 2 * spacing);
	
	for (int j = 0; j<mapHeight; ++j) {
		for (int i = 0; i<mapWidth; ++i) {
			if (map[i][j] == 3) {
				setShinyMaterial();
				//gluSphere(obiekt, .3f, 50, 50);
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
			drawRoof(i, j);
		}
	}

}

