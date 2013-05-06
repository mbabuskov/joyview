JoyView
=======

Simple image viewer with joystick support using SDL library.

I built this so that my 2-year-old kid can easily browse pictures in a directory without messing up anything.


Usage
=====

Run ./joyview in some directory with pictures.
Use any keyboard key or any joystick button to go to the next image.
Use ESC to quit.


Compiling
=========

You need to have SDL and SDL_image installed.

g++ -ojoyview `sdl-config --libs` -lSDL_image `sdl-config --cflags` joyview.cpp

Limitations
===========

Resolution is currently fixed in the code to 1024x768.
