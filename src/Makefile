#Makefile

#Config
COMPILER = g++
EDITOR = gedit
EDITOR_FLAGS = &

#Flags
SDL_FLAGS = -lSDL -lSDL_image -lSDL_ttf
COMPILE_FLAGS =

#Files
EXECUTABLES = main
OBJECT_FILES = main.o tetris.o util.o
HEADER_FILES = tetris.h util.h

#all:
all: $(EXECUTABLES)

#Main:
main: $(OBJECT_FILES)
	$(COMPILER) -o ../bin/tetris_lin64 $(OBJECT_FILES) $(SDL_FLAGS) $(COMPILE_FLAGS)

main.o: main.cpp $(HEADER_FILES)
	$(COMPILER) -c main.cpp $(SDL_FLAGS) $(COMPILE_FLAGS)

#tetris
tetris: tetris.o
	$(COMPILER) -o tetris tetris.o 

tetris.o: tetris.cpp tetris.h
	$(COMPILER) -c tetris.cpp $(COMPILE_FLAGS)

#util
util: util.o
	$(COMPILER) -o util utilp.o 

util.o: util.cpp util.h
	$(COMPILER) -c util.cpp $(COMPILE_FLAGS)
	
#Clean (removes .o and executable)
clean:
	rm -f *.o *~ $(EXECUTABLES)
	
edit:
	$(EDITOR) main.cpp tetris.cpp tetris.h util.cpp util.h Makefile $(EDITOR_FLAGS)
