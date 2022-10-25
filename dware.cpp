//Darien Ware
//Source File

#include <iostream>
#include <GL/glx.h>
#include "log.h"
#include "fonts.h"

using namespace std;

int greeting()
{
    cout << "Darien!" << endl;
    return 0;
}

unsigned int check_startup(unsigned int s)
{
    s = s ^ 1;
    return s;
}

void show_startup(int x, int y)
{
    Rect r;
    int xcent = x / 2;
    int ycent = y / 2;
    int w = 400;
    int h = 400;
   //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   //glEnable(GL_BLEND);
    glColor3f(0.15, 0.5, 0.1);
   //glColor4f(1.0, 0.0, 0.5, 0.5);
    glBegin(GL_QUADS);
        glVertex2f(xcent - w, ycent - h);
        glVertex2f(xcent - w, ycent + h);
        glVertex2f(xcent + w, ycent + h);
        glVertex2f(xcent + w, ycent - h);
    glEnd();
    r.left = xcent;
    r.bot = ycent + 100;
    r.center = 50;
    ggprint16(&r, 150, 0xffffffff, "VENOM");
    //glDisable(GL_BLEND);
}
