//modified by: Yeana Bond
//modified by: Jayden Bankston
//modified by: Darien Ware
//modified by: Jorge Ambriz
//Notes from Yeana: 
//program: snake.cpp
//author:  Gordon Griesel
//purpose: Simple snake game
//cs335 Spring 2014
//cmps3350 Spring 2018
//
//
//notes:
//This may be used as the starting point for a class project.
//Students should add the following components:
//
//A minor bug was left in the program for demonstration.
//
//These items could be used to generate your requirements phase.
//
// . Introduction page
// . Title page
// . Credits page
// . Main menu
// . Snake texture
// . Rat texture
// . Levels
// . Changes in difficulty/speed
// . Scoring
// . Save high scores
// . Board texture
// . Sound
// . Special effects
// . Mouse dragging
// . Win and lose indication
// . Additional features
//
using namespace std;
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <X11/Xlib.h>
//#include <X11/Xutil.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "log.h"
//#include "ppm.h"
#include "fonts.h"
#include "jambriz.h"
#include "jbankston.h"
#include "ybond.h"
#include "dware.h"


#define USE_OPENAL_SOUND
#ifdef USE_OPENAL_SOUND
#include </usr/include/AL/alut.h>
#endif //USE_OPENAL_SOUND

//macros
#define rnd() (double)rand()/(double)RAND_MAX

#define DIRECTION_DOWN  0
#define DIRECTION_LEFT  1
#define DIRECTION_UP    2
#define DIRECTION_RIGHT 3
//
#define MAX_GRID 80
typedef struct t_grid {
	int status;
	float color[4];
} Grid;
//
typedef struct t_snake {
	int status;
	int length;
	int pos[MAX_GRID*MAX_GRID][2];
	int direction;
	double timer;
	double delay;
} Snake;
//
typedef struct t_rat {
	int status;
	int pos[2];
} Rat;
//jayden added
//typedef struct t_hawk{
//        int status;
//	int pos[2]; 
//} Hawk; 
//

class Image {
public:
	int width, height;
	unsigned char *data;
	~Image() { delete [] data; }
	Image(const char *fname) {
		if (fname[0] == '\0')
			return;
		//printf("fname **%s**\n", fname);
		int ppmFlag = 0;
		char name[40];
		strcpy(name, fname);
		int slen = strlen(name);
		char ppmname[80];
		if (strncmp(name+(slen-4), ".ppm", 4) == 0)
			ppmFlag = 1;
		if (ppmFlag) {
			strcpy(ppmname, name);
		} else {
			name[slen-4] = '\0';
			//printf("name **%s**\n", name);
			sprintf(ppmname,"%s.ppm", name);
			//printf("ppmname **%s**\n", ppmname);
			char ts[100];
			//system("convert img.jpg img.ppm");
			sprintf(ts, "convert %s %s", fname, ppmname);
			system(ts);
		}
		//sprintf(ts, "%s", name);
		FILE *fpi = fopen(ppmname, "r");
		if (fpi) {
			char line[200];
			fgets(line, 200, fpi);
			fgets(line, 200, fpi);
			//skip comments and blank lines
			while (line[0] == '#' || strlen(line) < 2)
				fgets(line, 200, fpi);
			sscanf(line, "%i %i", &width, &height);
			fgets(line, 200, fpi);
			//get pixel data
			int n = width * height * 3;			
			data = new unsigned char[n];			
			for (int i=0; i<n; i++)
				data[i] = fgetc(fpi);
			fclose(fpi);
		} else {
			printf("ERROR opening image: %s\n",ppmname);
			exit(0);
		}
		if (!ppmFlag)
			unlink(ppmname);
	}
};
Image img[6] = {"./images/snake1.jpg",
				"./images/grandmother_flower.jpg",
				"./images/pattern_sand.jpg",
				"./images/roof_distance.jpg",
				"./images/exotic_plants_side.jpg",
				"./images/stream_horizontal.jpg"};

struct Textures {
	Image *background;
	Image *background2;
	Image *background3;
	Image *background4;
	Image *background5;
	Image *snakecimage;
	GLuint BackgroundTexture;
	GLuint BackgroundTexture2;
	GLuint BackgroundTexture3;
	GLuint BackgroundTexture4;
	GLuint BackgroundTexture5;
	GLuint snakectexture;
	Textures() {
		background=NULL;
		background2=NULL;
		background3=NULL;
		background4=NULL;
		background5=NULL;
		snakecimage=NULL;
	}
}t;

struct Global {
	int xres, yres;
	Grid grid[MAX_GRID][MAX_GRID];
	Snake snake;
	Rat rat;
	Hawk hawk;
	int gridDim;
	int boardDim;
	int gameover;
	int hawks;
	int winner;
	int gamestart;
	unsigned int setbackground;
	unsigned int pause;
	unsigned int help;
	unsigned  changeSnakeColor;
	unsigned int startup;
	unsigned int mapsize;
	unsigned int credits;
	unsigned int timestat;
	unsigned int reset;
	Button button[MAXBUTTONS];
	int nbuttons;
	//
	ALuint alBufferDrip, alBufferTick, alBufferBird, alBufferMCS, alBufferSGM;
    ALuint alSourceDrip, alSourceTick, alSourceBird, alSourceMCS, alSourceSGM;
	Global() {
		xres = 800;
		yres = 600;
		gridDim = 40;
		gameover = 0;
		hawks = 0; 
		winner = 0;
		credits = 0;
		nbuttons = 0;
		reset = 0;
		setbackground = 1;
		pause = 0;
		help = 0;
		changeSnakeColor = 0;
		//initialize startup screen as on
		startup = 1;
		mapsize = 0;

	}
} g;

class X11_wrapper {
private:
	Display *dpy;
	Window win;
public:
	X11_wrapper() {
		GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
		//GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
		XSetWindowAttributes swa;
		setupScreenRes(g.xres, g.yres);
		dpy = XOpenDisplay(NULL);
		if (dpy == NULL) {
			printf("\n\tcannot connect to X server\n\n");
			exit(EXIT_FAILURE);
		}
		Window root = DefaultRootWindow(dpy);
		XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
		if (vi == NULL) {
			printf("\n\tno appropriate visual found\n\n");
			exit(EXIT_FAILURE);
		} 
		Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
		swa.colormap = cmap;
		swa.event_mask = ExposureMask |
							KeyPressMask |
							KeyReleaseMask |
							ButtonPressMask |
							ButtonReleaseMask |
							PointerMotionMask |
							StructureNotifyMask |
							SubstructureNotifyMask;
		win = XCreateWindow(dpy, root, 0, 0, g.xres, g.yres, 0,	vi->depth,
						InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
		GLXContext glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
		glXMakeCurrent(dpy, win, glc);
		setTitle();
	}
	~X11_wrapper() {
		XDestroyWindow(dpy, win);
		XCloseDisplay(dpy);
	}
	void setTitle() {
		//Set the window title bar.
		XMapWindow(dpy, win);
		//Changed to better reflect our personal game.
		XStoreName(dpy, win, "Venom");
	}
	void setupScreenRes(const int w, const int h) {
		g.xres = w;
		g.yres = h;
	}
	void reshapeWindow(int width, int height) {
		//window has been resized.
		setupScreenRes(width, height);
		//
		glViewport(0, 0, (GLint)width, (GLint)height);
		glMatrixMode(GL_PROJECTION); glLoadIdentity();
		glMatrixMode(GL_MODELVIEW); glLoadIdentity();
		glOrtho(0, g.xres, 0, g.yres, -1, 1);
		setTitle();
	}
	void checkResize(XEvent *e) {
		//The ConfigureNotify is sent by the server if the window is resized.
		if (e->type != ConfigureNotify)
			return;
		XConfigureEvent xce = e->xconfigure;

		if (xce.width != g.xres || xce.height != g.yres) {
			//Window size did change.
			reshapeWindow(xce.width, xce.height);
		}
	}
	bool getXPending() {
		return XPending(dpy);
	}
	XEvent getXNextEvent() {
		XEvent e;
		XNextEvent(dpy, &e);
		return e;
	}
	void swapBuffers() {
		glXSwapBuffers(dpy, win);
	}
} x11;

//function prototypes
void initOpengl(void);
int checkMouse(XEvent *e);
int checkKeys(XEvent *e);
void init();
void initSounds(void);
void physics(void);
void render(void);
void getGridCenter(const int i, const int j, int cent[2]);
#ifdef USE_OPENAL_SOUND
void initSound();
void cleanupSound();
void playSound(ALuint source);
#endif //USE_OPENAL_SOUND


//-----------------------------------------------------------------------------
//Setup timers
const double physicsRate = 1.0 / 60.0;
const double oobillion = 1.0 / 1e9;
struct timespec timeStart, timeCurrent;
struct timespec timePause;
double physicsCountdown = 0.0;
double timeSpan = 0.0;
double timeDiff(struct timespec *start, struct timespec *end) {
	return (double)(end->tv_sec - start->tv_sec ) +
			(double)(end->tv_nsec - start->tv_nsec) * oobillion;
}
void timeCopy(struct timespec *dest, struct timespec *source) {
	memcpy(dest, source, sizeof(struct timespec));
}
//-----------------------------------------------------------------------------


int main(int argc, char *argv[])
{
	if (argc) {}
	if (argv[0]) {}
	logOpen();
	initOpengl();
	init();
	initialize_fonts();
	initSound();
	srand((unsigned int)time(NULL));
	clock_gettime(CLOCK_REALTIME, &timePause);
	clock_gettime(CLOCK_REALTIME, &timeStart);
	playSound(g.alSourceBird);
	int done = 0;
	while (!done) {
		while (x11.getXPending()) {
			XEvent e = x11.getXNextEvent();
			x11.checkResize(&e);
			done = checkMouse(&e);
			done = checkKeys(&e);
		}
		//
		//Below is a process to apply physics at a consistent rate.
		//1. Get the time right now.
		clock_gettime(CLOCK_REALTIME, &timeCurrent);
		//2. How long since we were here last?
		timeSpan = timeDiff(&timeStart, &timeCurrent);
		//3. Save the current time as our new starting time.
		timeCopy(&timeStart, &timeCurrent);
		//4. Add time-span to our countdown amount.
		physicsCountdown += timeSpan;
		//5. Has countdown gone beyond our physics rate? 
		//       if yes,
		//           In a loop...
		//              Apply physics
		//              Reducing countdown by physics-rate.
		//              Break when countdown < physics-rate.
		//       if no,
		//           Apply no physics this frame.
		while(physicsCountdown >= physicsRate) {
			//6. Apply physics
			physics();
			//7. Reduce the countdown by our physics-rate
			physicsCountdown -= physicsRate;
		}
		//Always render every frame.
		render();
		x11.swapBuffers();
		//Send data to jambriz.cpp file for Jlobal(Still in testing)
		get_class_data(g.gameover, g.timestat, g.reset, g.pause, g.credits);
		if(g.reset) {
			g.reset = 0;
			g.changeSnakeColor = 0;
			g.help = 0;
		}
	}
	cleanupSound();
	cleanup_fonts();
	logClose();
	return 0;
}

void initSound()
{
	#ifdef USE_OPENAL_SOUND
	alutInit(0, NULL);
	if (alGetError() != AL_NO_ERROR) {
		printf("ERROR: alutInit()\n");
		return;
	}
	//Clear error state.
	alGetError();
	//g.background3 = &img[3];
	//Setup the listener.
	//Forward and up vectors are used.
	float vec[6] = {0.0f,0.0f,1.0f, 0.0f,1.0f,0.0f};
	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
	alListenerfv(AL_ORIENTATION, vec);
	alListenerf(AL_GAIN, 1.0f);
	//
	//Buffer holds the sound information.
	g.alBufferDrip = alutCreateBufferFromFile("./sounds/drip.wav");
	g.alBufferTick = alutCreateBufferFromFile("./sounds/tick.wav");
	g.alBufferBird = alutCreateBufferFromFile("./sounds/bird.wav");
	g.alBufferMCS = alutCreateBufferFromFile("./sounds/music_for_credits_screen.wav");
    g.alBufferSGM = alutCreateBufferFromFile("./sounds/start_game.wav");

	//Source refers to the sound.
	//Generate a source, and store it in a buffer.
	alGenSources(1, &g.alSourceDrip);
	alSourcei(g.alSourceDrip, AL_BUFFER, g.alBufferDrip);
	//Set volume and pitch to normal, no looping of sound.
	alSourcef(g.alSourceDrip, AL_GAIN, 1.0f);
	alSourcef(g.alSourceDrip, AL_PITCH, 1.0f);
	alSourcei(g.alSourceDrip, AL_LOOPING, AL_FALSE);
	if (alGetError() != AL_NO_ERROR) {
		printf("ERROR: setting source\n");
		return;
	}
	//Generate a source, and store it in a buffer.
	alGenSources(1, &g.alSourceTick);
	alSourcei(g.alSourceTick, AL_BUFFER, g.alBufferTick);
	//Set volume and pitch to normal, no looping of sound.
	alSourcef(g.alSourceTick, AL_GAIN, 1.0f);
	alSourcef(g.alSourceTick, AL_PITCH, 1.0f);
	alSourcei(g.alSourceTick, AL_LOOPING, AL_FALSE);
	if (alGetError() != AL_NO_ERROR) {
		printf("ERROR: setting source\n");
		return;
	}
	//Generate a source, and store it in a buffer.
	alGenSources(1, &g.alSourceBird);
	alSourcei(g.alSourceBird, AL_BUFFER, g.alBufferBird);
	//Set volume and pitch to normal, no looping of sound.
	alSourcef(g.alSourceBird, AL_GAIN, 1.0f);
	alSourcef(g.alSourceBird, AL_PITCH, 1.0f);
	alSourcei(g.alSourceBird, AL_LOOPING, AL_TRUE);
	if (alGetError() != AL_NO_ERROR) {
		printf("ERROR: setting source\n");
		return;
	}
    //Generate a source, and store it in a buffer.
    alGenSources(1, &g.alSourceMCS);
    alSourcei(g.alSourceMCS, AL_BUFFER, g.alBufferMCS);
    //Set volume and pitch to normal, no looping of sound.
    alSourcef(g.alSourceMCS, AL_GAIN, 1.0f);
    alSourcef(g.alSourceMCS, AL_PITCH, 1.0f);
    alSourcei(g.alSourceMCS, AL_LOOPING, AL_TRUE);
    if (alGetError() != AL_NO_ERROR) {
        printf("ERROR: setting source\n");
        return;
    }
    //Generate a source, and store it in a buffer.
    alGenSources(1, &g.alSourceSGM);
    alSourcei(g.alSourceSGM, AL_BUFFER, g.alBufferSGM);
    //Set volume and pitch to normal, no looping of sound.
    alSourcef(g.alSourceSGM, AL_GAIN, 1.0f);
    alSourcef(g.alSourceSGM, AL_PITCH, 1.0f);
    alSourcei(g.alSourceSGM, AL_LOOPING, AL_FALSE);
    if (alGetError() != AL_NO_ERROR) {
        printf("ERROR: setting source\n");
        return;
    }
    get_sounds(g.alSourceDrip, g.alSourceTick, g.alSourceBird, g.alSourceMCS, g.alSourceSGM);

	#endif //USE_OPENAL_SOUND
}

void cleanupSound()
{
	#ifdef USE_OPENAL_SOUND
	//First delete the source.
	alDeleteSources(1, &g.alSourceDrip);
	alDeleteSources(1, &g.alSourceTick);
	alDeleteSources(1, &g.alSourceBird);
	alDeleteSources(1, &g.alSourceMCS);
	alDeleteSources(1, &g.alSourceSGM);
	
	//Delete the buffer.
	alDeleteBuffers(1, &g.alBufferDrip);
	alDeleteBuffers(1, &g.alBufferTick);
	alDeleteBuffers(1, &g.alBufferBird);
	alDeleteBuffers(1, &g.alBufferMCS);
	alDeleteBuffers(1, &g.alBufferSGM);
	//Close out OpenAL itself.
	//Get active context.
	ALCcontext *Context = alcGetCurrentContext();
	//Get device for active context.
	ALCdevice *Device = alcGetContextsDevice(Context);
	//Disable context.
	alcMakeContextCurrent(NULL);
	//Release context(s).
	alcDestroyContext(Context);
	//Close device.
	alcCloseDevice(Device);
	#endif //USE_OPENAL_SOUND
}

void playSound(ALuint source)
{
	#ifdef USE_OPENAL_SOUND
	alSourcePlay(source);
	#endif //USE_OPENAL_SOUND
}

void initOpengl(void)
{
	//OpenGL initialization
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_COLOR_MATERIAL);
	//
	//choose one of these
	//glShadeModel(GL_FLAT);
	glShadeModel(GL_SMOOTH);
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, 0);
	//
	glEnable(GL_TEXTURE_2D);
	//marble_texture = loadBMP("marble.bmp");
	glBindTexture(GL_TEXTURE_2D, 0);
	//for snaketexture
	glBindTexture(GL_TEXTURE_2D, 1);
	//
	//load the image file into a ppm structure.
	//
	//g.marbleImage = ppm6GetImage("./images/marble.ppm");
	t.snakecimage = &img[0];
	t.background = &img[1];
	t.background2 = &img[2];
	t.background3 = &img[3];
	t.background4 = &img[4];
	t.background5 = &img[5];
	
	//
	//create opengl texture elements
	//Marble Background
	glGenTextures(1, &t.BackgroundTexture);
	glBindTexture(GL_TEXTURE_2D, t.BackgroundTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	             t.background->width, t.background->height,
	             0, GL_RGB, GL_UNSIGNED_BYTE, t.background->data);
	//Sand pattern background
	glGenTextures(1, &t.BackgroundTexture2);
	glBindTexture(GL_TEXTURE_2D, t.BackgroundTexture2);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	             t.background2->width, t.background2->height,
	             0, GL_RGB, GL_UNSIGNED_BYTE, t.background2->data);
	//Roof background
	glGenTextures(1, &t.BackgroundTexture3);
	glBindTexture(GL_TEXTURE_2D, t.BackgroundTexture3);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	             t.background3->width, t.background3->height,
	             0, GL_RGB, GL_UNSIGNED_BYTE, t.background3->data);
	//Exotic plants background
	glGenTextures(1, &t.BackgroundTexture4);
	glBindTexture(GL_TEXTURE_2D, t.BackgroundTexture4);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	             t.background4->width, t.background4->height,
	             0, GL_RGB, GL_UNSIGNED_BYTE, t.background4->data);
	//Horizontal stream background
	glGenTextures(1, &t.BackgroundTexture5);
	glBindTexture(GL_TEXTURE_2D, t.BackgroundTexture5);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	             t.background5->width, t.background5->height,
	             0, GL_RGB, GL_UNSIGNED_BYTE, t.background5->data);
	//For Credits screen
	glGenTextures(1, &t.snakectexture);
	glBindTexture(GL_TEXTURE_2D, t.snakectexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	             t.snakecimage->width, t.snakecimage->height,
	             0, GL_RGB, GL_UNSIGNED_BYTE, t.snakecimage->data);
	get_textures(t.BackgroundTexture, t.BackgroundTexture2, t.BackgroundTexture3, t.BackgroundTexture4, t.BackgroundTexture5);
}

void initSnake()
{
	playSound(g.alSourceSGM);
	int i;
	g.snake.status = 1;
	g.snake.delay = .15;
	g.snake.length = rand() % 4 + 3;
	for (i=0; i<g.snake.length; i++) {
		g.snake.pos[i][0] = 2;
		g.snake.pos[i][1] = 2;
	}
	g.snake.direction = DIRECTION_RIGHT;
	//snake.timer = glfwGetTime() + 0.5;
}

void initRat()
{
	g.rat.status = 1;
	g.rat.pos[0] = 25;
	g.rat.pos[1] = 2;
}

void init()
{
	g.boardDim = g.gridDim * 10;
	//
	initSnake();
	initRat();
	//jayden added
	//extern void initHawk(Hawk *h);
	//initHawk(&g.hawk);
	//
	//initialize buttons...
	g.nbuttons=0;
	//size and position
	g.button[g.nbuttons].r.width = 140;
	g.button[g.nbuttons].r.height = 60;
	g.button[g.nbuttons].r.left = 20;
	g.button[g.nbuttons].r.bot = 320;
	g.button[g.nbuttons].r.right =
	   g.button[g.nbuttons].r.left + g.button[g.nbuttons].r.width;
	g.button[g.nbuttons].r.top =
	   g.button[g.nbuttons].r.bot + g.button[g.nbuttons].r.height;
	g.button[g.nbuttons].r.centerx =
	   (g.button[g.nbuttons].r.left + g.button[g.nbuttons].r.right) / 2;
	g.button[g.nbuttons].r.centery =
	   (g.button[g.nbuttons].r.bot + g.button[g.nbuttons].r.top) / 2;
	strcpy(g.button[g.nbuttons].text, "Reset");
	g.button[g.nbuttons].down = 0;
	g.button[g.nbuttons].click = 0;
	g.button[g.nbuttons].color[0] = 0.0f;
	g.button[g.nbuttons].color[1] = 0.4f;
	g.button[g.nbuttons].color[2] = 0.0f; //7
	g.button[g.nbuttons].dcolor[0] = g.button[g.nbuttons].color[0] * 0.5f;
	g.button[g.nbuttons].dcolor[1] = g.button[g.nbuttons].color[1] * 0.5f;
	g.button[g.nbuttons].dcolor[2] = g.button[g.nbuttons].color[2] * 0.5f;
	g.button[g.nbuttons].text_color = 0x00ffffff;
	g.nbuttons++;
	g.button[g.nbuttons].r.width = 140;
	g.button[g.nbuttons].r.height = 60;
	g.button[g.nbuttons].r.left = 20;
	g.button[g.nbuttons].r.bot = 210;
	g.button[g.nbuttons].r.right =
	   g.button[g.nbuttons].r.left + g.button[g.nbuttons].r.width;
	g.button[g.nbuttons].r.top = g.button[g.nbuttons].r.bot +
	   g.button[g.nbuttons].r.height;
	g.button[g.nbuttons].r.centerx = (g.button[g.nbuttons].r.left +
	   g.button[g.nbuttons].r.right) / 2;
	g.button[g.nbuttons].r.centery = (g.button[g.nbuttons].r.bot +
	   g.button[g.nbuttons].r.top) / 2;
	strcpy(g.button[g.nbuttons].text, "Quit");
	g.button[g.nbuttons].down = 0;
	g.button[g.nbuttons].click = 0;
	g.button[g.nbuttons].color[0] = 0.0f;
	g.button[g.nbuttons].color[1] = 0.4f;
	g.button[g.nbuttons].color[2] = 0.0f;
	g.button[g.nbuttons].dcolor[0] = g.button[g.nbuttons].color[0] * 0.5f;
	g.button[g.nbuttons].dcolor[1] = g.button[g.nbuttons].color[1] * 0.5f;
	g.button[g.nbuttons].dcolor[2] = g.button[g.nbuttons].color[2] * 0.5f;
	g.button[g.nbuttons].text_color = 0x00ffffff;
	g.nbuttons++;
	//Credits Screen Button
	g.button[3] = credits_screen_box();
	g.nbuttons++;
	g.button[4] = donec_box();
	g.nbuttons++;
}

void resetGame()
{
	initSnake();
	initRat();
	cleanhawk(&g.hawk); 
	g.gameover  = 0;
	g.hawks     = 0; 
	g.winner    = 0;
	g.changeSnakeColor = 0;
	g.help = 0;
	g.reset = 1;
}

//================================
//Yeana added an extern function:
//===============================
extern int show_my_name();
extern float change_snake_color();
//================================
//Darien added an extern function:
//================================
extern int greeting();
//=================================
//Jorge added an extern function:
//=================================
extern int jhello();
//=================================
//Jayden added an extern function:
//=================================
extern int Money();
extern int youlost(); 

int checkKeys(XEvent *e)
{
	static int shift=0;
	if (e->type != KeyRelease && e->type != KeyPress)
		return 0;
	int key = (XLookupKeysym(&e->xkey, 0) & 0x0000ffff);
	if (e->type == KeyRelease) {
		if (key == XK_Shift_L || key == XK_Shift_R)
			shift=0;
		return 0;
	}
	if (key == XK_Shift_L || key == XK_Shift_R) {
		shift=1;
		return 0;
	}
	(void)shift;
	switch (key) {
		case XK_r:
			resetGame();
			break;
		case XK_Escape:
			cleanupSound();
			exit(0);
			break;
		case XK_y:
			show_my_name();
			break;
		case XK_h:
		// My name (Yeana) and a number will show
			//show_my_name();
			// help screen state varialbe 
			g.help = help_screen(g.help);
			break;
		case XK_k:
            // To change the color of the snake
            g.changeSnakeColor++;
            break;

		case XK_s:
			g.startup = check_startup(g.startup);
			break;
		case XK_z:
			g.mapsize = check_map(g.mapsize);
			break;
		case XK_d:
			greeting();
			break;
		case XK_v:
		        g.gameover = 1;
		        showyoulost(g.xres,g.yres); 	
			break;
		case XK_e:
			g.hawks = 1;
			break;
		case XK_c:
			g.credits = set_credits_state(g.credits);
			break;
		case XK_t:
			g.timestat = g.timestat ^ 1;
			break;
		case XK_b:
			g.setbackground = changebackground(g.setbackground);
			break;
		case XK_j:
			Money();
			break;
		case XK_p:
			g.pause = pauseGame(g.pause);
			break;
		case XK_equal:
			g.snake.delay *= 0.9;
			if (g.snake.delay < 0.001)
				g.snake.delay = 0.001;
			break;
		case XK_minus:
			g.snake.delay *= (1.0 / 0.9);
			break;
		case XK_Left:
			g.snake.direction = DIRECTION_LEFT;
			break;
		case XK_Right:
			g.snake.direction = DIRECTION_RIGHT;
			break;
		case XK_Up:
			g.snake.direction = DIRECTION_UP;
			break;
		case XK_Down:
			g.snake.direction = DIRECTION_DOWN;
			break;
	}
	return 0;
}

int checkMouse(XEvent *e)
{
	static int savex = 0;
	static int savey = 0;
	int i,x,y;
	int lbutton=0;
	int rbutton=0;
	//
	if (e->type == ButtonRelease)
		return 0;
	if (e->type == ButtonPress) {
		if (e->xbutton.button==1) {
			//Left button is down
			lbutton=1;
		}
		if (e->xbutton.button==3) {
			//Right button is down
			rbutton=1;
			if (rbutton){}
		}
	}
	x = e->xbutton.x;
	y = e->xbutton.y;
	y = g.yres - y;
	if (savex != e->xbutton.x || savey != e->xbutton.y) {
		//Mouse moved
		savex = e->xbutton.x;
		savey = e->xbutton.y;
	}
	for (i=0; i<g.nbuttons; i++) {
		g.button[i].over=0;
		if (x >= g.button[i].r.left &&
			x <= g.button[i].r.right &&
			y >= g.button[i].r.bot &&
			y <= g.button[i].r.top) {
			g.button[i].over=1;
			if (g.button[i].over) {
				if (lbutton) {
					switch (i) {
						case 0:
							resetGame();
							break;
						case 1:
							printf("Quit was clicked!\n");
							cleanupSound();
							exit(0);
							break;
						case 2:
							g.credits = set_credits_state(g.credits);
							break;
						case 3:
							g.credits = set_credits_state(g.credits);
							break;
					}
				}
			}
		}
	}
	check_credits_box(e);
	return 0;
}

void getGridCenter(const int i, const int j, int cent[2])
{
	//This function can be optimized, and made more generic.
	int b2 = g.boardDim/2;
	int screenCenter[2] = {g.xres/2, g.yres/2};
	int s0 = screenCenter[0];
	int s1 = screenCenter[1];
	int bq;
	//quad upper-left corner
	int quad[2];
	//bq is the width of one grid section
	bq = (g.boardDim / g.gridDim);
	//-------------------------------------
	//because y dimension is bottom-to-top in OpenGL.
	int i1 = g.gridDim - i - 1;
	quad[0] = s0-b2;
	quad[1] = s1-b2;
	cent[0] = quad[0] + bq/2;
	cent[1] = quad[1] + bq/2;
	cent[0] += (bq * j);
	cent[1] += (bq * i1);
}

void physics(void)
{
	while(g.startup || g.pause || g.credits || g.help) {
		return;
	}
	int i;
	if (g.gameover)
	{
	    youlost(g.gameover);
	    return;
	}
	//
	//
	//Is it time to move the snake?
	static struct timespec snakeTime;
	static int firsttime=1;
	if (firsttime) {
		firsttime=0;
		clock_gettime(CLOCK_REALTIME, &snakeTime);
	}
	struct timespec tt;
	clock_gettime(CLOCK_REALTIME, &tt);
	double timeSpan = timeDiff(&snakeTime, &tt);
	if (timeSpan < g.snake.delay)
		return;
	timeCopy(&snakeTime, &tt);
	//
	playSound(g.alSourceDrip);
	//move the snake segments...
	int headpos[2];
	int newpos[2];
	int oldpos[2];
	//save the head position.
	headpos[0] = g.snake.pos[0][0];
	headpos[1] = g.snake.pos[0][1];
	//snake.direction:
	//0=down
	//1=left
	//2=up
	//3=right
	switch (g.snake.direction) {
		case DIRECTION_DOWN:  g.snake.pos[0][1] += 1; break;
		case DIRECTION_LEFT:  g.snake.pos[0][0] -= 1; break;
		case DIRECTION_UP:    g.snake.pos[0][1] -= 1; break;
		case DIRECTION_RIGHT: g.snake.pos[0][0] += 1; break;
	}
	//check for snake off board...
	if (g.snake.pos[0][0] < 0 ||
		g.snake.pos[0][0] > g.gridDim-1 ||
		g.snake.pos[0][1] < 0 ||
		g.snake.pos[0][1] > g.gridDim-1) {
		g.gameover=1;
		return;
	}
	//check for snake crossing itself...
	for (i=1; i<g.snake.length; i++) {
		if (g.snake.pos[i][0] == g.snake.pos[0][0] &&
			g.snake.pos[i][1] == g.snake.pos[0][1]) {
			g.gameover=1;
			return;
		}
	}
	//
	hawkgameover(g.snake.length, g.snake.pos, &g.gameover, &g.hawk);
	
    //
	newpos[0] = headpos[0];
	newpos[1] = headpos[1];
	for (i=1; i<g.snake.length; i++) {
		oldpos[0] = g.snake.pos[i][0];
		oldpos[1] = g.snake.pos[i][1];
		if (g.snake.pos[i][0] == newpos[0] &&
			g.snake.pos[i][1] == newpos[1])
			break;
		g.snake.pos[i][0] = newpos[0];
		g.snake.pos[i][1] = newpos[1];
		newpos[0] = oldpos[0];
		newpos[1] = oldpos[1];
	}
	//did the snake eat the rat???
	if (headpos[0] == g.rat.pos[0] && headpos[1] == g.rat.pos[1]) {
		//yes, increase length of snake.
		playSound(g.alSourceTick);
		//put new segment at end of snake.
		Log("snake ate rat. snake.length: %i   dir: %i\n",
		                                g.snake.length,g.snake.direction);
		int addlength = rand() % 4 + 4;
		for (i=0; i<addlength; i++) {
			g.snake.pos[g.snake.length][0] = g.snake.pos[g.snake.length-1][0];
			g.snake.pos[g.snake.length][1] = g.snake.pos[g.snake.length-1][1];
			g.snake.length++;
		}
		//new position for rat...
		int collision=0;
		int ntries=0;
		while (1) {
			g.rat.pos[0] = rand() % g.gridDim;
			g.rat.pos[1] = rand() % g.gridDim;
			collision=0;
			for (i=0; i<g.snake.length; i++) {
				if (g.rat.pos[0] == g.snake.pos[i][0] &&
					g.rat.pos[1] == g.snake.pos[i][1]) {
					collision=1;
					break;
				}
			}
			if (!collision) break;
			if (++ntries > 1000000) break;
		}
		Log("new rat: %i %i\n",g.rat.pos[0],g.rat.pos[1]);
		return;
	}
	//int tmp; 
	//extern int hawkphysics(int *head[], Hawk *h);
	//tmp = hawkphysics(&headpos[2]);
	//g.gameover = tmp;
}

void render(void)
{
	int i,j;
	Rect r;

	//--------------------------------------------------------
	//This code is repeated several times in this program, so
	//it can be made more generic and cleaner with some work.
	int b2 = g.boardDim/2;
	int s0 = g.xres>>1;
	int s1 = g.yres>>1;
	//center of a grid
	int cent[2];
	//bq is the width of one grid section
	//--------------------------------------------------------
	//start the opengl stuff
	//set the viewing area on screen
	glViewport(0, 0, g.xres, g.yres);
	//clear color buffer
	glClearColor(0.1f, 0.2f, 0.3f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//init matrices
	glMatrixMode (GL_PROJECTION); glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	//this sets to 2D mode (no perspective)
	glOrtho(0, g.xres, 0, g.yres, -1, 1);
	//

	//screen background-------------------------------------
	display_background(g.xres, g.yres, g.setbackground);

	/* //old background render code
	glColor3f(0.5f, 0.5f, 0.5f);
	glBindTexture(GL_TEXTURE_2D, g.BackgroundTexture);
	//glBindTexture(GL_TEXTURE_2D, setBackgroundTexture());
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(0,      0);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(0,      g.yres);
		glTexCoord2f(1.0f, 1.0f); glVertex2i(g.xres, g.yres);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(g.xres, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	*/
	for (i=0; i<g.nbuttons; i++) {
		if (g.button[i].over) {
			int w=2;
			glColor3f(1.0f, 1.0f, 0.0f);
			//draw a highlight around button
			glLineWidth(3);
			glBegin(GL_LINE_LOOP);
				glVertex2i(g.button[i].r.left-w,  g.button[i].r.bot-w);
				glVertex2i(g.button[i].r.left-w,  g.button[i].r.top+w);
				glVertex2i(g.button[i].r.right+w, g.button[i].r.top+w);
				glVertex2i(g.button[i].r.right+w, g.button[i].r.bot-w);
				glVertex2i(g.button[i].r.left-w,  g.button[i].r.bot-w);
			glEnd();
			glLineWidth(1);
		}
		if (g.button[i].down) {
			glColor3fv(g.button[i].dcolor);
		} else {
			glColor3fv(g.button[i].color);
		}
		glBegin(GL_QUADS);
			glVertex2i(g.button[i].r.left,  g.button[i].r.bot);
			glVertex2i(g.button[i].r.left,  g.button[i].r.top);
			glVertex2i(g.button[i].r.right, g.button[i].r.top);
			glVertex2i(g.button[i].r.right, g.button[i].r.bot);
		glEnd();
		r.left = g.button[i].r.centerx;
		r.bot  = g.button[i].r.centery-8;
		r.center = 1;
		if (g.button[i].down) {
			ggprint16(&r, 0, g.button[i].text_color, "Pressed!");
		} else {
			ggprint16(&r, 0, g.button[i].text_color, g.button[i].text);
		}
	}
	draw_credits_box();
	if (g.mapsize) {
		//render the map resize
		resize_map(g.xres, g.yres, g.boardDim, g.gridDim, g.setbackground);
		for (i=0; i<g.nbuttons; i++) {
		if (g.button[i].over) {
			int w=2;
			glColor3f(1.0f, 1.0f, 0.0f);
			//draw a highlight around button
			glLineWidth(3);
			glBegin(GL_LINE_LOOP);
				glVertex2i(g.button[i].r.left-w,  g.button[i].r.bot-w);
				glVertex2i(g.button[i].r.left-w,  g.button[i].r.top+w);
				glVertex2i(g.button[i].r.right+w, g.button[i].r.top+w);
				glVertex2i(g.button[i].r.right+w, g.button[i].r.bot-w);
				glVertex2i(g.button[i].r.left-w,  g.button[i].r.bot-w);
			glEnd();
			glLineWidth(1);
		}
		if (g.button[i].down) {
			glColor3fv(g.button[i].dcolor);
		} else {
			glColor3fv(g.button[i].color);
		}
		glBegin(GL_QUADS);
			glVertex2i(g.button[i].r.left,  g.button[i].r.bot);
			glVertex2i(g.button[i].r.left,  g.button[i].r.top);
			glVertex2i(g.button[i].r.right, g.button[i].r.top);
			glVertex2i(g.button[i].r.right, g.button[i].r.bot);
		glEnd();
		r.left = g.button[i].r.centerx;
		r.bot  = g.button[i].r.centery-8;
		r.center = 1;
		if (g.button[i].down) {
			ggprint16(&r, 0, g.button[i].text_color, "Pressed!");
		} else {
			ggprint16(&r, 0, g.button[i].text_color, g.button[i].text);
		}
	}
	draw_credits_box();
	}
	else {
	//draw the main game board in middle of screen
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
	//glColor3f(0.6f, 0.5f, 0.2f);
	glColor4f(0.4, 0.6, 0.2, 0.85);
	glBegin(GL_QUADS);
		glVertex2i(s0-b2, s1-b2);
		glVertex2i(s0-b2, s1+b2);
		glVertex2i(s0+b2, s1+b2);
		glVertex2i(s0+b2, s1-b2);
	glEnd();
	glDisable(GL_BLEND);
	//
	//grid lines...
	int x0 = s0-b2;
	int x1 = s0+b2;
	int y0 = s1-b2;
	int y1 = s1+b2;
	glColor3f(0.1f, 0.1f, 0.1f);
	glBegin(GL_LINES);
	for (i=1; i<g.gridDim; i++) {
		y0 += 10;
		glVertex2i(x0,y0);
		glVertex2i(x1,y0);
	}
	x0 = s0-b2;
	y0 = s1-b2;
	y1 = s1+b2;
	for (j=1; j<g.gridDim; j++) {
		x0 += 10;
		glVertex2i(x0,y0);
		glVertex2i(x0,y1);
	}
	glEnd();
	}
	//
	#define COLORFUL_SNAKE
	//
	//draw snake...
	#ifdef COLORFUL_SNAKE
	
	float c[3]={1.0f,1.0,0.5};
	// integer works!! 
	//char count = char(g.changeSnakeColor);
	/*
	if(g.changeSnakeColor == 1) {
	    //std::cout << g.changeSnakeColor << std::endl;
        c[0] = change_snake_color_1(g.changeSnakeColor);
	    c[1] = change_snake_color_2(g.changeSnakeColor);
	    c[2] = change_snake_color_3(g.changeSnakeColor);

	}

	if(g.changeSnakeColor == 2) {
	    //std::cout << g.changeSnakeColor << std::endl;
        c[0] = change_snake_color_1(g.changeSnakeColor);
	    c[1] = change_snake_color_2(g.changeSnakeColor);
	    c[2] = change_snake_color_3(g.changeSnakeColor);


	}*/

	if (g.changeSnakeColor > 0) {

        c[0] = change_snake_color_1(g.changeSnakeColor);
	    c[1] = change_snake_color_2(g.changeSnakeColor);
	    c[2] = change_snake_color_3(g.changeSnakeColor);    
	
	}

	if(g.changeSnakeColor > 4) {
	    g.changeSnakeColor = 0;
	}


    // Yeana's experiement on changing snake color randomly
	//float val_1 = g.changeSnakeColor;
	//float val_2 = change_snake_color();
	//float val_3 = change_snake_color();
	//float c[3] = {val_1, 1 - val_2, val_3};
	float rgb[3];
	rgb[0] = -0.9 / (float)g.snake.length;
	rgb[2] = -0.45 / (float)g.snake.length;
	glColor3fv(c);
	//
	glBegin(GL_QUADS);
	for (i=0; i<g.snake.length; i++) {
		getGridCenter(g.snake.pos[i][1],g.snake.pos[i][0],cent);
		glVertex2i(cent[0]-4, cent[1]-3);
		glVertex2i(cent[0]-4, cent[1]+4);
		glVertex2i(cent[0]+3, cent[1]+4);
		glVertex2i(cent[0]+3, cent[1]-3);
		c[0] +=	rgb[0];
		c[2] +=	rgb[2];
		glColor3fv(c);
	}
	glEnd();
	#else //COLORFUL_SNAKE
	glColor3f(0.1f, 0.8f, 0.1f);
	glBegin(GL_QUADS);
	for (i=0; i<g.snake.length; i++) {
		getGridCenter(g.snake.pos[i][1],g.snake.pos[i][0],cent);
		glVertex2i(cent[0]-4, cent[1]-3);
		glVertex2i(cent[0]-4, cent[1]+4);
		glVertex2i(cent[0]+3, cent[1]+4);
		glVertex2i(cent[0]+3, cent[1]-3);
		glColor3f(0.0f, 0.6f, 0.0f);
	}
	glEnd();
	#endif //COLORFUL_SNAKE
	//
	//
	//draw rat...
	getGridCenter(g.rat.pos[1],g.rat.pos[0],cent);
	glColor3f(0.1, 0.1f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2i(cent[0]-4, cent[1]-3);
	glVertex2i(cent[0]-4, cent[1]+4);
	glVertex2i(cent[0]+3, cent[1]+4);
	glVertex2i(cent[0]+3, cent[1]-3);
	glEnd();
	//
	//
	r.left   = g.xres/2;
	r.bot    = g.yres-100;
	r.center = 1;

	//Changed to better fit out game
	ggprint16(&r, 16, 0x00ffffff, "Venom");

	//Yeana's help screen
	if (g.help) {
	    // show help screen
	    show_help_screen(g.xres, g.yres);

	    return;
	}

	// Yeana's feature 1: change the snake color 
        /*if (g.changeSnakeColor == 1.0) {

            //red -= g.changeSnakeColor;
            //green += g.changeSnakeColor;
            //blue -= g.changeSnakeColor;

            val_1 = change_snake_color();
            val_2 = change_snake_color();
            val_3 = change_snake_color();
        }*/

	//Darien's Startup Screen
	if (g.startup) {
		//startup screen will automatically be toggled
		show_startup(g.xres,g.yres);
	}

	//jayden's you lost screen
	if (g.gameover){ 
	    cleanhawk(&g.hawk);
	    //show you lost
	    showyoulost(g.xres,g.yres);
	}

	//jayden crate hawks
	if (g.hawks) { 
	    cratehawks(&g.hawk, cent);
	    extern void initHawk(Hawk *h);
            initHawk(&g.hawk);
	}

	//Jorge's credits screen
	if (g.credits) {
		//toggle credits - seperate from a menu option for now
		show_credits_screen(g.xres, g.yres, t.snakectexture);
	}
	//Jorge's Timer feature: don't want to show it if any other screen is on
	if ((g.timestat == 1) &&
		(g.gameover != 1) && 
		(g.credits != 1 ) && 
		(g.startup != 1 )) {
        timer(g.xres, g.yres);
    }
	//Pause screen
	if ((g.pause == 1)    &&
        (g.gameover != 1) &&
        (g.credits != 1)  && 
        (g.startup != 1)) {
	   	show_pauseScreen(g.xres, g.yres);
    }

}

