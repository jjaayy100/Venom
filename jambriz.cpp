//Jorge Ambriz
//Source functions

#include <iostream>
#include <GL/glx.h>
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include "fonts.h"
using namespace std;

int jhello()
{
    cout << "Jorge" << endl;
    return 0;
}

void timer(int xres, int yres, int gamestart)
{
    int gamecount = time(NULL) - gamestart;
    Rect r;
    int w = 76;
    int h = w/2;
    int xpos = (xres/2)+300;
    int ypos = (yres/2)+160;
    glColor3ub(150, 160, 220); 
    glPushMatrix();
    glTranslatef(xpos, ypos, 0.0f);
    glBegin(GL_QUADS); 
        glVertex2f(-w, -h);
        glVertex2f(-w,  h);
        glVertex2f( w,  h);
        glVertex2f( w, -h);
        glEnd();
    glPopMatrix();
    r.left = xpos-12;
    r.bot = ypos-15;
    r.center = 50;
    ggprint16(&r, 50, 0xffffffff, "Playtime: %d",gamecount);
}

unsigned int set_credits_state(unsigned int credits) 
{
    credits = credits ^ 1;
    return credits;
}

void show_credits_screen(int xres, int yres)
{
    int xcent = xres / 2;
    int ycent = yres / 2;
    int w = 500;
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    	glVertex2f(xcent-w, ycent-w);
    	glVertex2f(xcent-w, ycent+w);
    	glVertex2f(xcent+w, ycent+w);
    	glVertex2f(xcent+w, ycent-w);
    glEnd();

}
