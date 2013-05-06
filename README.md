joyview
=======

Simple image viewer with joystick support using SDL library


Compiling
=========

You need to have SDL and SDL_image installed.

g++ -ojoyview `sdl-config --libs` -lSDL_image `sdl-config --cflags` joyview.cpp

Limitations
===========

Resolution is currently fixed in the code to 1024x768.
