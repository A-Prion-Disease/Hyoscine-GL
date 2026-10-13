#ifndef WIND_LOOP_HPP
#define WIND_LOOP_HPP


#include "Graphic_Funcs.hpp"

#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

class SDL_Interface{

const bool* keyboard_handle = nullptr;

SDL_Window* Window;
SDL_Renderer* Renderer;

SDL_WindowFlags Window_Flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
				SDL_WINDOW_HIGH_PIXEL_DENSITY;
	public:

int W_W, W_H;
int L_W, L_H;

SDL_Interface(int W, int H, bool& Running);

void CreateWindow(bool& Running);

void WindowLoop(GL_Renderer& GLR);

char InputCheck(bool& Running);

	  };

#endif
