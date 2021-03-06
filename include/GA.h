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
        int nr_parents;                  // number of parents for reproduction
        float mutation_rate;                  // rate of muations occuring during variation
        float crossover_rate;                 // rate of crossover occuring during variation
        int nr_inputs;                        // number of inputs for neural network
        int nr_outputs;                       // number of outputs for neural network
        int nr_neurons_1;                       // number of neurons for neural network hidden layer 1
        int nr_neurons_2;                       // number of neurons for neural network hidden layer 2
        vector<Individual> population;        // vector of individuals making up the population
        vector<Individual> parents;        // vector of individuals making up the parents
        vector<Individual> children;        // vector of individuals making up the children
        VectorXd current_fitness;          // current fitness of the individuals

    public: 
        GA(int, int, int, int, int, float, float);
        ~GA();
        VectorXd evaluate_fitness(NN*, Snake*);
        void show_game(sf::RenderWindow*, NN*, Snake*, int, int);
        void selection_roulette_wheel();
        void selection_fittest();
        void crossover();
        void mutation();
        void replacement();
        VectorXd get_gene_vector(int);
};
