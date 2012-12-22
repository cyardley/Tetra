//util.cpp
#include "util.h"
using namespace std;

//Print Help
//--------------------
void printHelp(){
    cout << "Command Line Parameters:\n";
    cout << "note: some of these could break the game...\n";
    cout << "'-about' -- prints info about the program\n";
    cout << "'-help' -- show this list\n";
    cout << "'-fullscreen' -- run the game in fullscreen mode\n";
    cout << "'-noCentre' -- do not centre the window in the screen\n";
    cout << "'-cheat' -- allow cheating (press . key)\n";
    cout << "'-future' -- show where the block will land\n";
    cout << "'-hard' -- starts the game on hard difficulty\n";
    cout << "'-hardMod' -- hard mode tick modifier\n";
    cout << "'-framerate X' -- set max frames per second to X\n";
    cout << "'-ticks X' -- X milliseconds for each tick\n";
    cout << "'-tickLevel X' -- X*level for game to add to tick\n";
    cout << "'-timeScore X' -- X score per second\n";
    cout << "'-lineScore X' -- X score for clearing a line\n";
    cout << "'-lineLevel X' -- clear X lines to go up a level\n";
    cout << "'-gridBLOCK X' -- X pixels height/width of each tile in game grid\n";
    cout << "'-gridBorder X' -- X empty tiles on either side of game\n";
    cout << "'-tileset X' -- changes tileset to ../data/X\n";
    cout << "'-lineclear X' -- change line clear delay time to X\n";
    exit(0);
}

//Draw Text
//--------------------
void drawText(string str, int X, int Y, Uint32 COLOR, int SIZE, SDL_Surface * screen){
    SDL_Color col = Uint32toSDL_Color(COLOR);
    TTF_Font *font = TTF_OpenFont( "../data/font.ttf", SIZE ); 
    SDL_Surface* text = TTF_RenderText_Solid(font, str.c_str(), col);
    SDL_Rect rect;rect.x = X;rect.y = Y;
    SDL_BlitSurface(text, NULL, screen, &rect);
    SDL_FreeSurface(text); 
    TTF_CloseFont(font);
}

//Fill Screen
//--------------------
void fillScreen(SDL_Surface* mainScreen){
    SDL_Rect rect;
    rect.x=0; rect.y=0;
    rect.w = mainScreen->w; rect.h = mainScreen->h;
    SDL_FillRect(mainScreen, &rect, BLACK); 
}

//convert integer to string
//--------------------
string itoa(int i){
    stringstream s;
    s << i;
    return s.str();
}

//Convert a Uint32 to a SDL_Color
//--------------------
SDL_Color Uint32toSDL_Color(Uint32 i){
    SDL_Color c;
    c.r = i >> 16;
    c.g = i >> 8;
    c.b = i;
    return c;
}
