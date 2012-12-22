//TETRIS
//----------------------
/* TODO
 * Interface improvements
 * Major Code Refactoring
 * Better menus, more options
 * Config file
 *Balance
/*/

//Includes
//---------------------
#include <iostream>
#include <fstream>
#include <time.h>
//---------------------
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
//---------------------
#include "tetris.h"
#include "util.h"
//---------------------
using namespace std;

//About
//---------------------
string name = "Tetris Clone";
string shortName = "Tetris";
string author = "Casey Yardley";
string about = "A simple tetris clone";
string year = "Jan 2011";
string copyright = "Copyright " + year + " " + author;
string version = "1.3.5";
string titleBar = name + " v" + version;

//Global Constants
//---------------------
Uint32 SCREEN_FLAGS = SDL_DOUBLEBUF/*|SDL_FULLSCREEN*/;
int SCREEN_DEPTH = 32;
int SCREEN_RES_X = 600;
int SCREEN_RES_Y = 560;
enum dir{NONE, UP, DOWN, LEFT, RIGHT};

//Global Variables
//---------------------
bool CHEAT = false;
bool SCREEN_CENTER = true;
bool ghost = false; //show where block will land
SDL_Surface* mainScreen;
int ticks = 500; //millseconds for each tick
int tickLevel = 5; //game adds tickLevel*level to ticks
int timeScore = 1; //score per second
int lineScore = 100; //base score for clearing a line
int lineLevel = 5; //lines to clear to go up a level
int FRAMERATE = 10; //frames per second
int LINECLEARDELAY = 500; //time to delay on each line clear (ms)
int score = 0;
bool hard = false;
int hardModifier = 5;
string highScores[5][2];
string tileset = "../data/deathshot.png";

//extern in tetris.h
int gridBLOCK = 20; //width/height of grid blocks
int gridBORDER = 3; //number of tiles on the sides

//Function Definitions
//---------------------
bool playGame(SDL_Surface* mainScreen);
void fillScreen(SDL_Surface* mainScreen);
void titleScreen(SDL_Surface* mainScreen);
bool menuScreen(SDL_Surface* mainScreen);
bool optionsScreen(SDL_Surface* mainScreen);

//Main
//---------------------
int main(int argc, char *argv[]){

    //Load Highscores
    ifstream scoreFile;
    scoreFile.open ("../data/scores.dat");
    if(scoreFile.is_open()){
        for(int i=0; i<5; i++){
            scoreFile >> highScores[i][0];
            scoreFile >> highScores[i][1];
        }
        scoreFile.close();
    }else cerr << "ERROR: Could not open ../data/scores.dat\n";
    //Command Line Params
    for(int i = 0; i < argc; i++){
        string str = argv[i];
        if(str=="help" || str=="-help" || str=="commands") printHelp(); //exits
        if(str=="-about") cout << titleBar << endl << "by " << author << endl << copyright << endl;
        if(str=="-fullscreen") SCREEN_FLAGS = SDL_DOUBLEBUF|SDL_FULLSCREEN;
        if(str=="-cheat") CHEAT = !CHEAT;
        if(str=="-ghost") ghost = !ghost;
        if(str=="-hard") hard = !hard;
        if(str=="-hardMod") hardModifier = atoi(argv[i+1]);
        if(str=="-framerate") FRAMERATE = atoi(argv[i+1]);
        if(str=="-noCentre") SCREEN_CENTER=!SCREEN_CENTER;
        if(str=="-ticks") ticks = atoi(argv[i+1]);
        if(str=="-tickLevel") tickLevel = atoi(argv[i+1]);
        if(str=="-timeScore") timeScore = atoi(argv[i+1]);
        if(str=="-lineScore") lineScore = atoi(argv[i+1]);
        if(str=="-lineLevel") lineLevel = atoi(argv[i+1]);
        if(str=="-gridBLOCK") gridBLOCK = atoi(argv[i+1]);
        if(str=="-gridBORDER") gridBORDER = atoi(argv[i+1]);
        if(str=="-tileset"){ string ts = argv[i+1]; tileset = "../data/"+ts; }
        if(str=="-lineclear") LINECLEARDELAY = atoi(argv[i+1]);
    }
     
    //Setup SDL
    mainScreen = SDL_SetVideoMode(SCREEN_RES_X, SCREEN_RES_Y, SCREEN_DEPTH, SCREEN_FLAGS);
    SDL_EnableUNICODE(true); //enable unicode
    if( SCREEN_CENTER ){
        putenv((char*)("SDL_VIDEO_CENTERED=1"));
    }
    if( mainScreen==NULL ){
        cout << "Could not set video mode: "<< SDL_GetError() << endl; 
        exit(1);
    }
    if( (SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO)==-1) ){
        cerr << "Could not Initalize SDL:" << SDL_GetError() << endl;
        exit(1);
    }else{ atexit(SDL_Quit); 
    }
    if( (TTF_Init()==-1) ){
        cerr << "Could not Initalize TTF:" << TTF_GetError() << endl;
        exit(1);
    }else{ atexit(TTF_Quit); 
    }
    SDL_WM_SetCaption(titleBar.c_str(), shortName.c_str());
    SDL_WM_SetIcon(IMG_Load("../data/icon.png"), NULL);
    srand ( time(NULL) );

    bool drawPage = true;
    while(true){
        if(drawPage)titleScreen(mainScreen);
        drawPage = false;
        //Handle Events
        SDL_Event event; 
        while (SDL_PollEvent(&event)){
           if (event.type==SDL_QUIT) return 0;
           if(event.type==SDL_KEYDOWN){ //if a key is pressed, play the game
               if(event.key.keysym.sym==SDLK_ESCAPE){
                   if(menuScreen(mainScreen) == false)return 0;
               }else{
                   playGame(mainScreen);
               }
               drawPage = true;
           }
        }
    }
    return 0;
}

//Title Screen
//--------------------
void titleScreen(SDL_Surface* mainScreen){
    //Calculate Highscores
    bool newScore = false;
    int nameIndex = 0;
    int scoreRecord;
    string s0, s1;
    for (int i=0; i<5; i++){
        if(score > atoi(highScores[i][1].c_str()) && newScore==false){
            string prev0 = highScores[i][0];
            string prev1 = highScores[i][1];
            highScores[i][0] = "_--";
            highScores[i][1] = itoa(score);            
            for(int j=i+1; j<5; j++){ 
                string tmp0 = highScores[j][0];
                string tmp1 = highScores[j][1];
                highScores[j][0] = prev0;
                highScores[j][1] = prev1;
                prev0 = tmp0; prev1 = tmp1;
            }
            newScore = true;
            scoreRecord = i;
        }
    }
    //Wait
    do {
        //handle initials input
        if(newScore){
            SDL_Event event;  
            while (SDL_PollEvent(&event)){            
                if(event.type==SDL_KEYDOWN){
                     if(event.key.keysym.sym==SDLK_RETURN && nameIndex > 2) newScore = false;
                     if(event.key.keysym.sym==SDLK_BACKSPACE){
                         nameIndex--;
                         (highScores[scoreRecord][0])[nameIndex] = '_';
                         if(nameIndex<0)nameIndex=0;
                         (highScores[scoreRecord][0])[nameIndex+1] = '-';
                     }
                     if(nameIndex<3){
                        char c = event.key.keysym.unicode;
                        if(isalnum(c)){
                            (highScores[scoreRecord][0])[nameIndex] = c;
                            nameIndex++;;
                            if(nameIndex<3)(highScores[scoreRecord][0])[nameIndex] = '_';
                       }
                    }
                }
            }
            //Save the new highscore to a file
            ofstream scoreFile;
            scoreFile.open ("../data/scores.dat");
            if(scoreFile.is_open()){
                for(int i=0; i<5; i++){
                scoreFile << highScores[i][0] << endl;
                scoreFile << highScores[i][1] << endl;
                }
                scoreFile.close();
           }else cerr << "ERROR: Could not open ../data/scores.dat\n";
        }
        fillScreen(mainScreen);        
        drawText("TETRIS", 120, 50, WHITE, 100, mainScreen);
        if(score!=0) drawText("Your Score: "+itoa(score), 140, 200, WHITE, 30, mainScreen);
        else drawText("=Press A Key=", 175, 200, WHITE, 30, mainScreen);
        //HighScores
        drawText("=High Scores=", 170, 260, WHITE, 30, mainScreen);
        for(int i=0; i<5; i++){
            drawText(highScores[i][0], 140, 300+(i*40), WHITE, 30, mainScreen); //Draw Name
            drawText(highScores[i][1], 300, 300+(i*40), WHITE, 30, mainScreen); //Draw Score
        }
        //Update Screen
        drawText(titleBar+", "+copyright, 35, 530, WHITE, 18, mainScreen);
        SDL_Flip(mainScreen);
    }while(newScore);
}

//Menu Screen
//--------------------
bool menuScreen(SDL_Surface* mainScreen){
    bool loop = true;
    bool update = true;
    int menu = 0;
    while(loop){
        SDL_Event event;  
        while (SDL_PollEvent(&event)){
            //Quit
            if(event.type==SDL_QUIT)exit(0);
            //Key Down
            if(event.type==SDL_KEYDOWN){
                //Return to game
                if(event.key.keysym.sym==SDLK_ESCAPE){
                    loop=false;
                }
                //Select Optons
                if(event.key.keysym.sym==SDLK_UP){
                    update = true;
                    if(menu==0)menu=4;
                    if(menu>0)menu--;
                }
                if(event.key.keysym.sym==SDLK_DOWN){
                    update = true;
                    if(menu==3)menu=-1;
                    if(menu<3)menu++;
                }
                //Apply Selection
                if(event.key.keysym.sym==SDLK_RETURN){
                    update = true;
                    if(menu==0) loop=false;
                    if(menu==1) optionsScreen(mainScreen);
                    if(menu==2) return false;
                    if(menu==3) exit(0);
                }
            }
        }
        //Draw
        if(update){
            SDL_Rect rect; rect.x=70; rect.y=70; rect.w = 450; rect.h = 450;
            SDL_FillRect(mainScreen, &rect, DARKGREY);
            drawText("=MENU=", 150, 80, WHITE, 60, mainScreen);
            drawText("Resume", 180, 180, WHITE, 50, mainScreen);
            drawText("Options", 185, 260, WHITE, 50, mainScreen);
            drawText("Title Screen", 140, 340, WHITE, 50, mainScreen);
            drawText("Exit", 230, 420, WHITE, 50, mainScreen);
            string cur = "-                       -";
            drawText(cur, 90, 180+(menu*80), WHITE, 50, mainScreen);
            SDL_Flip(mainScreen);
            update = false;
        }
    }
    return true;
}

//Options Screen
//--------------------
bool optionsScreen(SDL_Surface* mainScreen){
    bool loop = true;
    bool update = true;
    int menu = 0;
    while(loop){
        SDL_Event event;  
        while (SDL_PollEvent(&event)){
            //Quit
            if(event.type==SDL_QUIT)exit(0);
            //Key Down
            if(event.type==SDL_KEYDOWN){
                //Return to game
                if(event.key.keysym.sym==SDLK_ESCAPE){
                    loop=false;
                }
                //Select Optons
                if(event.key.keysym.sym==SDLK_UP){
                    update = true;
                    if(menu==0)menu=3;
                    if(menu>0)menu--;
                }
                if(event.key.keysym.sym==SDLK_DOWN){
                    update = true;
                    if(menu==2)menu=-1;
                    if(menu<2)menu++;
                }
                //Apply Selection
                if(event.key.keysym.sym==SDLK_RETURN){
                    update=true;
                    if(menu==0) loop=false;
                    if(menu==1) ghost=!ghost;
                    if(menu==2) hard=!hard;
                }
            }
        }
        //Draw
        if(update){
            SDL_Rect rect; rect.x=70; rect.y=70; rect.w = 450; rect.h = 450;
            SDL_FillRect(mainScreen, &rect, DARKGREY);
            drawText("=OPTIONS=", 110, 80, WHITE, 60, mainScreen);
            drawText("Return", 200, 180, WHITE, 50, mainScreen);
            string ghostOption; if(ghost)ghostOption="on"; else ghostOption="off";
            drawText("Ghosting: "+ghostOption, 135, 260, WHITE, 50, mainScreen);
            string difficultyOption; if(hard)difficultyOption="Hard"; else difficultyOption="Easy";
            drawText("Difficulty: "+difficultyOption, 120, 340, WHITE, 45, mainScreen);
            string cur = "-                       -";
            drawText(cur, 90, 180+(menu*80), WHITE, 50, mainScreen);
            SDL_Flip(mainScreen);
            update = false;
        }
    }
    return true;
}

//Play Game
//--------------------
bool playGame(SDL_Surface* mainScreen){
    score = 0;
    bool runGame = true;
    int timer = SDL_GetTicks();
    int fps = SDL_GetTicks();
    int level = 0;
    int lines = 0;
    int ghostY = 0;
    dir direction = NONE;
    int blockX, blockY, rotate, blockType, rr;
    int nextBlock = (rand()%blockNUM);
    bool newBLOCK = true;
    //load tileset
    SDL_Surface* tiles = IMG_Load(tileset.c_str());
    if(!tiles){
        cerr << "Error: Could not load " << tileset << endl;
        exit(1);
    }
    //Set up grid data
    int gridDATA[gridHEIGHT][gridWIDTH];
    for(int i=0; i<gridWIDTH; i++){
        for(int j=0; j<gridHEIGHT; j++){
            if( i==gridBORDER-1 || i==gridWIDTH-gridBORDER || j==gridHEIGHT-1 ){
                gridDATA[j][i] = 10;
            }else{
                gridDATA[j][i] = 0;
            }
        }
    }
    //Main Loop
    while(runGame){
        //time for a new block
        if(newBLOCK){
            blockX = (int)(gridWIDTH/2)-2;
            blockY = 1;
            rotate = 0;
            blockType = nextBlock;
            rr = (rand()%blockNUM);
            nextBlock = rr;
            newBLOCK = false;
        }
        //SDL Events
        SDL_Event event;  
        while (SDL_PollEvent(&event)){
            //Quit
            if(event.type==SDL_QUIT) exit(0);
            //Key Down
            if(event.type==SDL_KEYDOWN){
                //Rotate Block
                if(event.key.keysym.sym==SDLK_UP){
                    rotate++; direction=UP;
                    if(rotate>blockROTATE-1)rotate=0;
                    if(collide(blockType, rotate, blockX, blockY, gridDATA)){ //don't rotate into walls
                        rotate--;
                        if(rotate<0)rotate=blockROTATE-1;
                    }
                }
                //Switch block with next
                if(event.key.keysym.sym==SDLK_RCTRL){
                    int t = blockType;
                    blockType = nextBlock;
                    nextBlock = t;
                }
                //Drop block
                if(event.key.keysym.sym==SDLK_SPACE){
                     while( !collide(blockType, rotate, blockX, blockY, gridDATA) ){
                        blockY++;
                    }
                    blockY--;//correct
                }
                //Toggle Pause
                if(event.key.keysym.sym==SDLK_ESCAPE){
                    if(menuScreen(mainScreen) == false) runGame=false;
                }
                //Rotate though blocks (cheating)
                if(CHEAT && event.key.keysym.sym==SDLK_PERIOD){
                    blockType++;
                    if(blockType>=blockNUM)blockType=0;
                }
            }
           //Pause automatically if loose keyboard focus
            if(event.type== SDL_ACTIVEEVENT){
                if( event.active.state & SDL_APPINPUTFOCUS ){ //if keyboard focus changes
                    if( event.active.gain == 0 ){ //to inactive
                        menuScreen(mainScreen);
                    }
                }
            }
        }
        //Move Blocks 
        Uint8 *keystates = SDL_GetKeyState(NULL);
        if(keystates[SDLK_LEFT]){
            blockX--; direction=LEFT;
            if(collide(blockType, rotate, blockX, blockY, gridDATA))blockX++; //double check
        }
        if(keystates[SDLK_RIGHT]){
            blockX++; direction=RIGHT;
            if(collide(blockType, rotate, blockX, blockY, gridDATA))blockX--; //double check
        }
        if(keystates[SDLK_DOWN]){
            blockY++; direction=DOWN;
            if(collide(blockType, rotate, blockX, blockY, gridDATA)){
                blockY--;
                solidify(blockType, rotate, blockX, blockY, gridDATA);
                newBLOCK = true;
            }
        }
        //End SDL Events
       
        //Game Events
        //Ticks
        int tickCalc = ticks-(tickLevel*level);
        if(hard) tickCalc /= hardModifier;
        if(SDL_GetTicks() - timer >= tickCalc){
            score += timeScore;
            blockY++; direction=DOWN;
            if(collide(blockType, rotate, blockX, blockY, gridDATA)){
                blockY--;
                solidify(blockType, rotate, blockX, blockY, gridDATA);
                newBLOCK = true;
            }
            timer = SDL_GetTicks();
        }
        direction=NONE;
        //Clear any compleated lines
        clearGridLine(gridDATA, score, lines, lineScore, level, LINECLEARDELAY, mainScreen, tiles);
        //Deal with losing
        if(lose(gridDATA)) runGame=false;
        //Deal with Levels
        if(lines>=lineLevel){level++;lines=0;}
        //get ghostY
        ghostY=blockY;
        if(ghost){ while( !collide(blockType, rotate, blockX, ghostY, gridDATA) ){ ghostY++; } ghostY--;}
        //Graphical Display
        fillScreen(mainScreen);
        drawText("Score: ", 370, 50, WHITE, 35, mainScreen);
        drawText(itoa(score), 370, 90, WHITE, 35, mainScreen);
        drawText("Lines: "+itoa(lines), 370, 140, WHITE, 35, mainScreen);
        drawText("Level: "+itoa(level), 370, 180, WHITE, 35, mainScreen);
        drawGrid(mainScreen, gridDATA, tiles);
        drawBlock(mainScreen, blockType, rotate, blockX, blockY, tiles, true); //current block
        drawBlock(mainScreen, nextBlock, 0, 23, 16, tiles, true); // next block
        drawBlock(mainScreen, blockType, rotate, blockX, ghostY, tiles, false); //ghost block
        SDL_Flip(mainScreen); //Update Screen
        
        //Frame Rate
        if(SDL_GetTicks()-fps > (1000/FRAMERATE)){ 
            SDL_Delay( (1000/FRAMERATE) ); 
        } 
    }//End Main Loop
    return false;
}

