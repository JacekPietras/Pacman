#include "ghosts.h"

using namespace std;

int *ghostX;
int *ghostY;
int *ghostDirection;
int ghostNum;
static int **map;

bool cUg(int i, int j) {
	int k;
	for (k = 0; k<ghostNum; ++k)
		if (ghostX[k] == i && ghostY[k] == j - 1) return true;

	if (j == 0 || map[i][j - 1] != 1) return false;
	return true;
}
bool cDg(int i, int j) {
	int k;
	for (k = 0; k<ghostNum; ++k)
		if (ghostX[k] == i && ghostY[k] == j + 1) return true;

	if (j == mapHeight - 1 || map[i][j + 1] != 1) return false;
	return true;
}
bool cLg(int i, int j) {
	int k;
	for (k = 0; k<ghostNum; ++k)
		if (ghostX[k] == i - 1 && ghostY[k] == j) return true;

	if (i == 0 || map[i - 1][j] != 1) return false;
	return true;
}
bool cRg(int i, int j) {
	int k;
	for (k = 0; k<ghostNum; ++k)
		if (ghostX[k] == i + 1 && ghostY[k] == j) return true;

	if (i == mapWidth - 1 || map[i + 1][j] != 1) return false;
	return true;
}

bool checkGhostDirection(int i){
	if(ghostDirection[i] == 1 && cLg(ghostX[i], ghostY[i])) return false;  
	if(ghostDirection[i] == 2 && cRg(ghostX[i], ghostY[i])) return false;
	if(ghostDirection[i] == 3 && cUg(ghostX[i], ghostY[i])) return false;
	if(ghostDirection[i] == 4 && cDg(ghostX[i], ghostY[i])) return false;
	return true;
}
void checkWinOrLost(GameState &gs){
	int i;
	for(i=0 ; i<ghostNum ; ++i){
		if(gs.pacmanPosZ == ghostY[i] && gs.pacmanPosX == ghostX[i]){
			gs.gameOver = true;
		}
	}
	/*if(points == allPoints){
		clearScreen();
		mvprintw(screenH/2-1,screenW/2-4,"YOU WIN");
		refresh();
		sleep(2);
		ghostNum++;
		if(ghostNum > 4) ghostNum = 4;
		generateMap();
		return;
	}*/
}
void makeGhosts() {
	for (int i = 1; i <= ghostNum; i++)
	{
		switch (i)
		{
		case 1:
			ghostX[0] = 1;
			ghostY[0] = 1;
			ghostDirection[0] = 1;
			break;
		case 2:
			ghostX[1] = mapWidth - 2;
			ghostY[1] = mapHeight - 2;
			ghostDirection[1] = 1;
			break;
		case 3:
			ghostX[2] = 1;
			ghostY[2] = mapHeight - 2;
			ghostDirection[2] = 1;
			break;
		case 4:
			ghostX[3] = mapWidth - 2;
			ghostY[3] = 1;
			ghostDirection[3] = 1;
		}
	}
}
void makeGhosts(GameState& gs) {
	ghostX = gs.ghostX;
	ghostY = gs.ghostY;
	ghostDirection = gs.ghostDirection;
	ghostNum = gs.ghostNum;
	map=gs.map;
	srand(time(NULL));
	makeGhosts();
}

void moveGhosts(GameState& gs){
	int i, ghowstWait = 0;
	
	for(i=0 ; i<ghostNum ; ++i){
		ghowstWait = 0; // zeby sie duchy nie zakleszczyly
		
		do{
			gs.ghostDirection[i] = rand()%4 + 1;
			if(ghowstWait++ > 10) break;
		}while(!checkGhostDirection(i));
		
		if(ghowstWait<10){
			gs.ghostLastX[i] = ghostX[i];
			gs.ghostLastY[i] = ghostY[i];
			switch(ghostDirection[i]){
				case 1: gs.ghostX[i]-=1; break;
				case 2: gs.ghostX[i]+=1; break;
				case 3: gs.ghostY[i]-=1; break;
				case 4: gs.ghostY[i]+=1; break;
				default: return;
			}
		}
	}
}

