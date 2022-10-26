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

struct Jlobal {
    int gamestart;
    int seconds;
    int min;
    int tmp;
    Jlobal(){
        gamestart = time(NULL);
    }
} j;

int jhello()
{
    cout << "Jorge" << endl;
    return 0;
}

int timer(int xres, int yres)
{
    if (j.seconds == 60) {
        j.tmp = time(NULL) - j.gamestart; //grab the 59 seconds
        j.gamestart = j.gamestart + j.tmp; //Add them to the start
        j.seconds = 0; //reset the seconds
        j.min++; //Add a minute
    }
    else {
        j.seconds = time(NULL) - j.gamestart; //count upwards
    }
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
    if (j.min<10 && j.seconds<10) {
        ggprint16(&r, 50, 0xffffffff, "Timer: 0%d:0%d",j.min,j.seconds);
    }
    else if ((j.min<10 && j.seconds>10)) {
        ggprint16(&r, 50, 0xffffffff, "Timer: 0%d:%d",j.min,j.seconds);
    }
    else {
        ggprint16(&r, 50, 0xffffffff, "Timer: %d:%d",j.min,j.seconds);
    }
    return 0;
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
