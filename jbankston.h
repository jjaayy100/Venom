/// jayden include file
//

typedef struct t_hawk{
        int status;
        int pos[2];
} Hawk;


extern void youlost(int lost);
extern void showyoulost(int xres, int yres);
extern void cratehawks(Hawk *h, int cent[]);
extern void hawkgameover(int snakelength ,int pos[80*80][2],
       	int *gameover, Hawk *h);
extern int initHawk();
extern int hawkphysics(int head[]);
extern void getGridCenter(const int i, const int j, int cent[2]);
extern void cleanhawk(Hawk *h);
