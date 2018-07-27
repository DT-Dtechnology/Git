CPP = g++
GNN = -std=c++14
TARGET = git.exe

SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))
SUBDIR = ./command ./db ./file ./hash ./struct .

all : sub cur main

sub :
	make -C ./command
	make -C ./db
	make -C ./file
	make -C ./hash
	make -C ./struct

cur : $(OBJ)

%.o : %.cpp
	$(CPP) -c -o $@ $< $(GNN)

DEP = $(foreach dir, $(SUBDIR), $(wildcard $(dir)/*.o))

main: $(DEP)
	$(CPP) -o $(TARGET) $^ $(GNU)

clean:
	make -C ./command clean
	make -C ./db clean
	make -C ./file clean
	make -C ./hash clean
	make -C ./struct clean
	del *.o