#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"
#include <SDL2/SDL.h>

#define CELL 40
int state[50][50];
int next[50][50];
int col = 0, row = 0;
//the module to create a new window
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
//check if fault
    if (win == NULL)
    {
        printf("window created wrongly\n");
        exit(1);
    }

    return win;
}
//the module to create a new renderer
SDL_Renderer *newRen(SDL_Window *window)
{
    SDL_Renderer *ren = SDL_CreateRenderer(
        window,                  
        -1,                      
        SDL_RENDERER_ACCELERATED 
    );
//check if fault
    if (ren == NULL)
    {
        printf("renderer created wrongly\n");
        exit(1);
    }

    return ren;
}

void display(SDL_Renderer *ren)
{
    //draw lines
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
    //draw cells
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
//the module to read in the data
int read(char *filename)
{
    FILE *file;
    file = fopen(filename, "r");
    //check if fault
    if (file == NULL||filename==NULL)
    {
        printf("file not found");
        return -1;
    }
    //read
    fscanf(file, "%d%d\n", &col, &row);
    char c;
    for (int i = 0; i < col; ++i)
    {
        for (int j = 0; j < row; ++j)
        {
            c = fgetc(file);
            if (c == '0')
            {
                state[i][j] = 0;
            }
            else if (c == '1')
            {
                state[i][j] = 1;
            }
            else if (c == '\n')
            {
                i--;
                break;
            }
        }
    }
    fclose(file);
    return 0;
}
//the module to write the data
int write(char *filename)
{
    FILE *file = fopen(filename, "w+");
    //write
    if (filename==NULL)
    {
        return -1;
    }
    fprintf(file, "%d %d\n", col, row);
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            if (state[i][j]==1)
            {
                fputc('1',file);
            }else
            {
                fputc('0',file);
            }
        }
        fputc('\n',file);
    }
    return 0;
}
//the module to get the next generation
int nextgeneretion()
{
    //generate another one
    int livesum = 0;
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            if (i == 0 && j == 0)
            {
                livesum = state[i + 1][j + 1] + state[i][j + 1] + state[i + 1][j];
            }
            else if (i == 0 && j == row - 1)
            {
                livesum = state[i + 1][j - 1] + state[i][j - 1] + state[i + 1][j];
            }
            else if (j == 0 && i == col - 1)
            {
                livesum = state[i - 1][j + 1] + state[i][j + 1] + state[i - 1][j];
            }
            else if (i == 0 && j != 0 && j != row - 1)
            {
                livesum =
                    state[i + 1][j] + state[i][j + 1] + state[i][j - 1] + state[i + 1][j + 1] + state[i + 1][j - 1];
            }
            else if (j == 0 && i != 0 && i != col - 1)
            {
                livesum =
                    state[i + 1][j] + state[i][j + 1] + state[i - 1][j] + state[i - 1][j + 1] + state[i + 1][j + 1];
            }
            else if (i == col - 1 && j != 0 && j != row - 1)
            {
                livesum =
                    state[i][j - 1] + state[i][j + 1] + state[i - 1][j] + state[i - 1][j - 1] + state[i - 1][j + 1];
            }
            else if (j == row - 1 && i != 0 && i != col - 1)
            {
                livesum =
                    state[i + 1][j] + state[i][j - 1] + state[i - 1][j] + state[i - 1][j - 1] + state[i + 1][j - 1];
            }
            else if (j == row - 1 && i == col - 1)
            {
                livesum = state[i - 1][j] + state[i][j - 1] + state[i - 1][j - 1];
            }
            else
            {
                livesum = state[i + 1][j] + state[i + 1][j + 1] + state[i + 1][j - 1] + state[i - 1][j] +
                          state[i - 1][j + 1] + state[i - 1][j - 1] + state[i][j + 1] + state[i][j - 1];
            }
            if (state[i][j] == 1)
            {
                switch (livesum)
                {
                case 0:
                    next[i][j] = 0;
                    break;
                case 1:
                    next[i][j] = 0;
                    break;
                case 2:
                    next[i][j] = 1;
                    break;
                case 3:
                    next[i][j] = 1;
                    break;
                default:
                    next[i][j] = 0;
                    break;
                }
            }
            else
            {
                if (livesum == 3)
                {
                    next[i][j] = 1;
                }
            }
        }
    }
    //copy it back to the state
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            state[i][j] = next[i][j];
        }
    }
    return 0;
}
// the main module
int main(int argc, char *argv[])
{
    int times=0;
    if (argc>=2)
    {
        times=atoi(argv[1]);
    }
    
    int mx,my;
    read("init.txt");
//init everything
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window *win = newWin("game of life");
    SDL_Renderer *ren = newRen(win);
//event init
    SDL_Event windowEvent;
    int run = 1;
    int click=0,start=0;
    int n=0;
//event start
    while (run)
    {   
        click=0;
        if (times!=0)
        {
            if (n==times)
        {
            break;
        }
        }
        while (SDL_PollEvent(&windowEvent))
        {
            switch(windowEvent.type){
                case SDL_QUIT:
                    run=0;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    click =1;
                    break;
                    
                case SDL_KEYDOWN:
                    if(windowEvent.key.keysym.sym == SDLK_SPACE)start=1;
            }
        }
        //if click
        SDL_GetMouseState(&mx,&my);
        if (click)
        {
            state[my/CELL][mx/CELL]=!state[my/CELL][mx/CELL];
        }
        if (start)
        {
            nextgeneretion();
            n++;
        }
        //draw
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderClear(ren);
        display(ren);
        SDL_RenderPresent(ren);
//wait
        if (start)
        {
            SDL_Delay(1000/30);
        }
    }
//quit
    SDL_Quit();
    write("final.txt");
    return 0;
}