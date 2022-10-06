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
    glCOlor3f(10, 0.0, 0.5);
    glBegin(GL_QUADS);
        glVertex2f(xcent - w, ycent - w);
        glVertex2f(xcent - w, ycent + w);
        glVertex2f(xcent + w, ycent + w);
        glVertex2f(xcent + w, ycent - w);

    glEnd();
}