//Jorge Ambriz
//CMPS 3350-SE
//Source file

#include <iostream>
#include <GL/glx.h>
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include "fonts.h"
using namespace std;

#define MAXBUTTONS 4
typedef struct t_button {
	Rect r;
	char text[32];
	int over;
	int down;
	int click;
	float color[3];
	float dcolor[3];
	unsigned int text_color;
} Button;

struct Jlobal {
    int gamestart;
    int reset;
    int gameover;
    int timerstart;
    int seconds;
    int min;
    int tmp;
    int pause;
    int whatbackground;
    GLuint BackGroundTexture;
	GLuint BackGroundTexture2;
	GLuint BackGroundTexture3;
	GLuint BackGroundTexture4;
	GLuint BackGroundTexture5;
	GLuint snakectexture;
    Button button[MAXBUTTONS];
	int nbuttons;
    Jlobal(){
        gamestart = time(NULL);
        timerstart = time(NULL);
        whatbackground = 1;
        nbuttons = 0;
    }
} j;

void get_textures(GLuint BackgroundTexture, GLuint BackgroundTexture2, GLuint BackgroundTexture3, GLuint BackgroundTexture4, GLuint BackgroundTexture5)
{
    j.BackGroundTexture = BackgroundTexture;
    j.BackGroundTexture2 = BackgroundTexture2;
    j.BackGroundTexture3 = BackgroundTexture3;
    j.BackGroundTexture4 = BackgroundTexture4;
    j.BackGroundTexture5 = BackgroundTexture5;

}

void credits_screen_box(Button button[])
{
    j.button[3] = button[3];
    j.button[j.nbuttons].r.width = 140;
	j.button[j.nbuttons].r.height = 60;
	j.button[j.nbuttons].r.left = 20;
	j.button[j.nbuttons].r.bot = 500;
	j.button[j.nbuttons].r.right =
	   j.button[j.nbuttons].r.left + j.button[j.nbuttons].r.width;
	j.button[j.nbuttons].r.top =
	   j.button[j.nbuttons].r.bot + j.button[j.nbuttons].r.height;
	j.button[j.nbuttons].r.centerx =
	   (j.button[j.nbuttons].r.left + j.button[j.nbuttons].r.right) / 2;
	j.button[j.nbuttons].r.centery =
	   (j.button[j.nbuttons].r.bot + j.button[j.nbuttons].r.top) / 2;
	strcpy(j.button[j.nbuttons].text, "Credits");
	j.button[j.nbuttons].down = 0;
	j.button[j.nbuttons].click = 0;
	j.button[j.nbuttons].color[0] = 0.0f;
	j.button[j.nbuttons].color[1] = 0.4f;
	j.button[j.nbuttons].color[2] = 0.0f;
	j.button[j.nbuttons].dcolor[0] = j.button[j.nbuttons].color[0] * 0.5f;
	j.button[j.nbuttons].dcolor[1] = j.button[j.nbuttons].color[1] * 0.5f;
	j.button[j.nbuttons].dcolor[2] = j.button[j.nbuttons].color[2] * 0.5f;
	j.button[j.nbuttons].text_color = 0x00ffffff;
}

//This function will update values from the Global struct in snake.cpp
//to Jlobal in this source file to increase functionality. This could be improved.
void get_class_data(int gameover, int timestat, int reset, int pause)
{
    j.pause = pause;
    //For timer behavior
    j.gameover = gameover;
    j.reset = reset;
    if (timestat == 0 || j.gameover == 1 || reset == 1) {
            j.timerstart = time(NULL);
            j.seconds = 0;
            j.min = 0;
    }
}

int jhello()
{
    cout << "Jorge" << endl;
    return 0;
}

int timer(int xres, int yres)
{
    if (j.seconds >= 60) {
        j.tmp = time(NULL) - j.timerstart; //grab the 59 seconds
        j.timerstart = j.timerstart + j.tmp; //Add them to the start
        j.seconds = 0; //reset the seconds
        j.min++; //Add a minute
    }
    else {
        j.seconds = time(NULL) - j.timerstart; //count upwards
    }
    Rect r;
    int w = 76;
    int h = w/2;
    int xpos = (xres/2)+300;
    int ypos = (yres/2)+160;
    glColor3ub(50, 150, 50); 
    glPushMatrix();
    glTranslatef(xpos, ypos, 0.0f);
    glBegin(GL_QUADS); 
        glVertex2f(-w, -h);
        glVertex2f(-w,  h);
        glVertex2f( w,  h);
        glVertex2f( w, -h);
        glEnd();
    glPopMatrix();
    r.left = xpos;
    r.bot = ypos-8;
    r.center = 50;
    //Display time in the corect 00:00 (min:sec) format
    if (j.min<10 && j.seconds<10) {
        ggprint16(&r, 50, 0xffffffff, "0%d:0%d",j.min,j.seconds);
    }
    else if (j.min<10 && j.seconds>=10) {
        ggprint16(&r, 50, 0xffffffff, "0%d:%d",j.min,j.seconds);
    }
    else if (j.min>=10 && j.seconds<10) {
        ggprint16(&r, 50, 0xffffffff, "%d:0%d",j.min,j.seconds);
    }
    else {
        ggprint16(&r, 50, 0xffffffff, "%d:%d",j.min,j.seconds);
    }
    return 0;
}

unsigned int set_credits_state(unsigned int credits) 
{
    credits = credits ^ 1;
    return credits;
}

int changebackground(int background)
{
    int newbackground = background + 1;
    if (newbackground > 5)
    {
        newbackground = 1;
    }
    //cout << newbackground << endl; //for testing purposes
    return newbackground;
}

unsigned int pauseGame(unsigned int p)
{
    p = p ^ 1;
    return p;
}

void display_background(int xres, int yres, int background_num)
{
    if (background_num == 1) {
    glColor3f(0.5f, 0.5f, 0.5f);
	glBindTexture(GL_TEXTURE_2D, j.BackGroundTexture);
	//glBindTexture(GL_TEXTURE_2D, setBackgroundTexture());
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(0,      0);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(0,      yres);
		glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, yres);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
    }
    else if (background_num == 2){
        glColor3f(0.5f, 0.5f, 0.5f);
	glBindTexture(GL_TEXTURE_2D, j.BackGroundTexture2);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(0,      0);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(0,      yres);
		glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, yres);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
    }
    else if(background_num == 3) {
        glColor3f(0.5f, 0.5f, 0.5f);
	glBindTexture(GL_TEXTURE_2D, j.BackGroundTexture3);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(0,      0);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(0,      yres);
		glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, yres);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
    }
    else if(background_num == 4) {
        glColor3f(0.5f, 0.5f, 0.5f);
	glBindTexture(GL_TEXTURE_2D, j.BackGroundTexture4);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(0,      0);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(0,      yres);
		glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, yres);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
    }
    else if(background_num == 5) {
        glColor3f(0.5f, 0.5f, 0.5f);
	glBindTexture(GL_TEXTURE_2D, j.BackGroundTexture5);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(0,      0);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(0,      yres);
		glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, yres);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
    }

}

void show_credits_screen(int xres, int yres, GLuint snakectexture)
{
    glColor3f(1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, snakectexture);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(0,      0);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(0,      yres);
		glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, yres);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);

    //Edit names and profile pictures onto credits screen.
    /* older render code
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
    */
}

void show_pauseScreen(int xres, int yres)
{
    Rect r;
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    //glColor3f(1.0, 1.0, 1.0);
    glColor4f(0.0, 0.0, 0.0, 0.5);
    glBegin(GL_QUADS);
        glVertex2i(0,       0);
        glVertex2i(0,    yres);
        glVertex2i(xres, yres);
        glVertex2i(xres,    0);
    glEnd();
    glDisable(GL_BLEND);
    r.left = xres/2;
    r.bot = yres/2;
    r.center = 50;
    ggprint16(&r, 50, 0xffffffff, "Paused");



}
