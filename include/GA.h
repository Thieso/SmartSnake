#pragma once
#include <vector>
#include "include/Individual.h"

using namespace std; 

class GA {
    private: 
        int population_size; // number of individuals in a population
        float mutation_rate; // rate of muations occuring during variation
        NN* nn; // neural network 
        vector<Individual> individuals; // vector of individuals
        vector<int> current_fitness; // current fitness of the individuals

    public: 
        GA();
        vector<int> evaluate_fitness();
};
