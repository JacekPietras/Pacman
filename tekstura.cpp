/*
* Wczytywanie tekstury
*/

#include <stdio.h>
#include <windows.h>
#include "glut.h"
#include "tekstura.h"

int num_texture=100; 

int WczytajTeksture (char *filename) 
{
    // Pomocnicze
	int i, j=0;
    FILE *l_file;
    unsigned char *l_texture; 
    BITMAPFILEHEADER fileheader; 
    BITMAPINFOHEADER infoheader;
    RGBTRIPLE rgb;
    num_texture++;

    if( (l_file = fopen(filename, "rb"))==NULL) return (-1); 
    // Nag��wek:
	fread(&fileheader, sizeof(fileheader), 1, l_file); 
    fseek(l_file, sizeof(fileheader), SEEK_SET); 
    fread(&infoheader, sizeof(infoheader), 1, l_file); 
	// Alokacja pami�ci
    l_texture = (byte *) malloc(infoheader.biWidth * infoheader.biHeight * 4);
    memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);
 
    // Wczytywanie pikseli
	for (i=0; i < infoheader.biWidth*infoheader.biHeight; i++)
    {            
            fread(&rgb, sizeof(rgb), 1, l_file); 
            l_texture[j+0] = rgb.rgbtRed; 
            l_texture[j+1] = rgb.rgbtGreen; 
            l_texture[j+2] = rgb.rgbtBlue; 
            l_texture[j+3] = 255; // Alpha
            j += 4; 
    }
	fclose(l_file); 
     
    glBindTexture(GL_TEXTURE_2D, num_texture); // Zg�oszenie tekstury (poprzez jej unikatowe ID)
    // Ustawienie parametr�w rekstury
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Tiling tekstury, gdy za ma�a
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); 
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); 

    // Stw�rz taka teksture w OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);
    // I mipmapy do niej
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.biWidth, infoheader.biHeight, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

    free(l_texture); 

    return (num_texture); // Zwr�� identyfikator OpenGL ID tekstury 
}


int WczytajTekstureAlpha(char *filename)
{
	// Pomocnicze
	int i, j = 0;
	FILE *l_file;
	unsigned char *l_texture;
	BITMAPFILEHEADER fileheader;
	BITMAPINFOHEADER infoheader;
	RGBTRIPLE rgb;
	num_texture++;

	if ((l_file = fopen(filename, "rb")) == NULL) return (-1);
	// Nag��wek:
	fread(&fileheader, sizeof(fileheader), 1, l_file);
	fseek(l_file, sizeof(fileheader), SEEK_SET);
	fread(&infoheader, sizeof(infoheader), 1, l_file);
	// Alokacja pami�ci
	l_texture = (byte *)malloc(infoheader.biWidth * infoheader.biHeight * 4);
	memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);

	// Wczytywanie pikseli
	for (i = 0; i < infoheader.biWidth*infoheader.biHeight; i++)
	{
		fread(&rgb, sizeof(rgb), 1, l_file);
		l_texture[j + 0] = 0;
		l_texture[j + 1] = rgb.rgbtGreen;
		l_texture[j + 2] = rgb.rgbtBlue;
		l_texture[j + 3] = rgb.rgbtRed; // Alpha
		j += 4;
	}
	fclose(l_file);

	glBindTexture(GL_TEXTURE_2D, num_texture); // Zg�oszenie tekstury (poprzez jej unikatowe ID)
											   // Ustawienie parametr�w rekstury
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Tiling tekstury, gdy za ma�a
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); 

	// Stw�rz taka teksture w OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);
	// I mipmapy do niej
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.biWidth, infoheader.biHeight, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

	free(l_texture);

	return (num_texture); // Zwr�� identyfikator OpenGL ID tekstury 
}

