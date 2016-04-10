#include "map_planner.h"
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#define WIDTH 21
#define HEIGHT 9



#define HOLE_PERCENT 0.02f

void MapPlanner::setPoint(int x, int y) {
	if (x == posX && y == posY) return;
	map[x][y] = 3;
	map[width - x - 1][y] = 3;
	map[x][height - y - 1] = 3;
	map[width - x - 1][height - y - 1] = 3;
}

void MapPlanner::setPatch(int x1, int y1, int x2, int y2) {
	int i, j;
	for (j = 0; j<height / 2 + 1; ++j) {
		for (i = 0; i<width / 2 + 1; ++i) {
			if (i >= x1 && i <= x2 && j == y2) setPoint(i, j);
			if (j >= y1 && j <= y2 && i == x1) setPoint(i, j);

			if (i >= x2 && i <= x1 && j == y2) setPoint(i, j);
			if (j >= y2 && j <= y1 && i == x1) setPoint(i, j);
		}
	}
}

void MapPlanner::BFSrec(int posXbfs, int posYbfs, int **mapbfs) {
	mapbfs[posXbfs][posYbfs] = 2;

	if (mapbfs[posXbfs - 1][posYbfs] == 3)
		BFSrec(posXbfs - 1, posYbfs, mapbfs);
	if (mapbfs[posXbfs + 1][posYbfs] == 3)
		BFSrec(posXbfs + 1, posYbfs, mapbfs);
	if (mapbfs[posXbfs][posYbfs - 1] == 3)
		BFSrec(posXbfs, posYbfs - 1, mapbfs);
	if (mapbfs[posXbfs][posYbfs + 1] == 3)
		BFSrec(posXbfs, posYbfs + 1, mapbfs);
}

int MapPlanner::BFS() {
	int i, j, k, l;
	int **mapbfs;
	int posXN = 0;
	int posYN = 0;
	int posXS = -1;
	int posYS = -1;
	int hwidth = (width / 2);
	int hheight = (height / 2);

	mapbfs = new int*[width];
	for (int i = 0; i < width; ++i)
		mapbfs[i] = new int[height];

	for (j = 0; j<height; ++j) {
		for (i = 0; i<width; ++i) {
			mapbfs[i][j] = map[i][j];
		}
	}

	BFSrec(posX, posY, mapbfs);

	int type = pathType;
	if (type == 3)
		type = rand() % 2;

	if (type == 1) {
		//laczenie niespojnego z losowym
		//printf("random\n");
		for (j = 0; j<height; ++j) {
			for (i = 0; i<width; ++i) {
				if (mapbfs[i][j] == 3) {
					do {
						posXN = rand() % hwidth + 1;
						posYN = rand() % hheight + 1;
					} while (mapbfs[posXN][posYN] != 2);

					for (k = 0; k < width; ++k)
						delete[] mapbfs[k];
					delete[] mapbfs;

					setPatch(posXN, posYN, i, j);
					return 0;
				}
			}
		}
	}
	else {
		//laczenie niespojnego z najblizszym
		//printf("near\n");
		int dist = (height + width) * 2;
		for (j = 0; j<hheight + 1; ++j) {
			for (i = 0; i<hwidth + 1; ++i) {
				if (mapbfs[i][j] == 3) {
					for (k = 0; k<hheight + 1; ++k) {
						for (l = 0; l<hwidth + 1; ++l) {
							if (mapbfs[l][k] == 2) {
								int dist2 = (l - i>0 ? l - i : i - l) + (k - j>0 ? k - j : j - k);
								if (dist2 <= dist) {
									posXN = l;
									posYN = k;
									posXS = i;
									posYS = j;
									dist = dist2;
								}
							}
						}
					}
				}
			}
		}
	}


	for (i = 0; i < width; ++i)
		delete[] mapbfs[i];
	delete[] mapbfs;

	if (posXS >= 0) {
		setPatch(posXN, posYN, posXS, posYS);
		return 0;
	}

	return 1;
}

MapPlanner::MapPlanner() : pathType(3), width(WIDTH), height(HEIGHT) {
	generate();
}

MapPlanner::MapPlanner(int width, int height) : pathType(3) {
	this->width = width;
	this->height = height;

	if (width % 2 == 0)
		this->width = width + 1;
	if (height % 2 == 0)
		this->height = height + 1;

	generate();
}

MapPlanner::MapPlanner(int width, int height, int pathType) {
	this->width = width;
	this->height = height;

	if (width % 2 == 0)
		this->width = width + 1;
	if (height % 2 == 0)
		this->height = height + 1;

	this->pathType = pathType;

	generate();
}

MapPlanner::~MapPlanner() {
	for (int i = 0; i < width; ++i)
		delete[] map[i];
	delete[] map;
}

void MapPlanner::generate(void) {
	map = new int*[width];
	for (int i = 0; i < width; ++i)
		map[i] = new int[height];

	//printf("map constructed [%d][%d]\n", width, height);

	int i, j;
	for (j = 0; j<height; ++j) {
		for (i = 0; i<width; ++i) {
			map[i][j] = 1;
		}
	}
	posX = width / 2;
	posY = height / 2;

	setPoint(1, 1);
	srand(time(NULL));
	for (i = 0; i<(width*height)*HOLE_PERCENT; ++i) {
		setPoint(rand() % (width / 2) + 1, rand() % (height / 2) + 1);
	}

	while (!BFS()) {}

	map[posX][posY] = 2;
}

int **MapPlanner::getArray(void) {
	return map;
}

int MapPlanner::getWidth(void) {
	return width;
}

int MapPlanner::getHeight(void) {
	return height;
}

void MapPlanner::printSTD(void) {
	int i, j;
	for (j = 0; j<height; ++j) {
		for (i = 0; i<width; ++i) {
			if (map[i][j] == 3)
				printf(" ");
			else if (map[i][j] == 2)
				printf(" ");
			else if (map[i][j] == 1)
				printf("#");
			else
				printf("X");
		}
		printf("\n");
	}
}