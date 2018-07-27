CPP = g++
GNN = -std=c++14
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))


all : $(OBJ)

%.o : %.cpp
	$(CPP) -c -o $@ $< $(GNN)

clean:
	del $(OBJ)

