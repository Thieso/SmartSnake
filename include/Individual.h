#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "include/Snake.h"
#include "include/NN.h"

using namespace std;

class Individual {
    private:
        int fitness; // fitness value of the individual
        vector<vector<float>> wh; // matrix of weights for hidden layer
        vector<vector<float>> wo; // matrix of weights for output layer
    public:
        Individual(int, int, int);
        int evaluate_fitness(int, int, int);
        int show_game(int, int, int);
        vector<vector<float>> get_hidden_weights();
        vector<vector<float>> get_output_weights();
        vector<float> get_gene_vector();
        void set_gene_vector(vector<float>);
};
