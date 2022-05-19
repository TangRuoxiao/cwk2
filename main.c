#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"
#include <SDL2/SDL.h>

#define CELL 40
int state[50][50];
int next[50][50];
int col = 0, row = 0;

SDL_Window *newWin(char *name)
{
    SDL_Window *win = SDL_CreateWindow(
        name,                 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        CELL * col,             
        CELL * row,             
        0                       
    );

    if (win == NULL)
    {
        printf("window created wrongly\n");
        exit(1);
    }

    return win;
}

SDL_Renderer *newRen(SDL_Window *window)
{
    SDL_Renderer *ren = SDL_CreateRenderer(
        window,                  
        -1,                      
        SDL_RENDERER_ACCELERATED 
    );

    if (ren == NULL)
    {
        printf("renderer created wrongly\n");
        exit(1);
    }

    return ren;
}

void display(SDL_Renderer *ren)
{
    for (int v = CELL; v < CELL * col; v += CELL)
    {
        SDL_SetRenderDrawColor(ren, 110, 110, 110, 110);
        SDL_RenderDrawLine(ren, v, 0, v, CELL * row);
    }
    for (int h = CELL; h < CELL * row; h += CELL)
    {
        SDL_SetRenderDrawColor(ren, 110, 110, 110, 110);
        SDL_RenderDrawLine(ren, 0, h, CELL * col, h);
    }
    SDL_Rect rect;
    rect.w = CELL + 1;
    rect.h = CELL + 1;
    for (int i = 0; i< col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            if (state[i][j] == 1)
            {
                rect.x = j * CELL;
                rect.y = i * CELL;
                SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
                SDL_RenderFillRect(ren, &rect);
            }
        }
    }
}
