extern unsigned int check_startup(unsigned int s); 

extern void show_startup(int x, int y);    

unsigned int check_map(unsigned int k);

void resize_map(int x, int y, int boarddim, int griddim);

void dget_textures(GLuint BackggroundTexture);

void get_snake_pos(int length, int snake_pos[][2]);