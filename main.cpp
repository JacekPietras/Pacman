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

void windowInit()
{
	glClearColor(0, 0, 0, 0);			
    glShadeModel(GL_SMOOTH);					
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST); 
	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); 
	glEnable(GL_LIGHTING);
	GLfloat  ambient[4] = {0.3,0.3,0.3,1};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient); 

	GLfloat  diffuse[4] = {0.9,0.9,0.9,1};
	GLfloat  specular[4] = {0.9,0.9,0.9,1};
	GLfloat	 position[4] = {30,30,-30,1};
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
	glLightfv(GL_LIGHT0,GL_POSITION,position);
	glEnable(GL_LIGHT0);  // œwiatlo sceny

	/*******************MGLA**************************/

	float fogColor[4]= {0, 0, 0, 0.1f};
	glFogi(GL_FOG_MODE,GL_EXP2); // [GL_EXP, GL_EXP2, GL_LINEAR ]
	glFogfv(GL_FOG_COLOR, fogColor); 
	glFogf(GL_FOG_DENSITY, 0.010f); 
	glFogf(GL_FOG_START, 0.0f); 
	glFogf(GL_FOG_END, 200.0f); 
	glEnable(GL_FOG);  


}

void rozmiar (int width, int height)
{
	if (width==0) width++;
	if (width==0) width++;
	oknoSzerkosc=width;   // przy stereo nie mo¿na zmieniaæ rozmiaru
	oknoWysokosc=height; 
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glViewport(0,0,oknoSzerkosc,oknoWysokosc+24); 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    gluPerspective(45.0f,(GLfloat)oknoSzerkosc/(GLfloat)oknoWysokosc,1.0f,1000.0f);
    glMatrixMode(GL_MODELVIEW);
}

void rysuj()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Kasowanie ekranu
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0, 0, -20);
	glPopMatrix();
	gluLookAt(kameraX, kameraY, kameraZ, kameraX + 100 * sin(kameraKat), 3 + kameraPunktY, kameraZ - 100 * cos(kameraKat), 0, 1, 0); // kamera

	drawScene();

	glFlush();
	glPopMatrix();
	glutSwapBuffers(); 
}

void timer(){
	kameraKat = kameraKat + kameraPredkoscObrotu;
	kameraPunktY = kameraPunktY + kameraPredkoscPunktY;
	kameraX = kameraX + kameraPredkosc*sin(kameraKat);
	kameraZ = kameraZ - kameraPredkosc*cos(kameraKat);
	rysuj();		
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
	glutReshapeFunc(rozmiar);						// def. obs³ugi zdarzenia resize (GLUT)
	glutKeyboardFunc(KlawiszKlawiaturyWcisniety);	// def. obs³ugi klawiatury
	glutSpecialFunc(KlawiszSpecjalnyWcisniety);		// def. obs³ugi klawiatury (klawisze specjalne)
	glutMouseFunc(PrzyciskMyszyWcisniety); 			// def. obs³ugi zdarzenia przycisku myszy (GLUT)
	glutMotionFunc(RuchKursoraMyszy);				// def. obs³ugi zdarzenia ruchu myszy (GLUT)
	glutDisplayFunc(rysuj);							// def. funkcji rysuj¹cej



	glutTimerFunc(10, syncTimer, 10);
	resetKamery();
	//srand( (unsigned)time( NULL ) ); // generator liczb losowych
	glutMainLoop();
	return(0);
}

