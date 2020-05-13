#include "include/GA.h"

// constructor for genetic algorithm
GA::GA() {
    population_size = 100;
    mutation_rate = 0.15;
    crossover_rate = 0.1;
    nr_inputs = 6;
    nr_outputs = 4;
    nr_neurons = 5;
    current_fitness.resize(population_size);
    for (int i = 0; i < population_size; ++i) {
        Individual ind(nr_inputs, nr_outputs, nr_neurons);
        population.push_back(ind);
    }
}

// descructor 
GA::~GA() {
}

// evaluate the fitness of all individuals in the current population
VectorXd GA::evaluate_fitness() {
    // iterate over the population and compute their fitness
    for (unsigned int i = 0; i < population.size(); i++) {
        current_fitness(i) = population[i].evaluate_fitness();
    }
    return current_fitness;
}

// show the game on the window for individual with id id_individual
void GA::show_game(int id_individual) {
    population[id_individual].show_game();
}

// select new parents from the existing population based on their fitness value
void GA::selection() {
    // initialize random number generator
    random_device rd;
    uniform_real_distribution<float> distribution(0.0, 1.0);
    // vector of individuals making up the parents
    vector<Individual> parents;
    // compute total fitness
    float total_fitness = current_fitness.sum();
    // find the size of the roulette wheel part of each individual
    VectorXd roulette_wheel(population_size);
    for (int i = 0; i < population_size; i++) {
        roulette_wheel(i) = ((float) current_fitness(i)) / total_fitness;
        if (i > 0) {
            roulette_wheel(i) = roulette_wheel(i) + roulette_wheel(i - 1);
        }
    }
    roulette_wheel(roulette_wheel.size() - 1) = 1;
    // select the parents 
    float wheel_spin;
    for (int i = 0; i < population_size; i++) {
        // create random number between 0 and 1
        wheel_spin = distribution(rd);
        // look where the wheel stops and select the parent
        for (int j = 0; j < population_size; j++) {
            if (wheel_spin <= roulette_wheel(j)) {
                parents.push_back(population[j]);
                break;
            }
        }
    }
    // set the current population to the parents
    population = parents;
    parents.clear();
}

// apply crossover to the existing population
void GA::crossover() {
    // initialize random number generator
    random_device rd;
    uniform_real_distribution<float> distribution(0.0, 1.0);
    // vector of parents affected by crossover
    //vector<Individual> crossover_parents;
    // vector of indices of the crossover parents
    VectorXd crossover_indicator(population_size);
    // create a random number for each parent
    // if the randowm number is below the crossover rate, the parent will
    // experience crossover and be marked as such
    float random_number;
    for (unsigned int i = 0; i < population.size(); i++) {
        // create random number between 0 and 1
        random_number = distribution(rd);
        if (random_number < crossover_rate) {
            crossover_indicator(i) = 1;
        } else {
            crossover_indicator(i) = 0;
        }
    }
    // get the indices of the marked parents
    int nr_crossover = crossover_indicator.sum();
    VectorXd crossover_idx(nr_crossover);
    int idx_i = 0;
    for (unsigned int i = 0; i < crossover_indicator.size(); i++) {
        if (crossover_indicator(i) == 1) {
            crossover_idx(idx_i) = i;
            idx_i++;
        }
    }
    // find the point of crossover and perform the crossover with the adjacent
    // parent that is marked for it
    VectorXd gene_vector_hidden1;
    VectorXd gene_vector_hidden2;
    VectorXd gene_vector_output1;
    VectorXd gene_vector_output2;
    int random_index;
    for (unsigned int i = 0; i < crossover_idx.size(); i++) {
        // get gene vectors of both parents
        gene_vector_hidden1 = population[crossover_idx(i)].get_gene_vector_hidden();
        gene_vector_output1 = population[crossover_idx(i)].get_gene_vector_output();
        if (i == crossover_idx.size() - 1) {
            gene_vector_hidden2 = population[crossover_idx(0)].get_gene_vector_hidden();
            gene_vector_output2 = population[crossover_idx(0)].get_gene_vector_output();
        } else {
            gene_vector_hidden2 = population[crossover_idx(i + 1)].get_gene_vector_hidden();
            gene_vector_output2 = population[crossover_idx(i + 1)].get_gene_vector_output();
        }
        // create random number between 1 and the size of the gene vectors minus 1
        uniform_int_distribution<int> int_distribution(1, gene_vector_hidden1.size() + gene_vector_output1.size() - 3);
        random_index = int_distribution(rd);
        // perform crossover on the gene vectors depending on the random index 
        if (random_index < gene_vector_hidden1.size()) {
            gene_vector_hidden1.bottomRows(gene_vector_hidden1.size() - random_index) = gene_vector_hidden2.bottomRows(gene_vector_hidden1.size() - random_index);
            gene_vector_output1 = gene_vector_output2;
        } else {
            gene_vector_output1.bottomRows(random_index - gene_vector_hidden1.size()) = gene_vector_output2.bottomRows(random_index - gene_vector_hidden1.size());
        }
        // set gene vector for the individual
        population[crossover_idx(i)].set_gene_vector_hidden(gene_vector_hidden1);
        population[crossover_idx(i)].set_gene_vector_output(gene_vector_output1);
    }
}

// apply mutations to the existing population
void GA::mutation() {
    random_device rd;
    uniform_real_distribution<float> distribution(0.0, 1.0);
    uniform_real_distribution<float> mutation_dist(-0.05, 0.05);
    // initialize random number generator
    srand(time(NULL));
    // iterate over all gene vector and mutate them if necessary
    VectorXd gene_vector_hidden;
    VectorXd gene_vector_output;
    float random_number;
    for (int i = 0; i < population_size; i++) {
        gene_vector_hidden = population[i].get_gene_vector_hidden();
        gene_vector_output = population[i].get_gene_vector_output();
        for (int j = 0; j < gene_vector_hidden.size(); j++) {
            // create random number between 0 and 1
            random_number = distribution(rd);
            // if random number smaller than mutation rate, mutate the gene
            if (random_number < mutation_rate) {
                gene_vector_hidden[j] += mutation_dist(rd);
            }
        }
        for (int j = 0; j < gene_vector_output.size(); j++) {
            // create random number between 0 and 1
            random_number = distribution(rd);
            // if random number smaller than mutation rate, mutate the gene
            if (random_number < mutation_rate) {
                gene_vector_output[j] += mutation_dist(rd);
            }
        }
        // set mutated gene vector
        population[i].set_gene_vector_hidden(gene_vector_hidden);
        population[i].set_gene_vector_output(gene_vector_output);
    }
}
