#pragma once
#include <eigen3/Eigen/Dense>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "include/Snake.h"
#include "include/NN.h"

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;
using Eigen::Map;

class Individual {
    private:
        int fitness; // fitness value of the individual
        MatrixXd wh; // matrix of weights for hidden layer
        MatrixXd wo; // matrix of weights for output layer
    public:
        Individual(int, int, int);
        int evaluate_fitness(int, int, int);
        int show_game(int, int, int);
        VectorXd get_gene_vector_hidden();
        VectorXd get_gene_vector_output();
        void set_gene_vector_hidden(VectorXd);
        void set_gene_vector_output(VectorXd);
};
