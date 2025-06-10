#to build assignment 
#  $ cd assignment_dir
#  $ make
# executable binaraies should be put is assignment_dir/binaraies
#to run the game , you need to cd bin, and type./sfmlgame
#
#to complile and run in one command
#
#define which compiler to use

CXX :=g++
OUTPUT:=sfmlgame

#if you need to manually specify you sfml install dir do so here
SFML_DIR:= .

#compiler adn linker files
CXX_FLAGS:= -O3 -std=c++17
INCLUDES:= -I./src -I$(SFML_DIR)/INCLUDES
LDFLAGS:= -O3 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -L$(SFML_DIR)/lib

#the source files form the ecs game engine

SRC_FILES:=$(wildcard src/*.cpp)
OBJ_FILES:=$(SRC_FILES:.cpp=.o)

#all of these targets will be made if you jest make

all:$(OUTPUT)

