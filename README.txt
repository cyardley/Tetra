Tetris Clone v1.3.5b
by Casey Yardley
Copyright Jan 2011 Casey Yardley
==================================

Acknowledgements:
==================================
Thanks to DeathShot for his tileset.

Running on Linux
==================================
Install these packages: (look in your package manager, or google them)
-SDL 1.2
-SDL_image 1.2
-SDL_ttf 2.0
You obviously need the same development libraries to build the source on both Windows and Linux.

Controls:
==================================
up arrow: rotate block
right/left arrow: move block
down arrow: move down faster
right ctrl: swap block with next block
spacebar: drop block all the way down
Escape: Open the menu

Tilesets:
==================================
Each tile is a square.
You can set a new tileset using the -tileset command line parameter
Width/height of each square should depend on the "gridBlock"
  variable (change with -gridBLOCK command line parameter).
The grid is set up like:
  [border][I][square][T][N][rN][L][rL]
  [lineclear].. 'future' versions of above

Command Line Parameters:
==================================
note: some of these could break the game...
'-about' -- prints info about the program
'-help' -- show this list
'-fullscreen' -- run the game in fullscreen mode
'-noCentre' -- do not centre the window in the screen
'-cheat' -- allow cheating (press . key)
'-future' -- show where the block will land
'-hard' -- starts the game on hard difficulty
'-framerate X' -- set max frames per second to X
'-ticks X' -- X milliseconds for each tick
'-tickLevel X' -- X*level for game to add to tick
'-timeScore X' -- X score per second
'-lineScore X' -- X score for clearing a line
'-lineLevel X' -- clear X lines to go up a level
'-gridBLOCK X' -- X pixels height/width of each tile in game grid
'-gridBorder X' -- X empty tiles on either side of game
'-tileset X' -- changes tileset to ../data/X
'-lineclear X' -- change line clear delay time to X
