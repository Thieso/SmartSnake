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
        int nr_neurons;   // number of neurons for the neural network
        VectorXd inputs;  // Vector of input values
        VectorXd outputs; // Vector of output values
        MatrixXd wh;      // matrix of weights for hidden layer
        MatrixXd wo;      // matrix of weights for output layer
    public:
        Individual(int, int, int);
        int evaluate_fitness();
        int show_game();
        VectorXd get_gene_vector_hidden();
        VectorXd get_gene_vector_output();
        void set_gene_vector_hidden(VectorXd);
        void set_gene_vector_output(VectorXd);
};
