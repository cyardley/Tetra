//tetris.h
#ifndef TETRIS_H 
#define TETRIS_H
#include <iostream>
#include "SDL/SDL.h"

//Colors (0xRRGGBB)
const Uint32 BLACK = 0x000000;
const Uint32 DARKGREY = 0x444444;
const Uint32 WHITE = 0xffffff;
const Uint32 RED = 0xff0000;
const Uint32 GREEN = 0x00ff00;
const Uint32 BLUE = 0x0000ff;
const Uint32 YELLOW = 0xffff00;
const Uint32 LIGHTBLUE = 0x00ffffff;
const Uint32 PINK = 0xff00ff;
const Uint32 ORANGE = 0xff9900;


//Grid Data
extern int gridBLOCK;//def in main.cpp
extern int gridBORDER;//def in main.cpp
extern bool DRAW_GRID; //def in main.cpp
const int gridWIDTH = 20;
const int gridHEIGHT = 28;
void drawGrid(SDL_Surface* screen, int grid[gridHEIGHT][gridWIDTH], SDL_Surface* tiles);
void clearGridLine(int grid[gridHEIGHT][gridWIDTH], int & score, int & lines, int lineScore, int level, int LINECLEARDELAY, SDL_Surface* screen, SDL_Surface* tileset);
bool lose(int grid[gridHEIGHT][gridWIDTH]);

//BLOCK DATA:
const int blockWIDTH = 4;
const int blockHEIGHT = 4;
const int blockNUM = 7;
const int blockROTATE= 4;
void drawBlock(SDL_Surface* screen, int type, int rotate, int X, int Y, SDL_Surface* tiles, bool fill);
bool collide(int type, int rotate, int X, int Y, int grid[gridHEIGHT][gridWIDTH]);
void solidify(int type, int rotate, int X, int Y, int grid[gridHEIGHT][gridWIDTH]);

const bool blocks[blockNUM][blockROTATE][blockHEIGHT][blockWIDTH] = {
    {
// I
        { {0,1,0,0},
          {0,1,0,0},
          {0,1,0,0},
          {0,1,0,0} },
          
        { {0,0,0,0},
          {1,1,1,1},
          {0,0,0,0},
          {0,0,0,0} },
       
        { {0,1,0,0},
          {0,1,0,0},
          {0,1,0,0},
          {0,1,0,0} },

        { {0,0,0,0},
          {1,1,1,1},
          {0,0,0,0},
          {0,0,0,0} },
    },{
// [ ]
        { {1,1,0,0},
          {1,1,0,0},
          {0,0,0,0},
          {0,0,0,0} },

        { {1,1,0,0},
          {1,1,0,0},
          {0,0,0,0},
          {0,0,0,0} },
       
        { {1,1,0,0},
          {1,1,0,0},
          {0,0,0,0},
          {0,0,0,0} },

        { {1,1,0,0},
          {1,1,0,0},
          {0,0,0,0},
          {0,0,0,0} },
    },{
// T
        { {0,1,0,0},
          {1,1,1,0},
          {0,0,0,0},
          {0,0,0,0} },

        { {0,1,0,0},
          {1,1,0,0},
          {0,1,0,0},
          {0,0,0,0} },
       
        { {1,1,1,0},
          {0,1,0,0},
          {0,0,0,0},
          {0,0,0,0} },

        { {1,0,0,0},
          {1,1,0,0},
          {1,0,0,0},
          {0,0,0,0} },
     },{
// N
        { {1,1,0,0},
          {0,1,1,0},
          {0,0,0,0},
          {0,0,0,0} },

        { {0,1,0,0},
          {1,1,0,0},
          {1,0,0,0},
          {0,0,0,0} },
       
        { {1,1,0,0},
          {0,1,1,0},
          {0,0,0,0},
          {0,0,0,0} },

        { {0,1,0,0},
          {1,1,0,0},
          {1,0,0,0},
          {0,0,0,0} },
    },{
// rN
        { {0,1,1,0},
          {1,1,0,0},
          {0,0,0,0},
          {0,0,0,0} },
          
        { {1,0,0,0},
          {1,1,0,0},
          {0,1,0,0},
          {0,0,0,0} },
       
        { {0,1,1,0},
          {1,1,0,0},
          {0,0,0,0},
          {0,0,0,0} },

        { {1,0,0,0},
          {1,1,0,0},
          {0,1,0,0},
          {0,0,0,0} },
    },{
// L
        { {0,1,0,0},
          {0,1,0,0},
          {0,1,1,0},
          {0,0,0,0} },

        { {0,0,0,0},
          {0,0,1,0},
          {1,1,1,0},
          {0,0,0,0} },
       
        { {1,1,0,0},
          {0,1,0,0},
          {0,1,0,0},
          {0,0,0,0} },

        { {0,0,0,0},
          {1,1,1,0},
          {1,0,0,0},
          {0,0,0,0} },
    },{
// rL
        { {0,1,0,0},
          {0,1,0,0},
          {1,1,0,0},
          {0,0,0,0} },

        { {0,0,0,0},
          {1,1,1,0},
          {0,0,1,0},
          {0,0,0,0} },
       
        { {0,1,1,0},
          {0,1,0,0},
          {0,1,0,0},
          {0,0,0,0} },

        { {1,0,0,0},
          {1,1,1,0},
          {0,0,0,0},
          {0,0,0,0} }
    }
};

#endif
