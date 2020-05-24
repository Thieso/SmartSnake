CXX=g++
LDFLAGS=-g
LIBFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
SOURCES=Snake.cpp NN.cpp Individual.cpp GA.cpp Logger.cpp
SOURCES_MAIN=main.cpp play_individual.cpp test_snake.cpp test_individual.cpp test_nn.cpp test_logger.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))
OBJECTS_MAIN=$(subst .cpp,.o,$(SOURCES_MAIN))
EXECUTABLES=main_computations play_individual test_snake test_individual test_nn test_logger
INC_DIR=./include
CXXFLAGS=-c -Wall -std=c++11 -g -I$(INC_DIR)/..
BINDIR=/usr/bin

all: $(SOURCES) $(SOURCES_MAIN) main play_individual test_snake test_individual test_nn test_logger

main: $(OBJECTS) $(OBJECTS_MAIN)
	$(CXX) $@.cpp $(CXXFLAGS) -o $@.o $(LIBFLAGS)
	$(CXX) $(LDFLAGS) $@.o $(OBJECTS) -o $@ $(LIBFLAGS)

play_individual: $(OBJECTS) $(OBJECTS_MAIN)
	$(CXX) $@.cpp $(CXXFLAGS) -o $@.o $(LIBFLAGS)
	$(CXX) $(LDFLAGS) $@.o $(OBJECTS) -o $@ $(LIBFLAGS)

test_snake: $(OBJECTS) $(OBJECTS_MAIN)
	$(CXX) $@.cpp $(CXXFLAGS) -o $@.o $(LIBFLAGS)
	$(CXX) $(LDFLAGS) $@.o $(OBJECTS) -o $@ $(LIBFLAGS)

test_individual: $(OBJECTS) $(OBJECTS_MAIN)
	$(CXX) $@.cpp $(CXXFLAGS) -o $@.o $(LIBFLAGS)
	$(CXX) $(LDFLAGS) $@.o $(OBJECTS) -o $@ $(LIBFLAGS)

test_nn: $(OBJECTS) $(OBJECTS_MAIN)
	$(CXX) $@.cpp $(CXXFLAGS) -o $@.o $(LIBFLAGS)
	$(CXX) $(LDFLAGS) $@.o $(OBJECTS) -o $@ $(LIBFLAGS)

test_logger: $(OBJECTS) $(OBJECTS_MAIN)
	$(CXX) $@.cpp $(CXXFLAGS) -o $@.o $(LIBFLAGS)
	$(CXX) $(LDFLAGS) $@.o $(OBJECTS) -o $@ $(LIBFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LIBFLAGS)

clean:
	$(RM) *.o $(EXECUTABLES)
