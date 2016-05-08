#ifndef MAP_PLANNER_H
#define MAP_PLANNER_H

// Map
// 1 # - sciana
// 2   - puste
// 3 0 - punkt

// Path type:
// 1 - random
// 2 - near
// 3 - mixed

class MapPlanner {
public:
	MapPlanner();
	MapPlanner(int width, int height);
	MapPlanner(int width, int height, int pathType);
	~MapPlanner();
	int **getArray(void);
	int **getTilesArray(void);
	int getWidth(void);
	int getHeight(void);
	void printSTD(void);

private:
	int width;
	int height;
	int **map;
	int **map_tiles;
	int posX;
	int posY;
	int pathType;

	void generate(void);
	void setPoint(int x, int y);
	void setPatch(int x1, int y1, int x2, int y2);
	void BFSrec(int posXbfs, int posYbfs, int **mapbfs);
	int BFS();
};

#endif