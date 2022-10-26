//Paramveer Takkar	
//Source File

#include <iostream>
#include <GL/glx.h>

unsigned int pauseGame(unsigned int p)
{
    p = p ^ 1;
    return p;
}

void show_pauseScreen(int xres, int yres)
{
    int xcent = xres / 2;
    int ycent = yres / 2;
    int w = 200;
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    	glVertex2f(xcent - w, ycent - w);
	glVertex2f(xcent - w, ycent + w);
	glVertex2f(xcent + w, ycent + w);
	glVertex2f(xcent + w, ycent - w);

    glEnd();



}
