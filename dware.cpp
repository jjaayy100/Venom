//Darien Ware
//Source File

#include <iostream>
#include <GL/glx.h>

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
    int xcent = x / 2;
    int ycent = y / 2;
    int w = 300;
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glColor3f(1.0, 0.0, 0.5);
    glColor4f(1.0, 0.0, 0.5, 0.5);
    glBegin(GL_QUADS);
        glVertex2f(xcent - w, ycent - w);
        glVertex2f(xcent - w, ycent + w);
        glVertex2f(xcent + w, ycent + w);
        glVertex2f(xcent + w, ycent - w);

    glEnd();
    glDisable(GL_BLEND);
}