// Student Name: Yeana Bond
// Yeana's Source File 

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

// Initially, changing color of the snake depended on the time function.
// I noticed a pattern in the value of float variable, change.
// change_snake_color_1() - change_snake_color_3() were implemented 
// in order to change the color of the snake to a designated color 
// upon a number of key input 
unsigned int help_screen(unsigned int h)
{
    float a;
	a = 5 / 2;
	cout << " " << a << "\n" << endl;
	h = h ^ 1;
	return h;

}


void show_help_screen(int xres, int yres)
{
    int xcent = xres/2;
    int ycent = yres/2;
    int w = 300;
    glColor3f(0.9, 0.6, 1.0);
    glBegin(GL_QUADS);
    	glVertex2f(xcent -w, ycent -w);
    	glVertex2f(xcent -w, ycent +w);
    	glVertex2f(xcent +w, ycent +w);
    	glVertex2f(xcent +w, ycent -w);

    glEnd();

    Rect r;
    //glClear(GL_COLOR_BUFFER_BIT);
    r.bot = yres - 80;
    r.left = 150;
    r.center = 0;
    ggprint16(&r, 16, 0x00ffffff, " ============ H E L P    S C R E E N ============ ");


    r.bot = yres - 120;
    r.left = 150;
    r.center = 0;
    
    ggprint16(&r, 16, 0x00000000, "  k  -- change the color of the sna'K'e   (YEANA)");
    ggprint16(&r, 16, 0x0089508c, " === ");

    
    r.bot = yres - 160;
    r.left = 150;
    r.center = 0;
    
    ggprint16(&r, 16, 0x0089508c, "  b  -- change the 'B'ackground   (JORGE) ");
    ggprint16(&r, 16, 0x0089508c, " === ");

    
    r.bot = yres - 200;
    r.left = 150;
    r.center = 0;
    
    ggprint16(&r, 16, 0x00000000, "  z  -- change the si'Z'e of the grid   (DARIEN)");
    ggprint16(&r, 16, 0x0089508c, " === ");

    r.bot = yres - 240;
    r.left = 150;
    r.center = 0;
   
    ggprint16(&r, 16, 0x0089508c, "  p  -- 'P'ause the game  (JORGE + YEANA) ");
    ggprint16(&r, 16, 0x0089508c, " === ");

    
    r.bot = yres - 280;
    r.left = 150;
    r.center = 0;
    
    ggprint16(&r, 16, 0x00000000, "  t  -- display the 'T'imer   (JORGE) ");
    ggprint16(&r, 16, 0x0089508c, " === ");


    r.bot = yres - 320;
    r.left = 150;
    r.center = 0;
    
    ggprint16(&r, 16, 0x0089508c, "  e  -- play againt an 'E'nemy (a hawk)  (JAY) ");
    ggprint16(&r, 16, 0x0089508c, " === ");

    r.bot = yres - 360;
    r.left = 150;
    r.center = 0;
    
    ggprint16(&r, 16, 0x00000000, "  c  -- view the 'C'redit screen  (JORGE)");
    ggprint16(&r, 16, 0x0089508c, " === ");

    r.bot = yres - 400;
    r.left = 150;
    r.center = 0;
    
    ggprint16(&r, 16, 0x0089508c, "  v  -- view the game-o'V'er screen   (JAY) ");
    ggprint16(&r, 16, 0x0089508c, " === ");

    
    r.bot = yres - 440;
    r.left = 150;
    r.center = 0;

    ggprint16(&r, 16, 0x00000000, "  h  -- view the 'H'elp screen   (YEANA)  ");
    ggprint16(&r, 16, 0x0089508c, " === ");

    r.bot = yres - 480;
    r.left = 150;
    r.center = 0;
   
    ggprint16(&r, 16, 0x0089508c, "  s  -- 'S'tart the game   (DARIEN) ");
    ggprint16(&r, 16, 0x0089508c, " === ");


    r.bot = yres - 520;
    r.left = 150;
    r.center = 0;

    ggprint16(&r, 16, 0x00000000, "  r  -- 'R'eset the game  ");
    ggprint16(&r, 16, 0x0089508c, " === ");

}

// RGB value reference: https://www.tug.org/pracjourn/2007-4/walden/color.pdf
// I am pretty sure I can use a better data structure after looking at the above
// file: there is a patten I can follow 

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

        case 3:
            red = 0.4f;
            break;

        case 4:
            red = 1.0f;
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
        
        case 3:
            green = 0.1f;
            break;

        case 4:
            green = 0.4f;
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

        case 3:
            blue = 0.7f;
            break;

        case 4:
            blue = 0.0f;
            break;

        default:
            blue = 0.5f;
    }

    return blue; 
}
