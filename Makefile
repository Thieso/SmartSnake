CC=g++
LDFLAGS=-g
LIBFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
SOURCES=main.cpp Snake.cpp NN.cpp Individual.cpp GA.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main
INC_DIR=./include
CFLAGS=-c -Wall -std=c++11 -g -I$(INC_DIR)/..
BINDIR=/usr/bin

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBFLAGS)

testSnake: $(OBJECTS)
	$(CC) testSnake.cpp $(LDFLAGS) Snake.o -o testSnake $(LIBFLAGS)

testIndividual: $(OBJECTS)
	$(CC) testIndividual.cpp $(LDFLAGS) Individual.o -o testIndividual $(LIBFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ $(LIBFLAGS)

clean:
	rm *.o $(EXECUTABLE)

install:
	#install -s $(EXECUTABLE) $(BINDIR)
	sudo cp -u $(EXECUTABLE) $(BINDIR)
uninstall:
	sudo rm $(BINDIR)/$(EXECUTABLE)
