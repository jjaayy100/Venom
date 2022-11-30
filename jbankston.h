/// jayden include file
//

typedef struct t_hawk{
        int status;
        int pos[2];
} Hawk;


extern void youlost(int lost);
extern void showyoulost(int xres, int yres);
extern void cratehawks(int xres, int yres, Hawk *h, int cent[]);
extern int initHawk();
extern int hawkphysics(int head[]);
extern void getGridCenter(const int i, const int j, int cent[2]);
