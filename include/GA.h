#pragma once
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include <numeric>
#include "include/Individual.h"

using namespace std; 

class GA {
    private: 
        int population_size;                  // number of individuals in a population
        int nr_parents;                       // number of parents in each generation
        float mutation_rate;                  // rate of muations occuring during variation
        float crossover_rate;                 // rate of crossover occuring during variation
        int nr_inputs;                        // number of inputs for neural network
        int nr_outputs;                       // number of outputs for neural network
        int nr_neurons;                       // number of neurons for neural network
        vector<Individual> population;        // vector of individuals making up the population
        vector<Individual> parents;           // vector of individuals making up the parents
        vector<Individual> crossover_parents; // vector of individuals marked for crossover
        vector<int> crossover_idx;            // vector of indices of the crossover parents
        vector<int> current_fitness;          // current fitness of the individuals

    public: 
        GA();
        ~GA();
        vector<int> evaluate_fitness();
        void show_game(int id_individual);
        void selection();
        void crossover();
        void mutation();
        void replacement();
};
