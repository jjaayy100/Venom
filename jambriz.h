//Jorge's header file
//
#include </usr/include/AL/alut.h>

#define MAXBUTTONS 10
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

extern int timer(int xres, int yres);
extern Button credits_screen_box();
extern Button donec_box();
extern void draw_credits_box();
extern int check_credits_box(XEvent *e);
extern void get_sounds(ALuint alSourceDrip, ALuint alSourceTick, ALuint alSourceBird, ALuint alSourceMCS, ALuint alsourceSGM);
extern void get_textures(GLuint BackgroundTexture, GLuint BackgroundTexture2, GLuint BackgroundTexture3, GLuint BackgroundTexture4, GLuint BackgroundTexture5);
extern void display_background(int xres, int yres,int background_num);
extern unsigned int set_credits_state(unsigned int credits);
extern void show_credits_screen(int xres, int yres, GLuint snakectexture);
extern void get_class_data(int gameover, int timestat, int reset, int pause, int credits);
extern unsigned int pauseGame(unsigned int p);
extern void show_pauseScreen(int xres, int yres);
extern int changebackground(int background);