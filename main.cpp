#include <windows.h>
#include "glut.h"
#include <time.h>
#include <math.h>
#include <direct.h>
#include <GL/glu.h>
#include "draw_scene.h"
#include "model3DS.h"
#define _INTERAKCJA
#include "interakcja.cpp"

// Wymiary okna
int oknoSzerkosc=1024;
int oknoWysokosc=768;
bool fog = true;

GLfloat pacmanPosX = 0.0f, pacmanPosZ = 0.0f;


void setCamera() {
	kameraX = 0;
	kameraY = 15;
	kameraZ = 0;
	kameraKat = 0;
	kameraPunktY = -15;
	kameraPredkoscPunktY = 0;
	kameraPredkosc = 0;
	kameraPredkoscObrotu = 0;
	kameraPrzemieszczanie = true;
}

void windowInit() {
	glShadeModel(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);
	//glEnable(GL_CULL_FACE); 
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_LIGHTING);
	//glEnable(GL_POLYGON_SMOOTH);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	
	
	//GLfloat  ambient[4] = { 0.3,0.3,0.3,1 };
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

	//GLfloat  diffuse[4] = { 0.9,0.9,0.9,1 };
	//GLfloat  specular[4] = { 0.9,0.9,0.9,1 };
	//GLfloat	 position[4] = { 30,30,30,1 };


	GLfloat  ambient[4] = { 0.5,0.5,0.5,0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

	GLfloat  diffuse[4] = { 0.5,0.5,0.5,0 };
	GLfloat  specular[4] = { 0.5,0.5,0.5,0 };
	GLfloat	 position[4] = { 30,30,30,1 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);  // œwiatlo sceny

	if (fog) {
		float fogColor[4] = { 0, 0, 0, 1 };
		glFogi(GL_FOG_MODE, GL_EXP2); // [GL_EXP, GL_EXP2, GL_LINEAR ]
		glFogfv(GL_FOG_COLOR, fogColor);
		glFogf(GL_FOG_DENSITY, 0.010f);
		glFogf(GL_FOG_START, 0.0f);
		glFogf(GL_FOG_END, 200.0f);
		glEnable(GL_FOG);
	}
}



struct model_w_skladzie {
	char * filename;
	model3DS * model;
	struct model_w_skladzie *wsk;
};
struct model_w_skladzie* sklad_modeli = NULL;

void dodajModel(model3DS * _model, char* file_name)
{
	struct model_w_skladzie* tmp;
	tmp = (struct model_w_skladzie *) malloc(sizeof(struct model_w_skladzie));
	tmp->filename = (char *)malloc(strlen(file_name) + 1);
	strcpy(tmp->filename, file_name);
	tmp->model = _model;
	tmp->wsk = sklad_modeli;
	sklad_modeli = tmp;
}

model3DS * pobierzModel(char* file_name)
{
	struct model_w_skladzie* sklad_tmp = sklad_modeli;
	while (sklad_tmp) {
		if (!_stricmp(sklad_tmp->filename, file_name)) return sklad_tmp->model;
		char file_name_full[_MAX_PATH];
		strcpy(file_name_full, file_name);
		strcat(file_name_full, ".3ds");
		if (!_stricmp(sklad_tmp->filename, file_name_full)) return sklad_tmp->model;

		sklad_tmp = sklad_tmp->wsk;
	}
	return NULL;
}

void ladujModele()
{
	WIN32_FIND_DATA *fd;
	HANDLE fh;
	model3DS * model_tmp;
	char directory[_MAX_PATH];
	if (_getcwd(directory, _MAX_PATH) == NULL) return;
	strcat(directory, "\\data\\*.3ds");

	fd = (WIN32_FIND_DATA *)malloc(sizeof(WIN32_FIND_DATA));
	fh = FindFirstFile((LPCSTR)directory, fd);
	if (fh != INVALID_HANDLE_VALUE)
		do {
			if (fd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {	// katalogi ignorujemy
				if (FindNextFile(fh, fd)) continue; else break;
			}
			// ladowanie obiektu i dodanie do kontenera
			char filename[_MAX_PATH];
			strcpy(filename, "data\\");
			strcat(filename, fd->cFileName);
			model_tmp = new model3DS(filename, 1, false);
			dodajModel(model_tmp, fd->cFileName);
			printf("[3DS] Model '%s' stored\n", fd->cFileName);
		} while (FindNextFile(fh, fd));
}

void rysujModel(char * file_name, int tex_num = -1)
{
	model3DS * model_tmp;
	if (model_tmp = pobierzModel(file_name))
		if (tex_num == -1)
			model_tmp->draw();
		else
			model_tmp->draw(tex_num, false);

}

void resizeWindow (int width, int height){
	if (width==0) width++;
	if (width==0) width++;
	oknoSzerkosc=width;
	oknoWysokosc=height; 
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glViewport(0,0,oknoSzerkosc,oknoWysokosc+24); 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    gluPerspective(45.0f,(GLfloat)oknoSzerkosc/(GLfloat)oknoWysokosc,1.0f,1000.0f);
    glMatrixMode(GL_MODELVIEW);
}

void drawFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Kasowanie ekranu
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(kameraX, kameraY, kameraZ, kameraX + 100 * sin(kameraKat), 3 + kameraPunktY, kameraZ - 100 * cos(kameraKat), 0, 1, 0); // kamera
	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
	glPushMatrix();

	handleMovement(pacmanPosX, pacmanPosZ);
	drawScene(pacmanPosX, pacmanPosZ);
	glMatrixMode(GL_MODELVIEW);

	glPopMatrix();
	glFlush();
	glPopMatrix();
	glutSwapBuffers(); 
}

void timer(){
	kameraKat = kameraKat + kameraPredkoscObrotu;
	kameraPunktY = kameraPunktY + kameraPredkoscPunktY;
	kameraX = kameraX + kameraPredkosc*sin(kameraKat);
	kameraZ = kameraZ - kameraPredkosc*cos(kameraKat);
	drawFrame();		
}

void syncTimer (int ID){
	timer();
	glutTimerFunc(1,syncTimer,10);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(oknoSzerkosc, oknoWysokosc);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Pacman");
	windowInit();
	glutReshapeFunc(resizeWindow);					// def. obs³ugi zdarzenia resize (GLUT)
	glutKeyboardFunc(onKeyDown);					// def. obs³ugi klawiatury
	glutKeyboardUpFunc(onKeyUp);
	glutSpecialFunc(KlawiszSpecjalnyWcisniety);		// def. obs³ugi klawiatury (klawisze specjalne)
	glutMouseFunc(PrzyciskMyszyWcisniety); 			// def. obs³ugi zdarzenia przycisku myszy (GLUT)
	glutMotionFunc(RuchKursoraMyszy);				// def. obs³ugi zdarzenia ruchu myszy (GLUT)
	glutDisplayFunc(drawFrame);						// def. funkcji rysuj¹cej
	glutTimerFunc(10, syncTimer, 10);
	setCamera();

	ladujModele();
	drawInit();
	glutMainLoop();
	return(0);
}

