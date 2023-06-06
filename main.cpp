#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

void DrawOnSurface(SDL_Surface &surface, int x, int y);

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *mWindow = SDL_CreateWindow("Random Walk", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320 * 3, 180 * 3, SDL_WINDOW_SHOWN);

    SDL_Surface *mSurface = SDL_GetWindowSurface(mWindow);
    SDL_Surface *mBackSurface = SDL_CreateRGBSurface(0, 320, 180, 32, 0, 0, 0, 0);
    SDL_FillRect(mSurface, nullptr, SDL_MapRGB(mSurface->format, 0, 0, 0));
    SDL_FillRect(mBackSurface, nullptr, SDL_MapRGB(mSurface->format, 0, 0, 0));

    SDL_Event event;
    bool isRunning = true;
    bool isPaused = false;
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
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_SPACE)
                {
                    isPaused = !isPaused;
                }
            }
        }
        if (!isPaused)
        {
            std::srand(static_cast<unsigned int>(SDL_GetTicks() * (std::rand() % (RAND_MAX / 2)) + 1));
            int randY = (std::rand() % 3) - 1;
            y += randY;
            SDL_Delay(std::rand() % 100);
            std::srand(static_cast<unsigned int>((SDL_GetTicks64() % (std::rand() % RAND_MAX) * std::rand())));
            int randX = (std::rand() % 3) - 1;
            x += randX;
            DrawOnSurface(*mBackSurface, x, y);
            SDL_BlitScaled(mBackSurface, nullptr, mSurface, nullptr);
            SDL_UpdateWindowSurface(mWindow);
        }
    }

    SDL_FreeSurface(mBackSurface);
    SDL_FreeSurface(mSurface);
    SDL_DestroyWindow(mWindow);
    return 0;
}

void DrawOnSurface(SDL_Surface &surface, int x, int y)
{
    int width = surface.w;
    int height = surface.h;
    if (x > width)
    {
        x = width;
    }
    if (x < 0)
    {
        x = 0;
    }
    if (y < 0)
    {
        y = 1;
    }
    if (y > height)
    {
        y = height - 1;
    }

    int index = y * width + x;
    uint32_t red = SDL_MapRGB(surface.format, 175, 0, 0);
    SDL_LockSurface(&surface);
    uint32_t *pixels = (uint32_t *)surface.pixels;
    if (pixels[index] != red)
    {
        pixels[index] = red;
    }
    else
    {
        pixels[index] = SDL_MapRGB(surface.format, 175, 0x8B, 0);
    }
    SDL_UnlockSurface(&surface);
}
