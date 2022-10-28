//jayden Bankston
//Source file
//
//
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "log.h"
#include "fonts.h"

using namespace std;

int Money()
{
    cout << "Jay Money!" << endl;
    return 0;
}
void youlost(int lost)
{
    if (lost <= 0)
    {
	cout << "You Lost" << endl; 
	lost++;
    }

   
}
void showyoulost(int xres, int yres)
{
    Rect r; 
    int xcent = xres / 2; 
    int ycent = yres / 2;
    int w = 350;
    int h = 220; 
    glColor3f(0, 0, 0); 
    glBegin(GL_QUADS);
            glVertex2f(xcent-w, ycent-h);
            glVertex2f(xcent-w, ycent+h);
            glVertex2f(xcent+w, ycent+h);
            glVertex2f(xcent+w, ycent-h);
    glEnd();
    r.left = xcent;
    r.bot = ycent + 80;
    r.center = 50;
    ggprint16(&r, 50, 0xffffffff, "YOU LOST");
}
