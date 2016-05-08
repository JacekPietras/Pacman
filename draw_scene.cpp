#include "draw_scene.h"
#include "tekstura.h"
#include <math.h>

#define M_PI 3.14159265358979323846
int mapWidth = 20;
int mapHeight = 20;
MapPlanner planner(mapWidth, mapHeight);
int **map;
int **map_tiles;
double spacing = 2.0;

int roof_id0;
int roof_id1;
int roof_id2;
int roof_id3;
int roof_id4;
int floor_id0_1;
int floor_id0_2;
int floor_id0_3;
int floor_id1_1;
int floor_id1_2;
int floor_id1_3;
int floor_id2_1;
int floor_id2_2;
int floor_id2_3;
int floor_id3_1;
int floor_id3_2;
int floor_id3_3;
int floor_id4_1;
int floor_id4_2;
int floor_id4_3;

int side_1_id;
int side_2_id;
int side_3_id;

int energy_id;
int pacman_id;



void setGreyMaterial() {
	glDisable(GL_BLEND);
	GLfloat  matSpecular[4] = { 0,0,0,1 };
	GLfloat  matAmbient[4] = { 0.5,0.5,0.5,1 };
	GLfloat  matDiffuse[4] = { 1,1,1,1 };
	GLfloat  matEmission[4] = { 0,0,0,1 };
	GLfloat  matShininess = 10;

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matEmission);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, matShininess);
}

void setPacmanMaterial() {
	glDisable(GL_BLEND);
	GLfloat  matSpecular[4] = { 1,1,1,1 };
	GLfloat  matAmbient[4] = { 0.2,0.2,0.2,1 };
	GLfloat  matDiffuse[4] = { .9,.9,.9,1 };
	GLfloat  matEmission[4] = { 0,0,0,1 };
	GLfloat  matShininess = 50;

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matEmission);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, matShininess);
}

void setShinyMaterial() {
	GLfloat  matSpecular[4] = { 1,1,1,1 };
	GLfloat  matAmbient[4] = { 1,1,1,1 };
	GLfloat  matDiffuse[4] = { 1,1,1,1 };
	GLfloat  matEmission[4] = { 1,1,1,1 };
	GLfloat  matShininess = 50;

	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);  // w³¹czenie trybu koloryzacji materia³ów
	//glEnable(GL_COLOR_MATERIAL); // teraz zmiana koloru materia³u nastêpuje poprzez zwykly glColor*()


	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matEmission);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, matShininess);

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
	map_tiles = planner.getTilesArray();
	mapWidth = planner.getWidth();
	mapHeight = planner.getHeight();

	floor_id0_1 = WczytajTeksture("floor0.bmp");
	floor_id0_2 = WczytajTeksture("floor0_2.bmp");
	floor_id0_3 = WczytajTeksture("floor0_3.bmp");
	floor_id1_1 = WczytajTeksture("floor1.bmp");
	floor_id1_2 = WczytajTeksture("floor1_2.bmp");
	floor_id1_3 = WczytajTeksture("floor1_3.bmp");
	floor_id2_1 = WczytajTeksture("floor2.bmp");
	floor_id2_2 = WczytajTeksture("floor2_2.bmp");
	floor_id2_3 = WczytajTeksture("floor2_3.bmp");
	floor_id3_1 = WczytajTeksture("floor3.bmp");
	floor_id3_2 = WczytajTeksture("floor3_2.bmp");
	floor_id3_3 = WczytajTeksture("floor3_3.bmp");
	floor_id4_1 = WczytajTeksture("floor4.bmp");
	floor_id4_2 = WczytajTeksture("floor4_2.bmp");
	floor_id4_3 = WczytajTeksture("floor4_3.bmp");

	roof_id0 = WczytajTeksture("roof0.bmp");
	roof_id1 = WczytajTeksture("roof1.bmp");
	roof_id2 = WczytajTeksture("roof2.bmp");
	roof_id3 = WczytajTeksture("roof3.bmp");
	roof_id4 = WczytajTeksture("roof4.bmp");

	side_1_id = WczytajTeksture("side_1.bmp");
	side_2_id = WczytajTeksture("side_2.bmp");
	side_3_id = WczytajTeksture("side_3.bmp");

	energy_id = WczytajTeksture("energy.bmp");
	pacman_id = WczytajTeksture("pacman.bmp");
}


void drawCluster(double x, double y, double z, int how, int rot, int textureType) {
	double s = spacing / 2;
	double shift = -0.005;
	if (z > 0) 
		s = spacing;
	
	glMatrixMode(GL_TEXTURE);
	glScalef(1 / s, 1 / s, 1 / s);
	glRotatef(90, 1, 0, 0);
	if(z>0)
		glTranslatef(spacing / 2, spacing / 2, spacing / 2);
	glTranslatef(shift, 0, shift);
	glRotatef(rot, 0, 1, 0);

	if (z < 0) {
	switch (how) {
	case 0:
		if (textureType == 1)
			glBindTexture(GL_TEXTURE_2D, floor_id0_1);
		else if (textureType == 1)
			glBindTexture(GL_TEXTURE_2D, floor_id0_2);
		else
			glBindTexture(GL_TEXTURE_2D, floor_id0_3);

		break;
	case 1:
		if (textureType == 1)
			glBindTexture(GL_TEXTURE_2D, floor_id1_1);
		else if (textureType == 1)
			glBindTexture(GL_TEXTURE_2D, floor_id1_2);
		else
			glBindTexture(GL_TEXTURE_2D, floor_id1_3);
		break;
	case 2:
	case 3:
		if (textureType == 1)
			glBindTexture(GL_TEXTURE_2D, floor_id2_1);
		else if (textureType == 1)
			glBindTexture(GL_TEXTURE_2D, floor_id2_2);
		else
			glBindTexture(GL_TEXTURE_2D, floor_id2_3);
		break;
	case 4:
	case 5:
		if (textureType == 1)
			glBindTexture(GL_TEXTURE_2D, floor_id3_1);
		else if (textureType == 1)
			glBindTexture(GL_TEXTURE_2D, floor_id3_2);
		else
			glBindTexture(GL_TEXTURE_2D, floor_id3_3);
		break;
	default:
		if (textureType == 1)
			glBindTexture(GL_TEXTURE_2D, floor_id4_1);
		else if (textureType == 1)
			glBindTexture(GL_TEXTURE_2D, floor_id4_2);
		else
			glBindTexture(GL_TEXTURE_2D, floor_id4_3);
	}
}
	else {
		switch (textureType) {
		case 1:
			glBindTexture(GL_TEXTURE_2D, roof_id0);
			break;
		case 2:
			glBindTexture(GL_TEXTURE_2D, roof_id1);
			break;
		case 3:
			glBindTexture(GL_TEXTURE_2D, roof_id2);
			break;
		case 4:
			glBindTexture(GL_TEXTURE_2D, roof_id3);
			break;
		default:
			glBindTexture(GL_TEXTURE_2D, roof_id4);
		}
	}

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord3f(x, z, y);
	glVertex3f(x, z, y);

	glTexCoord3f(x + s, z, y);
	glVertex3f(x + s, z, y);

	glTexCoord3f(x + s, z, y + s);
	glVertex3f(x + s, z, y + s);

	glTexCoord3f(x, z, y + s);
	glVertex3f(x, z, y + s);
	glEnd();

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
}

void drawSide(double x, double y, double z, int rot, int textureType) {
	double shift = -0.005;
	glMatrixMode(GL_TEXTURE);
	glScalef(1/ spacing, 1 / spacing, 1 / spacing);
	glRotatef(0, 1, 0, 0);
	glTranslatef(spacing / 2, spacing / 2, 0);
	glRotatef(270+rot, 0, 1, 0);

	double sr = sin(rot*M_PI/180);
	double cr = cos(rot*M_PI / 180);

	if(textureType==5)
		glBindTexture(GL_TEXTURE_2D, side_3_id);
	else if (textureType == 2)
		glBindTexture(GL_TEXTURE_2D, side_1_id);
	else if (textureType == 3)
		glBindTexture(GL_TEXTURE_2D, side_2_id);
	else if (textureType == 4)
		glBindTexture(GL_TEXTURE_2D, side_2_id);
	else
		glBindTexture(GL_TEXTURE_2D, side_1_id);

	glBegin(GL_QUADS);
	glNormal3f(sr, 0.0f, cr);
	
	sr *= spacing;
	cr *= spacing;

	glTexCoord3f(x, z, y);
	glVertex3f(x, z, y);

	glTexCoord3f(x + sr, z, y+cr);
	glVertex3f(x + sr, z, y+cr);

	glTexCoord3f(x + sr, z + spacing, y+cr);
	glVertex3f(x + sr, z + spacing, y+cr);

	glTexCoord3f(x, z + spacing, y);
	glVertex3f(x, z + spacing, y);
	glEnd();

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
}

void drawWall(int i, int j) {
	double s = spacing / 2;
	double x = (i - (mapWidth / 2))*spacing - s;
	double y = (j - (mapHeight / 2))*spacing - s;
	double z = s;
	int rot = 0;
	int how = 0;

	if (map[i][j] != 1) { // floor
		z = -s;

		how = 0;
		rot = 0;
		if (map[i-1][j-1] == 1)
			how += 1;
		if (map[ i ][j-1] == 1)
			how += 2;
		if (map[i-1][ j ] == 1)
			how += 4;
		drawCluster(x, y, z, how, rot, map_tiles[i][j]);
		
		how = 0;
		rot = 90;
		if (map[i+1][j-1] == 1)
			how += 1;
		if (map[ i ][j-1] == 1)
			how += 4;
		if (map[i+1][ j ] == 1)
			how += 2;
		drawCluster(x + spacing - s, y, z, how, rot, map_tiles[i][j]);

		how = 0;
		rot = 270;
		if (map[i-1][j+1] == 1)
			how += 1;
		if (map[ i ][j+1] == 1)
			how += 4;
		if (map[i-1][ j ] == 1)
			how += 2;
		drawCluster(x, y + spacing - s, z, how, rot, map_tiles[i][j]);

		how = 0;
		rot = 180;
		if (map[i+1][j+1] == 1)
			how += 1;
		if (map[ i ][j+1] == 1)
			how += 2;
		if (map[i+1][ j ] == 1)
			how += 4;
		drawCluster(x + spacing - s, y + spacing - s, z, how, rot, map_tiles[i][j]);
	} else {
		//roof
		how = 0;
		rot = 0;
		if (i==0 || j==0 || map[i - 1][j - 1] != 1)
			how += 1;
		if (j==0 || map[i][j - 1] != 1)
			how += 2;
		if (i==0||map[i - 1][j] != 1)
			how += 4;
		drawCluster(x, y, z, how, rot, map_tiles[i][j]);
		/*
		how = 0;
		rot = 90;
		if (i == mapWidth - 1 || j == 0 || map[i + 1][j - 1] != 1)
			how += 1;
		if (j == 0 || map[i][j - 1] != 1)
			how += 4;
		if (i == mapWidth - 1 || map[i + 1][j] != 1)
			how += 2;
		drawCluster(x + spacing - s, y, z, how, rot, map_tiles[i][j]);

		how = 0;
		rot = 270;
		if (j == mapHeight -1 ||i==0 ||map[i - 1][j + 1] != 1)
			how += 1;
		if (j == mapHeight -1 ||map[i][j + 1] != 1)
			how += 4;
		if (i==0 ||map[i - 1][j] != 1)
			how += 2;
		drawCluster(x, y + spacing - s, z, how, rot, map_tiles[i][j]);

		how = 0;
		rot = 180;
		if (j == mapHeight -1 ||i == mapWidth -1 ||map[i + 1][j + 1] != 1)
			how += 1;
		if (j == mapHeight -1 ||map[i][j + 1] != 1)
			how += 2;
		if (i == mapWidth -1 ||map[i + 1][j] != 1)
			how += 4;
		drawCluster(x + spacing - s, y + spacing - s, z, how, rot, map_tiles[i][j]);
		*/

		// sides

		if(j==0 || map[i][j-1]!=1)
			drawSide(x, y, -z,90, map_tiles[i][j]);
		
		if (j == mapHeight -1 || map[i][j + 1] != 1)
			drawSide(x, y+spacing, -z,90, map_tiles[i][j]);

		if (i == 0 || map[i - 1][j] != 1)
			drawSide(x, y, -z, 0, map_tiles[i][j]);

		if (i == mapWidth -1 || map[i+1][j] != 1)
			drawSide(x + spacing, y, -z,0, map_tiles[i][j]);
	}
}

// Function fired every frame
void drawScene(GLfloat pacmanPosX, GLfloat pacmanPosZ) {
	GLUquadricObj *obiekt = gluNewQuadric();
	gluQuadricOrientation(obiekt, GLU_OUTSIDE);
	gluQuadricDrawStyle(obiekt, GLU_FILL);


	// Shift for all map
	glTranslatef(0, 0, -30);


	/*
	glPushMatrix();


	GLint list[50];
	setShinyMaterial();

	glNewList(list[0], GL_COMPILE);

	gluQuadricDrawStyle(obiekt, GLU_FILL);
	gluQuadricNormals(obiekt, GLU_SMOOTH);
	gluQuadricOrientation(obiekt, GLU_OUTSIDE);
	gluQuadricTexture(obiekt, GL_TRUE);

	glMatrixMode(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, energy_id);


	glEndList();


	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();



	glPopMatrix();
	*/


	// Labirynth
	glPushMatrix();
	glTranslatef(-mapWidth / 2 * spacing, 0, - mapHeight / 2 * spacing);
	
	for (int j = 0; j<mapHeight; ++j) {
		for (int i = 0; i<mapWidth; ++i) {
			if (map[i][j] == 3) {
				glPushMatrix();
				setShinyMaterial();

				glMatrixMode(GL_TEXTURE);
				glMatrixMode(GL_MODELVIEW);
				glBindTexture(GL_TEXTURE_2D, energy_id);
				gluQuadricDrawStyle(obiekt, GLU_FILL);
				gluQuadricNormals(obiekt, GLU_SMOOTH);
				gluQuadricOrientation(obiekt, GLU_OUTSIDE);
				gluQuadricTexture(obiekt, GL_TRUE);

				gluSphere(obiekt, .3f, 50, 50);
				glPopMatrix();
			}

			glTranslatef(spacing, 0, 0);
		}
		glTranslatef(-mapWidth* spacing, 0, spacing);
	}
	glPopMatrix();

	//Pacman
	glPushMatrix();
		glTranslatef(pacmanPosX, 0, pacmanPosZ);

		glPushMatrix();
		setPacmanMaterial();

		glMatrixMode(GL_TEXTURE);
		glMatrixMode(GL_MODELVIEW);
		glBindTexture(GL_TEXTURE_2D, pacman_id);
		gluQuadricDrawStyle(obiekt, GLU_FILL);
		gluQuadricNormals(obiekt, GLU_SMOOTH);
		gluQuadricOrientation(obiekt, GLU_OUTSIDE);
		gluQuadricTexture(obiekt, GL_TRUE);

		gluSphere(obiekt, .8, 50, 50);
		glPopMatrix();

	glPopMatrix();

	setGreyMaterial();
	for (int j = 0; j<mapHeight; ++j) {
		for (int i = 0; i<mapWidth; ++i) {
			drawWall(i, j);
		}
	}
}

