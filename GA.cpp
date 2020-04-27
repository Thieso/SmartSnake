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

// show the game on the window for individual with id id_individual
void GA::show_game(sf::RenderWindow* window, int id_individual) {
    individuals[id_individual].show_game(window, nn);
}

// select new parents from the existing population based on their fitness value
void GA::selection() {
    this->sort_population_by_fitness();
}

// sort the individuals in the current population based on their fitness values
void GA::sort_population_by_fitness() {
    // create pair array for the population
    pair<int, Individual> pairt[population_size]; 
  
    // Storing the respective array 
    // elements in pairs. 
    for (int i = 0; i < population_size; i++) { 
        pairt[i].first = current_fitness[i];
        pairt[i].second = individuals[i]; 
    } 
  
    // Sorting the pair array. 
    sort(pairt, pairt + population_size); 
      
    // Modifying original arrays 
    for (int i = 0; i < population_size; i++) { 
        current_fitness[i] = pairt[i].first; 
        individuals[i] = pairt[i].second; 
    } 
}

// apply crossover to the existing population
void GA::crossover() {

}

// apply mutations to the existing population
void GA::mutation() {

}
