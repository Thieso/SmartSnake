#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/Snake.h"
#include "include/Food.h"
#include "include/NN.h"

using namespace std;

class Individual {
    private:
        int fitness; // fitness value of the individual
        vector<vector<float>> wh; // matrix of weights for hidden layer
        vector<vector<float>> wo; // matrix of weights for output layer
    public:
        Individual();
        int evaluate_fitness(NN);
};
