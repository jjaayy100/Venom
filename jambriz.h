//Jorge's header file
//

extern int timer(int xres, int yres);
extern void get_textures(GLuint BackgroundTexture, GLuint BackgroundTexture2, GLuint BackgroundTexture3, GLuint BackgroundTexture4, GLuint BackgroundTexture5);
extern void display_background(int xres, int yres,int background_num);
extern unsigned int set_credits_state(unsigned int credits);
extern void show_credits_screen(int xres, int yres, GLuint snakectexture);
extern void get_class_data(int gameover, int timestat, int reset, int pause);
extern unsigned int pauseGame(unsigned int p);
extern void show_pauseScreen(int xres, int yres);
extern int changebackground(int background);