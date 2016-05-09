#include <windows.h>
#include "glut.h"
#include <time.h>
#include <math.h>
#include <direct.h>
#include <GL/glu.h>
#include "draw_scene.h"
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

	drawInit();

	glutMainLoop();
	return(0);
}

