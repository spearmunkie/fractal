#include<SDL.h>

SDL_Surface* screen;
struct RGB
{
    int r;
    int g;
    int b;
};

void pset(int x,int y,const RGB& color)
{
    Uint32 colorSDL = SDL_MapRGB(screen->format, color.r, color.g, color.b);
    Uint32* bufp;
    bufp = (Uint32*)screen->pixels + y * screen->pitch / 4 + x;
    *bufp = colorSDL;
}

int main( int argc, char* args[] )
{
    SDL_Event event;

    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
        return 1;
    screen = SDL_SetVideoMode(670, 400, 32, SDL_SWSURFACE );
    if( screen == NULL )
        return 1;
    SDL_WM_SetCaption( "OMG a mandlebrot!!!!111!!eleven!!!", NULL );
    RGB col1,col2,tmp;
    col1.r=255;
    col1.b=255;
    col1.g=255;

    col2.r=0;
    col2.b=255;
    col2.g=0;

    tmp=col1;
    double c1, c2, x, y, r, x1, y1;
    int maxIter=5,iter=0;
    for(int i=0;i<670;i++)
    {
        c1 = -2 + 4 * (i+1 - 100) / 700;
        for(int j=0;j<400;j++)
        {

            c2 = 2 - 4 * (j+1 + 150) / 700;
            tmp=col1;
            x = c1;
            y = c2;
            for (int n=1;n<=30;n++)
            {
                x1 = x * x - y * y + c1;
                y1 = 2 * x * y + c2;
                r = (x1 * x1 + y1 * y1);
                if (r >4.0)
                {
                    tmp=col2;
                    break;
                }
                x = x1;
                y = y1;
            }
            pset(i,j,tmp);
        }
    }
    if( SDL_Flip( screen ) == -1 )
                return 1;
    SDL_Delay(2000);
}
