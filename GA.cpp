#include "include/GA.h"

// constructor for genetic algorithm
GA::GA() {
    population_size = 1000;
    nr_parents = 1000;
    mutation_rate = 0.1;
    crossover_rate = 0.2;
    nr_inputs = 6;
    nr_outputs = 4;
    nr_neurons = 6;
    current_fitness.resize(population_size);
    for (int i = 0; i < population_size; ++i) {
        Individual ind(nr_inputs, nr_outputs, nr_neurons);
        population.push_back(ind);
        parents.push_back(ind);
    }
}

// descructor 
GA::~GA() {
}

// evaluate the fitness of all individuals in the current population
vector<int> GA::evaluate_fitness() {
    current_fitness.clear();
    // iterate over the population and compute their fitness
    for (int i = 0; i < population.size(); i++) {
        current_fitness.push_back(population[i].evaluate_fitness(nr_inputs, nr_outputs, nr_neurons));
    }
    return current_fitness;
}

// show the game on the window for individual with id id_individual
void GA::show_game(int id_individual) {
    population[id_individual].show_game(nr_inputs, nr_outputs, nr_neurons);
}

// select new parents from the existing population based on their fitness value
void GA::selection() {
    parents.clear();
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
    roulette_wheel[roulette_wheel.size() - 1] = 1;
    // select the parents 
    float wheel_spin;
    for (int i = 0; i < nr_parents; i++) {
        // create random number between 0 and 1
        wheel_spin = ((float) (rand() % 100 + 1)) / 100.0;
        // look where the wheel stops and select the parent
        for (int j = 0; j < population_size; j++) {
            if (wheel_spin <= roulette_wheel[j]) {
                parents.push_back(population[j]);
                break;
            }
        }
    }
}

// apply crossover to the existing population
void GA::crossover() {
    crossover_parents.clear();
    crossover_idx.clear();
    // create a random number for each parent
    // if the randowm number is below the crossover rate, the parent will
    // experience crossover
    float random_number;
    for (int i = 0; i < parents.size(); i++) {
        // create random number between 0 and 1
        random_number = ((float) (rand() % 100 + 1)) / 100.0;
        if (random_number < crossover_rate) {
            crossover_parents.push_back(parents[i]);
            crossover_idx.push_back(i);
        }
    }
    // find the point of crossover and perform the crossover with the adjacent
    // parent that is marked for it
    vector<float> gene_vector1;
    vector<float> gene_vector2;
    int random_index;
    for (int i = 0; i < crossover_parents.size(); i++) {
        // get gene vectors of both parents
        gene_vector1 = crossover_parents[i].get_gene_vector();
        if (i < crossover_parents.size() - 1)
            gene_vector2 = crossover_parents[i + 1].get_gene_vector();
        else
            gene_vector2 = crossover_parents[0].get_gene_vector();
        // create random number between 1 and the size of the gene vector minus 1
        random_index = rand() % (gene_vector1.size() - 2) + 1;
        // perform crossover on the gene vectors
        for (int j = random_index; j < gene_vector1.size(); j++) {
            gene_vector1[j] = gene_vector2[j];
        }
        // set gene vector for the individual
        crossover_parents[i].set_gene_vector(gene_vector1);
    }

    // insert the crossover parents back into the parents array
    for (int i = 0; i < crossover_parents.size(); i++) {
        parents[crossover_idx[i]] = crossover_parents[i];
    }
}

// apply mutations to the existing population
void GA::mutation() {
    // iterate over all gene vector and mutate them if necessary
    vector<float> gene_vector;
    float random_number;
    for (int i = 0; i < nr_parents; i++) {
        gene_vector = parents[i].get_gene_vector();
        for (int j = 0; j < gene_vector.size(); j++) {
            // create random number between 0 and 1
            random_number = ((float) (rand() % 100 + 1)) / 100.0;
            // if random number smaller than mutation rate, mutate the gene
            if (random_number < mutation_rate) {
                gene_vector[j] += (float) (rand() % 5 + 1) / 100.0 - 0.1;
            }
        }
        // set mutated gene vector
        parents[i].set_gene_vector(gene_vector);
    }
}

// replace the current population by the parent vector
void GA::replacement() {
    //population = parents;
    population.clear();
    for (int i = 0; i < population_size; i++) {
        population.push_back(parents[i]);
    }
}
