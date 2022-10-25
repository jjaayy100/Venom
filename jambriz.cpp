//Jorge Ambriz
//Source functions

#include <iostream>
#include <GL/glx.h>
#include <cstring>
#include <stdlib.h>
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
    /*
    //Render snake1.jpg on top of white rendered screen
    //  Using the tutorial from https://open.gl/textures
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
    int width = xres;
    int height = yres;
    unsigned char* image = SOIL_load_image("snake1.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);
    GLuint tex;
    //int image;
    //GLuint texture = ("/home/jorge/downloads/snake1.jpg");
    int xcent = xres / 2;
    int ycent = yres / 2;
    //int w = 500;
    glColor3f(0.5f, 0.5f, 0.5f);
	glBindTexture(GL_TEXTURE_2D, tex);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(0,         0);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(0,     ycent);
		glTexCoord2f(1.0f, 1.0f); glVertex2i(xcent, ycent);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(xcent,     0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
    */

    // older render code
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
