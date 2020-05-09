CC=g++
LDFLAGS=-g
LIBFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
SOURCES=main.cpp Snake.cpp NN.cpp Individual.cpp GA.cpp
TEST=testSnake.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main
INC_DIR=./include
CFLAGS=-c -Wall -std=c++11 -g -I$(INC_DIR)/..
#CFLAGS=-c -std=c++11 -g -I$(INC_DIR)/..
BINDIR=/usr/bin

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBFLAGS)

test: $(OBJECTS)
	$(CC) $(TEST) $(LDFLAGS) Snake.o -o test $(LIBFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ $(LIBFLAGS)

clean:
	rm *.o $(EXECUTABLE)

install:
	#install -s $(EXECUTABLE) $(BINDIR)
	sudo cp -u $(EXECUTABLE) $(BINDIR)
uninstall:
	sudo rm $(BINDIR)/$(EXECUTABLE)
