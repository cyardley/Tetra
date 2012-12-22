//util.h
#ifndef UTIL_H 
#define UTIL_H
#include <iostream>
#include <sstream>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "tetris.h"

void printHelp();

void drawText(std::string str, int X, int Y, Uint32 COLOR, int SIZE, SDL_Surface * screen);

void fillScreen(SDL_Surface* mainScreen);

std::string itoa(int i);

SDL_Color Uint32toSDL_Color(Uint32 i);


#endif
