#pragma once
#include <eigen3/Eigen/Dense>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include <numeric>
#include <time.h>
#include "include/Individual.h"

using namespace std; 
using Eigen::MatrixXd;
using Eigen::VectorXd;

class GA {
    private: 
        int population_size;                  // number of individuals in a population
        float mutation_rate;                  // rate of muations occuring during variation
        float crossover_rate;                 // rate of crossover occuring during variation
        int nr_inputs;                        // number of inputs for neural network
        int nr_outputs;                       // number of outputs for neural network
        int nr_neurons;                       // number of neurons for neural network
        vector<Individual> population;        // vector of individuals making up the population
        VectorXd current_fitness;          // current fitness of the individuals

    public: 
        GA();
        ~GA();
        VectorXd evaluate_fitness();
        void show_game(int id_individual);
        void selection();
        void crossover();
        void mutation();
};
