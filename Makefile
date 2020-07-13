CC = g++
CFLAGS = -Wall
DEBUGFLAGS = -g -O0 
LIBS = -lSDL2 -lSDL2main -lGL
O = -O3
SRC = ./src/*.cpp
all:
	$(CC) $(SRC) $(LIBS) $(O) -o ./bin/bytepusher
debug:
	$(CC) $(SRC) $(LIBS) $(DEBUGFLAGS) -o ./bin/bytepusherDBG