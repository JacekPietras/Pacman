#include "draw_scene.h"

#define M_PI 3.14159265358979323846
#define BLACK 0
#define BLUE 1
int **map;
int **map_tiles;



// Function fired on start


void drawShadow(double x, double y, int color) {
	double s = spacing;
	double z = -spacing / 2+0.05;

	x *= spacing;
	y *= spacing;

	x -= spacing / 2;
	y -= spacing / 2;

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glScalef(1 / spacing, 1 / spacing, 1 / spacing);
	glRotatef(90, 1, 0, 0);
	glTranslatef(-x, 0, -y);

	if(color == BLUE)
		glBindTexture(GL_TEXTURE_2D, shadow_ball_id);
	else
		glBindTexture(GL_TEXTURE_2D, shadow_id);

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

	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
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


void draw(void(*shape)(float, float), float x, float z) {
	glPushMatrix();
		shape(x,z);
	glPopMatrix();
}
void draw(void(*shape)(float, float, GameState &gs), float x, float z, GameState &gs) {
	glPushMatrix();
		shape(x, z, gs);
	glPopMatrix();
}
void draw(void(*shape)(float, float, char * str), float x, float z, char * str) {
	glPushMatrix();
		shape(x, z, str);
	glPopMatrix();
}
template <typename T>
void draw(void(*shape)(T arg), T arg) {
	glPushMatrix();
		shape(arg);
	glPopMatrix();
}

// Function fired every frame
void drawScene(GameState &gs) {
	if (!gs.gameOver) {
		map = gs.map;
		map_tiles = gs.map_tiles;

		glPushMatrix();
		setGreyMaterial();
		for (int j = 0; j < mapHeight; ++j) {
			for (int i = 0; i < mapWidth; ++i) {
				drawWall(i, j);
			}
		}
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

		for (int j = 0; j < mapHeight; ++j) {
			for (int i = 0; i < mapWidth; ++i) {
				if (map[i][j] == 3) {
					setShinyMaterial();
					drawShadow((i - mapWidth / 2), (j - mapHeight / 2), BLUE);
				}
			}
		}

		glPushMatrix();
		// Align world with map
			glTranslatef((-mapWidth / 2) * spacing, 0, (-mapHeight / 2) * spacing);

			for (int i = 0; i < gs.ghostNum; ++i) {
				draw(ghost, gs.ghostLerpX[i], gs.ghostLerpY[i]);
			}

			draw(pacman, gs.pacLerpX, gs.pacLerpZ, gs);

			setShadowMaterial();
			drawShadow(gs.pacLerpX, gs.pacLerpZ, BLACK);

			draw(points, gs.map);

		glPopMatrix();

		draw(hud, oknoSzerkosc - 300, 10, gs);
	}
	else {
		draw(text, oknoSzerkosc / 2, oknoWysokosc / 2, "GAME OVER");
		draw(hud, oknoSzerkosc - 300, 10, gs);
	}
}


