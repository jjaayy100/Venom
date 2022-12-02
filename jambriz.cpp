// Jorge Ambriz
// CMPS 3350-SE
// Source file

#include <iostream>
#include <GL/glx.h>
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include "fonts.h"
#include "jambriz.h"
using namespace std;


struct Jlobal
{
    int gamestart;
    int reset;
    int gameover;
    int timerstart;
    int seconds;
    int min;
    int tmp;
    int pause;
    int whatbackground;
    int xres;
    int yres;
    unsigned int credits;
    GLuint BackGroundTexture;
    GLuint BackGroundTexture2;
    GLuint BackGroundTexture3;
    GLuint BackGroundTexture4;
    GLuint BackGroundTexture5;
    GLuint snakectexture;
    Button button[MAXBUTTONS];
    int nbuttons;
    Jlobal() {
        gamestart = time(NULL);
        timerstart = time(NULL);
        whatbackground = 1;
        credits = 0;
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

Button credits_screen_box()
{
    j.button[j.nbuttons].r.width = 140;
    j.button[j.nbuttons].r.height = 60;
    j.button[j.nbuttons].r.left = 20;
    j.button[j.nbuttons].r.bot = 50;
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
    j.nbuttons++;
    return j.button[0];
}

Button donec_box()
{
    j.button[j.nbuttons].r.width = 140;
    j.button[j.nbuttons].r.height = 60;
    j.button[j.nbuttons].r.left = 20;
    j.button[j.nbuttons].r.bot = 50;
    j.button[j.nbuttons].r.right =
        j.button[j.nbuttons].r.left + j.button[j.nbuttons].r.width;
    j.button[j.nbuttons].r.top =
        j.button[j.nbuttons].r.bot + j.button[j.nbuttons].r.height;
    j.button[j.nbuttons].r.centerx =
        (j.button[j.nbuttons].r.left + j.button[j.nbuttons].r.right) / 2;
    j.button[j.nbuttons].r.centery =
        (j.button[j.nbuttons].r.bot + j.button[j.nbuttons].r.top) / 2;
    strcpy(j.button[j.nbuttons].text, "Done");
    j.button[j.nbuttons].down = 0;
    j.button[j.nbuttons].click = 0;
    j.button[j.nbuttons].color[0] = 1.0f;
    j.button[j.nbuttons].color[1] = 1.0f;
    j.button[j.nbuttons].color[2] = 1.0f;
    j.button[j.nbuttons].dcolor[0] = j.button[j.nbuttons].color[0] * 0.5f;
    j.button[j.nbuttons].dcolor[1] = j.button[j.nbuttons].color[1] * 0.5f;
    j.button[j.nbuttons].dcolor[2] = j.button[j.nbuttons].color[2] * 0.5f;
    j.button[j.nbuttons].text_color = 0x00000000;
    j.nbuttons++;
    return j.button[1];

}

// This function will update values from the Global struct in snake.cpp
// to Jlobal in this source file to increase functionality. This could be improved.
void get_class_data(int gameover, int timestat, int reset, int pause, int credits)
{
    j.credits = credits;
    j.pause = pause;
    // For timer behavior
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
        j.tmp = time(NULL) - j.timerstart;   // grab the 59 seconds
        j.timerstart = j.timerstart + j.tmp; // Add them to the start
        j.seconds = 0;                       // reset the seconds
        j.min++;                             // Add a minute
    }
    else {
        j.seconds = time(NULL) - j.timerstart; // count upwards
    }
    Rect r;
    int w = 76;
    int h = w / 2;
    int xpos = (xres / 2) + 300;
    int ypos = (yres / 2) + 160;
    glColor3ub(50, 150, 50);
    glPushMatrix();
    glTranslatef(xpos, ypos, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-w, -h);
        glVertex2f(-w, h);
        glVertex2f(w, h);
        glVertex2f(w, -h);
    glEnd();
    glPopMatrix();
    r.left = xpos;
    r.bot = ypos - 8;
    r.center = 50;
    // Display time in the corect 00:00 (min:sec) format
    if (j.min < 10 && j.seconds < 10) {
        ggprint16(&r, 50, 0xffffffff, "0%d:0%d", j.min, j.seconds);
    }
    else if (j.min < 10 && j.seconds >= 10) {
        ggprint16(&r, 50, 0xffffffff, "0%d:%d", j.min, j.seconds);
    }
    else if (j.min >= 10 && j.seconds < 10) {
        ggprint16(&r, 50, 0xffffffff, "%d:0%d", j.min, j.seconds);
    }
    else {
        ggprint16(&r, 50, 0xffffffff, "%d:%d", j.min, j.seconds);
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
    if (newbackground > 5) {
        newbackground = 1;
    }
    // cout << newbackground << endl; //for testing purposes
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
        // glBindTexture(GL_TEXTURE_2D, setBackgroundTexture());
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex2i(0, 0);
            glTexCoord2f(0.0f, 1.0f); glVertex2i(0, yres);
            glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, yres);
            glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, 0);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else if (background_num == 2) {
        glColor3f(0.5f, 0.5f, 0.5f);
        glBindTexture(GL_TEXTURE_2D, j.BackGroundTexture2);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex2i(0, 0);
            glTexCoord2f(0.0f, 1.0f); glVertex2i(0, yres);
            glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, yres);
            glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, 0);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else if (background_num == 3) {
        glColor3f(0.5f, 0.5f, 0.5f);
        glBindTexture(GL_TEXTURE_2D, j.BackGroundTexture3);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex2i(0, 0);
            glTexCoord2f(0.0f, 1.0f); glVertex2i(0, yres);
            glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, yres);
            glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, 0);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else if (background_num == 4) {
        glColor3f(0.5f, 0.5f, 0.5f);
        glBindTexture(GL_TEXTURE_2D, j.BackGroundTexture4);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex2i(0, 0);
            glTexCoord2f(0.0f, 1.0f); glVertex2i(0, yres);
            glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, yres);
            glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, 0);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else if (background_num == 5) {
        glColor3f(0.5f, 0.5f, 0.5f);
        glBindTexture(GL_TEXTURE_2D, j.BackGroundTexture5);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex2i(0, 0);
            glTexCoord2f(0.0f, 1.0f); glVertex2i(0, yres);
            glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, yres);
            glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, 0);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

int check_credits_box(XEvent *e)
{
    static int savex = 0;
    static int savey = 0;
    int i, x, y;
    int lbutton = 0;
    int rbutton = 0;
    if (e->type == ButtonRelease)
        return 0;
    if (e->type == ButtonPress) {
        if (e->xbutton.button == 1) {
            // Left button is down
            lbutton = 1;
        }
        if (e->xbutton.button == 3) {
            // Right button is down
            rbutton = 1;
            if (rbutton){}
        }
    }
    x = e->xbutton.x;
    y = e->xbutton.y;
    y = j.yres - y;
    if (savex != e->xbutton.x || savey != e->xbutton.y) {
        // Mouse moved
        savex = e->xbutton.x;
        savey = e->xbutton.y;
    }
    for (i = 0; i < j.nbuttons; i++) {
        j.button[i].over = 0;
        if (x >= j.button[i].r.left &&
            x <= j.button[i].r.right &&
            y >= j.button[i].r.bot &&
            y <= j.button[i].r.top) {
            j.button[i].over = 1;
            if (j.button[i].over) {
                if (lbutton) {
                    switch (i) {
                    case 0:
                        j.credits = 1;
                        break;
                    case 1:
                        j.credits = 0;
                        break;
                    }
                }
            }
        }
    }
    return 0;
}

void draw_credits_box()
{
    Rect r;
    if (j.button[0].over) {
        int w = 2;
        glColor3f(1.0f, 1.0f, 0.0f);
        // draw a highlight around button
        glLineWidth(3);
        glBegin(GL_LINE_LOOP);
            glVertex2i(j.button[0].r.left - w, j.button[0].r.bot - w);
            glVertex2i(j.button[0].r.left - w, j.button[0].r.top + w);
            glVertex2i(j.button[0].r.right + w, j.button[0].r.top + w);
            glVertex2i(j.button[0].r.right + w, j.button[0].r.bot - w);
            glVertex2i(j.button[0].r.left - w, j.button[0].r.bot - w);
        glEnd();
        glLineWidth(1);
    }
    if (j.button[0].down) {
        glColor3fv(j.button[0].dcolor);
    }
    else {
        glColor3fv(j.button[0].color);
    }
    glBegin(GL_QUADS);
        glVertex2i(j.button[0].r.left, j.button[0].r.bot);
        glVertex2i(j.button[0].r.left, j.button[0].r.top);
        glVertex2i(j.button[0].r.right, j.button[0].r.top);
        glVertex2i(j.button[0].r.right, j.button[0].r.bot);
    glEnd();
    r.left = j.button[0].r.centerx;
    r.bot = j.button[0].r.centery - 8;
    r.center = 1;
    if (j.button[0].down) {
        ggprint16(&r, 0, j.button[0].text_color, "Pressed!");
    }
    else {
        ggprint16(&r, 0, j.button[0].text_color, j.button[0].text);
    }
}

void show_credits_screen(int xres, int yres, GLuint snakectexture)
{
    j.xres = xres;
    j.yres = yres;
    Rect r;
    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, snakectexture);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(0, 0);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(0, yres);
        glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, yres);
        glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, 0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    if (j.button[1].over) {
        int w = 2;
        glColor3f(1.0f, 1.0f, 0.0f);
        // draw a highlight around button
        glLineWidth(3);
        glBegin(GL_LINE_LOOP);
            glVertex2i(j.button[1].r.left - w, j.button[1].r.bot - w);
            glVertex2i(j.button[1].r.left - w, j.button[1].r.top + w);
            glVertex2i(j.button[1].r.right + w, j.button[1].r.top + w);
            glVertex2i(j.button[1].r.right + w, j.button[1].r.bot - w);
            glVertex2i(j.button[1].r.left - w, j.button[1].r.bot - w);
        glEnd();
        glLineWidth(1);
    }
    if (j.button[1].down) {
        glColor3fv(j.button[1].dcolor);
    }
    else {
        glColor3fv(j.button[1].color);
    }
    glBegin(GL_QUADS);
    glVertex2i(j.button[1].r.left, j.button[1].r.bot);
    glVertex2i(j.button[1].r.left, j.button[1].r.top);
    glVertex2i(j.button[1].r.right, j.button[1].r.top);
    glVertex2i(j.button[1].r.right, j.button[1].r.bot);
    glEnd();
    r.left = j.button[1].r.centerx;
    r.bot = j.button[1].r.centery - 8;
    r.center = 1;
    if (j.button[1].down) {
        ggprint16(&r, 0, j.button[1].text_color, "Pressed!");
    }
    else {
        ggprint16(&r, 0, j.button[1].text_color, j.button[1].text);
    }

    // Edit names and profile pictures onto credits screen.
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
    // glColor3f(1.0, 1.0, 1.0);
    glColor4f(0.0, 0.0, 0.0, 0.5);
    glBegin(GL_QUADS);
    glVertex2i(0, 0);
    glVertex2i(0, yres);
    glVertex2i(xres, yres);
    glVertex2i(xres, 0);
    glEnd();
    glDisable(GL_BLEND);
    r.left = xres / 2;
    r.bot = yres / 2;
    r.center = 50;
    ggprint16(&r, 50, 0xffffffff, "Paused");
}
