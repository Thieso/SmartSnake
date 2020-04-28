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
        int population_size; // number of individuals in a population
        int nr_parents; // number of parents in each generation
        float mutation_rate; // rate of muations occuring during variation
        NN* nn; // neural network 
        vector<Individual> population; // vector of individuals making up the population
        vector<Individual> parents; // vector of individuals making up the parents
        vector<int> current_fitness; // current fitness of the individuals

    public: 
        GA();
        vector<int> evaluate_fitness();
        void show_game(sf::RenderWindow* window, int id_individual);
        void selection();
        void crossover();
        void mutation();
};
