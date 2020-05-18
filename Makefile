CXX=g++
LDFLAGS=-g
LIBFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
SOURCES=main.cpp Snake.cpp NN.cpp Individual.cpp GA.cpp Logger.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))
EXECUTABLE=main_computations
INC_DIR=./include
CXXFLAGS=-c -Wall -std=c++11 -g -I$(INC_DIR)/..
BINDIR=/usr/bin

all: $(SOURCES) $(EXECUTABLE) testSnake testIndividual testNN play_individual

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBFLAGS)

testSnake: $(OBJECTS)
	$(CXX) testSnake.cpp $(LDFLAGS) Snake.o -o testSnake $(LIBFLAGS)

testIndividual: $(OBJECTS)
	$(CXX) testIndividual.cpp $(CXXFLAGS) -o testIndividual.o $(LIBFLAGS)
	$(CXX) $(LDFLAGS) testIndividual.o Individual.o Snake.o NN.o  -o testIndividual $(LIBFLAGS)

testNN: $(OBJECTS)
	$(CXX) testNN.cpp $(CXXFLAGS) -o testNN.o $(LIBFLAGS)
	$(CXX) $(LDFLAGS) testNN.o NN.o -o testNN $(LIBFLAGS)

play_individual: $(OBJECTS)
	$(CXX) play_individual.cpp $(CXXFLAGS) -o play_individual.o $(LIBFLAGS)
	$(CXX) $(LDFLAGS) play_individual.o Individual.o Logger.o Snake.o NN.o -o play_individual $(LIBFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LIBFLAGS)

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE) testSnake testIndividual testNN play_individual
