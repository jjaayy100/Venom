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
#include "jbankston.h"

using namespace std;

struct Glo {
    int gridDim;
    Glo(){
	Hawk hawk;
	gridDim = 40;
    }
}n;

//typedef struct t_hawk{
//        int status;
//        int pos[2];
//} Hawk;

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
    ggprint16(&r, 50, 0xffffffff, "Press 'R' To Restart");
}

void initHawk(Hawk *h)
{
    h->status = 1; 
    h->pos[0] = 25; 
    h->pos[1] = 2; 
}

int hawkphysics(int *head[], Hawk *h)
{
    while(1) {
	h->pos[0] = rand() % n.gridDim;
	h->pos[1] = rand() % n.gridDim;
    }

}

void cratehawks(int xres, int yres, Hawk *h, int cent[])
{
    getGridCenter(h->pos[1],h->pos[0],cent);
        glColor3f(0.82, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2i(cent[0]-4, cent[1]-3);
        glVertex2i(cent[0]-4, cent[1]+4);
        glVertex2i(cent[0]+3, cent[1]+4);
        glVertex2i(cent[0]+3, cent[1]-3);
        glEnd();

	//r.left   = g.xres/2;
        //r.bot    = g.yres-100;
        //r.center = 1;
}


