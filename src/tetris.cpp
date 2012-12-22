//tetris.cpp
#include "tetris.h"

using namespace std;

void drawGrid(SDL_Surface* screen, int grid[gridHEIGHT][gridWIDTH], SDL_Surface* tiles){
    int dx, dy;
    for(int i=0; i<gridWIDTH; i++){
        for(int j=0; j<gridHEIGHT; j++){
            dx = i*gridBLOCK;
            dy = j*gridBLOCK;
            if(grid[j][i] >= 1){
                SDL_Rect grids, tilecut;
                grids.x = dx; grids.y = dy;
                int tile = grid[j][i];
                if(tile==10)tile=0;
                tilecut.x = tile*gridBLOCK; tilecut.y = 0;
                tilecut.w = gridBLOCK; tilecut.h = gridBLOCK;
                SDL_BlitSurface(tiles, &tilecut, screen, &grids);
            }
        }
    }
}

void drawBlock(SDL_Surface* screen, int type, int rotate, int X, int Y, SDL_Surface* tiles, bool fill){
    int dx, dy;
    for(int i=0; i<blockHEIGHT; i++){
        for(int j=0; j<blockWIDTH; j++){
            dx = X*gridBLOCK + i*gridBLOCK;
            dy = Y*gridBLOCK + j*gridBLOCK;
            if(blocks[type][rotate][j][i] == 1){
                SDL_Rect grids, tilecut;
                grids.x = dx; grids.y = dy;
                tilecut.x = (type+1)*gridBLOCK; tilecut.y = 0;
                tilecut.w = gridBLOCK; tilecut.h = gridBLOCK;
                if(!fill)tilecut.y = gridBLOCK;
                SDL_BlitSurface(tiles, &tilecut, screen, &grids); 
            }
        }
    }
}

bool collide(int type, int rotate, int X, int Y, int grid[gridHEIGHT][gridWIDTH]){
    for(int i=0; i<blockHEIGHT; i++){
        for(int j=0; j<blockWIDTH; j++){
            if(grid[Y+j][X+i]>=1){
                if(blocks[type][rotate][j][i]==1){
                    return true;
                }
            }
        }
    }
    return false;
}

void solidify(int type, int rotate, int X, int Y, int grid[gridHEIGHT][gridWIDTH]){
    for(int i=0; i<blockHEIGHT; i++){
        for(int j=0; j<blockWIDTH; j++){
            if(blocks[type][rotate][i][j]==1){
                grid[Y+i][X+j] = type+1;
            }
        }
    }
}

void clearGridLine(int grid[gridHEIGHT][gridWIDTH], int & score, int & lines, int lineScore, int level, int LINECLEARDELAY, SDL_Surface* screen, SDL_Surface* tileset){
    bool line = true;
    bool display = false;
    for(int i=0; i<gridHEIGHT-1; i++){
        line = true;
        for(int j=gridBORDER; j<gridWIDTH-gridBORDER; j++){
            if(grid[i][j]==0) line=false;
        }
        if(line==true){
            display = true;
            //clear the line
            for(int j=gridBORDER; j<gridWIDTH-gridBORDER; j++){
                grid[i][j]=0;//clear line
                //display
                SDL_Rect grids, tilecut;
                grids.x = j*gridBLOCK; grids.y = i*gridBLOCK;
                tilecut.x = 0; tilecut.y = gridBLOCK;
                tilecut.w = gridBLOCK; tilecut.h = gridBLOCK;
                SDL_BlitSurface(tileset, &tilecut, screen, &grids);
            }
            //move all down
            for(int k=i; k>0; k--){
                for(int l=gridBORDER; l<gridWIDTH-gridBORDER; l++){
                    grid[k][l] = grid[k-1][l];
                }
            }
            //Award player
            lines++;
            score += lineScore*level;
        }
    }
    if(display){
        //display and delay
        SDL_Flip(screen);
        SDL_Delay(LINECLEARDELAY);
    }
}

bool lose(int grid[gridHEIGHT][gridWIDTH]){
    bool dead = false;
    for(int i=gridBORDER; i<gridWIDTH-gridBORDER; i++){
        if(grid[1][i]>=1) dead = true;
    }
    return dead;
}
