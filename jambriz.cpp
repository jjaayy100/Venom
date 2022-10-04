//Jorge Ambriz
//Source functions

#include <iostream>
#include <GL/glx.h>
using namespace std;

int jhello()
{
    cout << "Jorge" << endl;
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
