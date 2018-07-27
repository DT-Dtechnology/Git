CPP = g++
CC = gcc
GNN = -std=c++14
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))


all : $(OBJ) sqlite3.o

%.o : %.cpp
	$(CPP) -c -o $@ $< $(GNN)

sqlite3.o : sqlite3.c
	$(CC) -c -o $@ $<

clean:
	del $(OBJ) sqlite3.o

