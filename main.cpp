#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

void DrawOnSurface(SDL_Surface &surface, int x, int y);

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *mWindow = SDL_CreateWindow("Random Walk", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 360, SDL_WINDOW_SHOWN);

    SDL_Surface *mSurface = SDL_GetWindowSurface(mWindow);
    SDL_FillRect(mSurface, nullptr, SDL_MapRGB(mSurface->format, 0, 0, 0));

    SDL_Event event;
    bool isRunning = true;
    int x = 640 / 4;
    int y = 360 / 4;
    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }
        int randNum = (std::rand() % 4);
        if (randNum == 0)
        {
            ++x;
        }
        if (randNum == 1)
        {
            --x;
        }
        if (randNum == 2)
        {
            ++y;
        }
        if (randNum == 3)
        {
            --y;
        }
        DrawOnSurface(*mSurface, x, y);
        SDL_UpdateWindowSurface(mWindow);
    }

    SDL_FreeSurface(mSurface);
    SDL_DestroyWindow(mWindow);
    return 0;
}

void DrawOnSurface(SDL_Surface &surface, int x, int y)
{
    int width = surface.w;
    int height = surface.h;
    if (x >= width || x <= 0 || y <= 0 || y >= height)
    {
        return;
    }
    int index = y * width + x;
    uint32_t white = SDL_MapRGB(surface.format, 255, 255, 255);
    SDL_LockSurface(&surface);
    uint32_t *pixels = (uint32_t *)surface.pixels;
    pixels[index] = white;
    SDL_UnlockSurface(&surface);
}
