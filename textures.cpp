#include "textures.h"
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
int shadow_id;
int shadow_ball_id;

void loadTextures() {
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

	energy_id = WczytajTekstureAlpha("energy.bmp");
	shadow_id = WczytajTekstureAlpha("shadow.bmp");
	shadow_ball_id = WczytajTekstureAlpha("shadow_ball.bmp");
}