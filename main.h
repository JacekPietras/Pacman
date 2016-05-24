#pragma once
//widh and height must be odd
#define mapWidth 21
#define mapHeight 21
#define spacing 2.0

extern int oknoSzerkosc;
extern int oknoWysokosc;

struct GameState {
	//Positions on map
	int pacmanPosX = mapWidth/2, pacmanPosZ = mapHeight/2, pacmanLastX, pacmanLastZ;
	float pacLerpX, pacLerpZ;

	int **map;
	int **map_tiles;
	int pacmanAngle;
	int points = 0;

	int ghostX[4], ghostY[4], ghostLastX[4], ghostLastY[4];
	float ghostLerpX[4], ghostLerpY[4];
	int ghostDirection[4];
	int ghostNum = 4;

	bool gameOver = false;
	bool won = false;
};
