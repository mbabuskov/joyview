#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <vector>
#include <sys/types.h>
#include <dirent.h>

// g++ -ojoyview `sdl-config --libs` -lSDL_image `sdl-config --cflags` joyview.cpp
//-----------------------------------------------------------------------------
bool getchm()
{
    while (true)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_KEYDOWN:
                    return (SDLK_ESCAPE != event.key.keysym.sym);
                case SDL_JOYBUTTONDOWN:
                    /*
                    if (event.jbutton.button > 3 && (event.jbutton.button%2 == 0))
                        return SDLK_p;
                    else
                        return SDLK_RETURN;
                        */
                    return true;
            }
        }
        SDL_Delay(1);
    }
}
//-----------------------------------------------------------------------------
int main()
{
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_JOYSTICK) < 0)
    {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return false;
    }

    // flags |= SDL_HWSURFACE|SDL_DOUBLEBUF;
    SDL_Surface *m_Screen = SDL_SetVideoMode(1024, 768, 24,
        SDL_ANYFORMAT | SDL_FULLSCREEN | SDL_SWSURFACE);
    if (!m_Screen)
    {
        fprintf(stderr, "Init failed: %s\n", SDL_GetError());
        return 1;
    }
    fprintf(stderr, "OK\n");

    SDL_Joystick *joy = 0;
    if (SDL_NumJoysticks() > 0)
        joy = SDL_JoystickOpen(0);
    fprintf(stderr, "Joysticks: %d\n", SDL_NumJoysticks());
    SDL_JoystickEventState(SDL_ENABLE);

    //SDL_ShowCursor(SDL_DISABLE);
    SDL_ShowCursor(SDL_ENABLE);

    // vrti slike
    DIR *d = opendir(".");
    struct dirent *de;
    std::vector<std::string> files;
    while (de = readdir(d))
    {
        std::string fn(de->d_name);
        if (fn.find(".jpg") == std::string::npos)
            continue;
        files.push_back(fn);
    }
    closedir(d);

    while (true)
    {
        for (std::vector<std::string>::iterator it = files.begin();
            it != files.end(); ++it)
        {
            SDL_Surface *s = IMG_Load((*it).c_str());
            if (!s)
            {
                fprintf(stderr, "%s\n", (const char *)SDL_GetError());
            }
            else
            {
                SDL_FillRect(m_Screen, NULL, 0);
                SDL_Rect dest;
                dest.x = (1024 - s->w) / 2;
                dest.y = (768 - s->h) / 2;
                SDL_BlitSurface(s, 0, m_Screen, &dest);
                SDL_Flip(m_Screen);
            }
            SDL_FreeSurface(s);
            if (!getchm())
            {
                if (joy)
                    SDL_JoystickClose(joy);
                return 0;
            }
        }
    }


    return 0;
}
//-----------------------------------------------------------------------------
