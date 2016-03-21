/*

 OpenGL - szablon do æwiczeñ laboratoryjnych
 (C) Micha³ Turek.

*/

#include <windows.h>
#include "glut.h"
#include "szablon.h"
#include <GL/glu.h>

//Wymiary okna
int screen_width=640;
int screen_height=480;

// obiekt GL
GLUquadricObj *obiekt;

void rozmiar (int width, int height)
{
    screen_width=width; 
    screen_height=height; 

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glViewport(0,0,screen_width,screen_height); 

	glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
	gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,1.0f,10000.0f);
    glutPostRedisplay (); // Przerysowanie sceny
}



/**********************************************************
 		G³ówna metoda rysuj¹ca
 *********************************************************/

void rysuj(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Kasowanie ekranu
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); 
	
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    	/*******************!SZABLON!**************************/
	// oswietlenie sceny - swiat³o globalne

	GLfloat  matSpecular1[4] = {0.5,1,1,1};
	GLfloat  matAmbient1[4] = {0.2,0.2,0.2,1};
	GLfloat  matDiffuse1[4] = {1,0,0,1};
	GLfloat  matEmission1[4] = {0,0,0,1};
	GLfloat  matShininess1 = 10;
	
	GLfloat  matSpecular2[4] = {1,0.3,1,1};
	GLfloat  matAmbient2[4] = {0.2,0.2,0.2,1};
	GLfloat  matDiffuse2[4] = {0.5,0.5,0.5,1};
	GLfloat  matEmission2[4] = {0,0,0,1};
	GLfloat  matShininess2 = 10;
		
	glMaterialfv(GL_FRONT, GL_SPECULAR,matSpecular1);
	glMaterialfv(GL_FRONT, GL_AMBIENT,matAmbient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,matDiffuse1);
	glMaterialfv(GL_FRONT, GL_EMISSION,matEmission1);
	glMateriali(GL_FRONT,GL_SHININESS,matShininess1);

	glTranslatef(-2.0,-1.5,-10); 
    gluSphere(obiekt,1,50,50); 
	glTranslatef(4.0,0.0,0); 
  	gluSphere(obiekt,1,50,50); 
	
	glMaterialfv(GL_FRONT, GL_SPECULAR,matSpecular2);
	glMaterialfv(GL_FRONT, GL_AMBIENT,matAmbient2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,matDiffuse2);
	glMaterialfv(GL_FRONT, GL_EMISSION,matEmission2);
	glMateriali(GL_FRONT,GL_SHININESS,matShininess2);

	glTranslatef(0.0,0,-5); 
  	gluSphere(obiekt,1,50,50); 
	glTranslatef(-4.0,0.0,0); 
  	gluSphere(obiekt,1,50,50); 
	

	/******************************************************/

    glFlush(); // rysowanie w buforze
    glutSwapBuffers(); // Wys³anie na ekran
}

int main(int argc, char **argv)
{
    // INIT - wszystkie funkcje obs³ugi okna i przetwzrzania zdarzeñ realizuje GLUT
	glutInit(&argc, argv);    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(screen_width,screen_height);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Szablon");    

	glutDisplayFunc(rysuj);			// def. funkcji rysuj¹cej
    //glutIdleFunc(rysuj);			// def. funkcji rysuj¹cej w czasie wolnym procesoora (w efekcie: ci¹gle wykonywanej)
    glutReshapeFunc (rozmiar);		// def. obs³ugi zdarzenia resize (GLUT)
	
	// ustawienie renderowania
   	glViewport(0,0,screen_width,screen_height); // Okno wype³niane
    glEnable(GL_DEPTH_TEST); 
    
	obiekt = gluNewQuadric();
	gluQuadricOrientation(obiekt, GLU_OUTSIDE);
	gluQuadricDrawStyle (obiekt, GLU_FILL);
	
 	/*******************!SZABLON!**************************/
	// oswietlenie sceny - swiat³o globalne

	GLfloat  ambient[4] = {0.5,0.5,0.5,1};
	
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient); // oœwietlenie globalne
	glEnable(GL_LIGHTING);

	GLfloat  ambientLight0[4] = {0.0,0.0,0.0,1};;
	GLfloat  diffuseLight0[4] = {1,1,1,1};;
	GLfloat  specular0[4] = {0.4,1.0,0.4,1};;
	GLfloat	 lightPos0[4] = {-20,20,30,1};;

	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight0);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight0);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specular0);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos0);
	glEnable(GL_LIGHT0);


	
	/******************************************************/
	
	glutMainLoop();					// start obs³ugi komunikatów
    return(0);    
}
