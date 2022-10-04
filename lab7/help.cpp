// Yeana Bond
// help source file 
// Oct 3
//
//
#include <GL/glx.h>
#include "fonts.h"

unsigned int help_screen(unsigned int h)
{
	h = h ^ 1;
	return h;

}


void show_help_screen(int xres, int yres)
{
    int xcent = xres/2;
    int ycent = yres/2;
    int w = 300;
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    	glVertex2f(xcent -w, ycent -w);
    	glVertex2f(xcent -w, ycent +w);
    	glVertex2f(xcent +w, ycent +w);
    	glVertex2f(xcent +w, ycent -w);

    glEnd();

    Rect r;
    glClear(GL_COLOR_BUFFER_BIT);
    r.bot = yres - 20;
    r.left = 10;
    r.center = 0;
    ggprint8b(&r, 16, 0x00ff0000, " HELP ");
}
