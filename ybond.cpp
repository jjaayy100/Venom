// Student Name: Yeana Bond
// New source file 1

using namespace std;
#include <iostream>

// in order to call rand() and srand()
#include <cstdlib>
// in order to use time()
#include <ctime>
using namespace std;
#include <GL/glx.h>
#include "fonts.h"
 


int show_my_name()
{
    cout << "Yeana.\n" << endl;
    return 0;
}



// Oct 25 update

float change_snake_color()
{
    srand (static_cast <unsigned> (time(NULL)));
    cout << "Press k to change the snake color.\n" << endl;

    //From:  https://www.demo2s.com/cpp/cpp-float-c-static-cast-float-loops-floor-loops.html
    //The below line 
    float change = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    // cout << change << "\n" <<  endl;

    return change;


}

unsigned int help_screen(unsigned int h)
{
    float a;
	a = 5 / 2;
	cout << " " << a << "\n" << endl;
	h = h ^ 1;
	return h;

}

unsigned int switch_K(unsigned int k)
{
   
	k = k ^ 1;
	return k;

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
    //glClear(GL_COLOR_BUFFER_BIT);
    r.bot = yres - 20;
    r.left = 10;
    r.center = 0;
    ggprint8b(&r, 16, 0x00ff0000, " HELP ");


    r.bot = yres - 30;
    r.left = 100;
    r.center = 0;
    ggprint8b(&r, 16, 0x00ff0000, " Press k: to change color of the snake ");

}

float change_snake_color_1(int i)
{
    float red = 0.0f;
    switch(i) {
        case 1:
            red = 0.9f;
            break;

        case 2:
            red = 0.0f;
            break;

        default:
            red = 0.5f;

    } 

    return red;
}

float change_snake_color_2(int i)
{
    float green = 0.0f;
    switch(i) {
        case 1:
            green = 0.0f;
            break;

        case 2:
            green = 0.0f;
            break;

        default:
            green = 0.5f;

    } 

    return green;
}

float change_snake_color_3(int i)
{
    float blue = 0.0f;
    switch(i) {
        case 1:
            blue = 0.0f;
            break;

        case 2:
            blue = 1.0f;
            break;

        default:
            blue = 0.5f;
    }

    return blue; 
}

