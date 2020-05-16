#pragma once
#include <eigen3/Eigen/Dense>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <time.h>
#include "include/Snake.h"
#include "include/NN.h"

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;
using Eigen::Map;

class Individual {
    private:
        int fitness;      // fitness value of the individual
        int nr_inputs;    // number of inputs for the neural network
        int nr_outputs;   // number of outputs for the neural network
        int nr_neurons_1; // number of neurons for the neural network hidden layer 1
        int nr_neurons_2; // number of neurons for the neural network hidden layer 2
        int maxSteps;     // maximum number of steps the snake can do
        VectorXd inputs;  // Vector of input values
        VectorXd outputs; // Vector of output values
        MatrixXd wh_1;    // matrix of weights for hidden layer 1
        MatrixXd wh_2;    // matrix of weights for hidden layer 2
        MatrixXd wo;      // matrix of weights for output layer
    public:
        Individual(int, int, int, int);
        ~Individual();
        Individual(Individual&&);
        Individual(const Individual&);
        int evaluate_fitness(NN*, Snake*);
        void show_game(sf::RenderWindow*, NN*, Snake*);
        VectorXd get_gene_vector();
        void set_gene_vector(VectorXd);
        Individual& operator=(Individual&&);
        Individual& operator=(const Individual&);
};
