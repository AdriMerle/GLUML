CC = g++
ECHO = echo
CFLAGS =  -c -g -ansi -pedantic -Wall -std=c++11 
MAPFLAG = -DMAP
SRC = $(wildcard *.cpp)
HDR = $(wildcard *.h)
OBJ = $(SRC:.cpp=.o)
EXE = main

# all: $(SRC) $(OBJ) $(EXE)

all : $(EXE) $(OBJ)
	./main

$(EXE): $(OBJ)
	@echo "\n\e[0;35m\033[1mEdition des liens\033[0m"
	$(CC) $(CLAGS) $^ -o $@

%.o : %.cpp $(HDR)
	@echo "\e[1;33m\033[1mCompilation de" $< "\033[0m"
	$(CC)   $(CFLAGS) $< -o $@ $(MAPFLAG)

clean:
	rm *.o $(EXE)

tests : tests.cpp
	g++ -o tests tests.cpp
	./tests