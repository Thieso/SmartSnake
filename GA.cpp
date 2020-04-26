#include "include/GA.h"

// constructor for genetic algorithm
GA::GA() {
    population_size = 1;
    mutation_rate = 0.1;
    current_fitness.resize(population_size);
    nn = new NN(10, 4, 10);
    for (int i = 0; i < population_size; ++i) {
        Individual* ind = new Individual(10, 4, 10);
        individuals.push_back(*ind);
    }
}

// evaluate the fitness of all individuals in the current population
vector<int> GA::evaluate_fitness() {
    // iterate over the individuals and compute their fitness
    for (int i = 0; i < population_size; ++i) {
        current_fitness[i] = individuals[i].evaluate_fitness(nn);
    }
    return current_fitness;
}
