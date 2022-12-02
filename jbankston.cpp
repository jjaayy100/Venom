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

struct Blobal
{
    GLuint LostTexture;
} B;

void get_textures(GLuint Losttexture)
{
    B.LostTexture = Losttexture;
}

void display_lost(int xres, int yres)
{
    glColor3f(0.5f, 0.5f, 0.5f);
    glBindTexture(GL_TEXTURE_2D, B.LostTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(0, 0);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(0, yres);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, yres);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, 0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

}
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
	ggprint16(&r, 50, 0xffffffff, "Dont Be Sorry");
	ggprint16(&r, 50, 0xffffffff, "Be Better");

        ggprint16(&r, 50, 0xffffffff, "Press 'R' To Restart");
}

void initHawk(Hawk *h)
{
    if (rand()%1000 < 5)
    {	
	h->status = 1; 
	h->pos[0] = rand()%30; 
	h->pos[1] = rand()%30; 
    }
}

void cleanhawk(Hawk *h)
{
    h->status = 0;
    h->pos[0] = -1;
    h->pos[1] = -1;

}

//int hawkphysics(int *head[], Hawk *h)
//{
//   if (*head[0] == h->pos[0] && *head[1] == h->pos[1]){
//	return 1;
//    }
//    return 0;
//}

void hawkgameover(int snakelength ,int pos[80*80][2], int *gameover, Hawk *h)
{
    for (int i=1; i< snakelength; i++) {
	if ( pos[i][0] == h->pos[0] && 
		pos[i][1] == h->pos[1]) {
	    *gameover=1;
	    return;
	}
    }


}

void cratehawks(Hawk *h, int cent[])
{
    getGridCenter(h->pos[1],h->pos[0],cent);
        glColor3f(0.82, 0.1f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2i(cent[0]-4, cent[1]-3);
        glVertex2i(cent[0]-4, cent[1]+4);
        glVertex2i(cent[0]+3, cent[1]+4);
        glVertex2i(cent[0]+3, cent[1]-3);
        glEnd();

}


