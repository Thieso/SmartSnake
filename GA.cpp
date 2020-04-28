#include "include/GA.h"

// constructor for genetic algorithm
GA::GA() {
    population_size = 10;
    nr_parents = 10;
    mutation_rate = 0.1;
    current_fitness.resize(population_size);
    nn = new NN(6, 4, 6);
    for (int i = 0; i < population_size; ++i) {
        Individual* ind = new Individual(6, 4, 6);
        population.push_back(*ind);
    }
}

// evaluate the fitness of all individuals in the current population
vector<int> GA::evaluate_fitness() {
    // iterate over the population and compute their fitness
    for (int i = 0; i < population_size; ++i) {
        current_fitness[i] = population[i].evaluate_fitness(nn);
    }
    return current_fitness;
}

// show the game on the window for individual with id id_individual
void GA::show_game(sf::RenderWindow* window, int id_individual) {
    population[id_individual].show_game(window, nn);
}

// select new parents from the existing population based on their fitness value
void GA::selection() {
    // compute total fitness
    float total_fitness = accumulate(current_fitness.begin(), current_fitness.end(), 0);
    // find the size of the roulette wheel part of each individual
    vector<float> roulette_wheel(population_size);
    for (int i = 0; i < population_size; i++) {
        roulette_wheel[i] = ((float) current_fitness[i]) / total_fitness;
        if (i > 0) {
            roulette_wheel[i] = roulette_wheel[i] + roulette_wheel[i - 1];
        }
    }
    // select the parents 
    float wheel_spin;
    for (int i = 0; i < nr_parents; i++) {
        // create random number between 0 and 1
        wheel_spin = ((float) (rand() % 100 + 1)) / 100.0;
        // look where the wheel stops and select the parent
        for (int j = 0; j < population_size; j++) {
            if (wheel_spin > roulette_wheel[j] && wheel_spin < roulette_wheel[j+1]) {
                parents[i] = population[j];
                break;
            }
        }
    }
}

// apply crossover to the existing population
void GA::crossover() {

}

// apply mutations to the existing population
void GA::mutation() {

}
