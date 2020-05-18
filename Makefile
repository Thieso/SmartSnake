CC=g++
LDFLAGS=-g
LIBFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
SOURCES=main.cpp Snake.cpp NN.cpp Individual.cpp GA.cpp Logger.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main_computations
INC_DIR=./include
CFLAGS=-c -std=c++11 -g -I$(INC_DIR)/..
BINDIR=/usr/bin

all: $(SOURCES) $(EXECUTABLE) testSnake testIndividual testNN play_individual

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBFLAGS)

testSnake: $(OBJECTS)
	$(CC) testSnake.cpp $(LDFLAGS) Snake.o -o testSnake $(LIBFLAGS)

testIndividual: $(OBJECTS)
	$(CC) testIndividual.cpp $(CFLAGS) -o testIndividual.o $(LIBFLAGS)
	$(CC) $(LDFLAGS) testIndividual.o Individual.o Snake.o NN.o  -o testIndividual $(LIBFLAGS)

testNN: $(OBJECTS)
	$(CC) testNN.cpp $(CFLAGS) -o testNN.o $(LIBFLAGS)
	$(CC) $(LDFLAGS) testNN.o NN.o -o testNN $(LIBFLAGS)

play_individual: $(OBJECTS)
	$(CC) play_individual.cpp $(CFLAGS) -o play_individual.o $(LIBFLAGS)
	$(CC) $(LDFLAGS) play_individual.o Individual.o Logger.o Snake.o NN.o -o play_individual $(LIBFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ $(LIBFLAGS)

clean:
	rm *.o $(EXECUTABLE) testSnake testIndividual testNN play_individual
