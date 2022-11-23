//Darien Ware
//Source File

#include <iostream>
#include <GL/glx.h>
#include "log.h"
#include "fonts.h"
#include "jambriz.h"

using namespace std;

struct background{
    GLuint BackgroundTexture;
    GLuint BackgroundTexture2;
    GLuint BackgroundTexture3;
    GLuint BackgroundTexture4;
    GLuint BackgroundTexture5;

} d;


void dget_textures(GLuint BackgroundTexture)
{
    d.BackgroundTexture = BackgroundTexture;
}
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

//Within snake.cpp, you can change the boardDim(dimansions) on line 947,955,and 508
//doing this will change how large the grid and its size is. try to find a way to toggle and cycle through it

unsigned int check_map(unsigned int k)
{
    k = k ^ 1;
    return k;
}

//resizing should be done in render. The check keys function should just go to the call in render
void resize_map(int x, int y, int boarddim, int griddim)
{
    int brs = boarddim / 20;
    int grs = griddim / 2;
    //x = g.xres
    //y = g.yres
//    Rect r;
    int b2 = boarddim / 2;
    //right shift operation of xres and yres
    int s0 = x>>1;
    int s1 = y>>1;
    //center of the grid
    //int center[2];
    //set the viewing area on screen
    glViewport(0, 0, x, y); 
    //clear color buffer
    glClearColor(0.1f, 0.2f, 0.3f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //init matrices
    glMatrixMode (GL_PROJECTION); glLoadIdentity();
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
    //this sets to 2D mode (no perspective)
    glOrtho(0, x, 0, y, -1, 1); 
    //  
    //screen background
    glColor3f(0.5f, 0.5f, 0.5f);
    glBindTexture(GL_TEXTURE_2D, 0); //g.marbleTexture);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(0,      0); 
        glTexCoord2f(0.0f, 1.0f); glVertex2i(0,      y); 
        glTexCoord2f(1.0f, 1.0f); glVertex2i(x, y); 
        glTexCoord2f(1.0f, 0.0f); glVertex2i(x, 0); 
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0); 

    //draw the main board in a different color and size
    glColor3f(0.2f, 0.5f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2i(s0-b2, s1-b2);
        glVertex2i(s0-b2, s1+b2);
        glVertex2i(s0+b2, s1+b2);
        glVertex2i(s0+b2, s1-b2);
    glEnd();
    //  
    //grid lines...
    int x0 = s0-b2;
    int x1 = s0+b2;
    int y0 = s1-b2;
    int y1 = s1+b2;
    glColor3f(0.3f, 0.3f, 0.2f);
    glBegin(GL_LINES);
    for (int i=1; i<brs; i++) {
        y0 += 20; 
        glVertex2i(x0,y0);
        glVertex2i(x1,y0);
    }
    x0 = s0-b2;
    y0 = s1-b2;
    y1 = s1+b2;
    for (int j=1; j<grs; j++) {
        x0 += 20;
        glVertex2i(x0,y0);
        glVertex2i(x0,y1);
    }
    glEnd();
}
//new_board_dim()