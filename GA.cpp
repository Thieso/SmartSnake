#include "include/GA.h"

// constructor for genetic algorithm
GA::GA(int nr_inputs, int nr_outputs, int nr_neurons_1, int nr_neurons_2, int population_size, float mutation_rate, float crossover_rate) {
    this->population_size = population_size;
    this->nr_parents = population_size/2;
    this->mutation_rate = mutation_rate;
    this->crossover_rate = crossover_rate;
    this->nr_inputs = nr_inputs;
    this->nr_outputs = nr_outputs;
    this->nr_neurons_1 = nr_neurons_1;
    this->nr_neurons_2 = nr_neurons_2;
    current_fitness.resize(population_size);
    population.assign(population_size, Individual(nr_inputs, nr_outputs, nr_neurons_1, nr_neurons_2));
}

// descructor 
GA::~GA() {
}

// evaluate the fitness of all individuals in the current population
VectorXd GA::evaluate_fitness(NN* nn, Snake* snake) {
    // iterate over the population and compute their fitness
    VectorXd fitness_ind(10);
    for (unsigned int i = 0; i < population.size(); i++) {
        for (int j = 0; j < 10; j++)
            fitness_ind(j) = population[i].evaluate_fitness(nn, snake);
        current_fitness(i) = fitness_ind.mean();
    }
    return current_fitness;
}

// show the game on the window for individual with id id_individual
void GA::show_game(sf::RenderWindow* window, NN* nn, Snake* snake, int id_individual, int generation) {
    population[id_individual].show_game(window, nn, snake, generation);
}

// select new parents using roulette wheel selection
void GA::selection_roulette_wheel() {
    parents.clear();
    children.clear();
    // initialize random number generator
    random_device rd;
    uniform_real_distribution<float> distribution(0.0, 1.0);
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
    for (int i = 0; i < nr_parents; i++) {
        // create random number between 0 and 1
        wheel_spin = distribution(rd);
        // look where the wheel stops and select the parent
        for (int j = 0; j < population_size; j++) {
            if (wheel_spin <= roulette_wheel(j)) {
                parents.push_back(population[j]);
                children.push_back(population[j]);
                break;
            }
        }
    }
}

// select parents simply by choosing the fittest ones
void GA::selection_fittest() {
    parents.clear();
    children.clear();
    // find the size of the roulette wheel part of each individual
    VectorXd sorted_fitness(current_fitness);
    std::sort(sorted_fitness.data(),sorted_fitness.data()+sorted_fitness.size());
    // iterate over parents and find the fittest
    for (int i = 0; i < nr_parents; i++) {
        // look where the wheel stops and select the parent
        for (int j = 0; j < population_size; j++) {
            if (current_fitness(j) == sorted_fitness(i)) {
                parents.push_back(population[j]);
                children.push_back(population[j]);
                break;
            }
        }
    }
}

// apply crossover to the existing population
void GA::crossover() {
    // initialize random number generator
    random_device rd;
    uniform_real_distribution<float> distribution(0.0, 1.0);
    // vector of parents affected by crossover
    //vector<Individual> crossover_parents;
    // vector of indices of the crossover parents
    VectorXd crossover_indicator(nr_parents);
    // create a random number for each parent
    // if the randowm number is below the crossover rate, the parent will
    // experience crossover and be marked as such
    float random_number;
    for (int i = 0; i < nr_parents; i++) {
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
    VectorXd gene_vector_1;
    VectorXd gene_vector_2;
    int random_index;
    for (unsigned int i = 0; i < crossover_idx.size(); i++) {
        // get gene vectors of both parents
        gene_vector_1 = children[crossover_idx(i)].get_gene_vector();
        if (i == crossover_idx.size() - 1) {
            gene_vector_2 = children[crossover_idx(0)].get_gene_vector();
        } else {
            gene_vector_2 = children[crossover_idx(i + 1)].get_gene_vector();
        }
        // create random number between 1 and the size of the gene vectors minus 1
        uniform_int_distribution<int> int_distribution(1, gene_vector_1.size() - 2);
        random_index = int_distribution(rd);
        // perform crossover on the gene vectors depending on the random index 
        gene_vector_1.bottomRows(random_index) = gene_vector_2.bottomRows(random_index);
        // set gene vector for the individual
        children[crossover_idx(i)].set_gene_vector(gene_vector_1);
    }
}

// apply mutations to the existing population
void GA::mutation() {
    // initialize random number generator
    random_device rd;
    uniform_real_distribution<float> distribution(0.0, 1.0);
    uniform_real_distribution<float> mutation_dist(-0.10, 0.10);
    // iterate over all gene vector and mutate them if necessary
    VectorXd gene_vector;
    float random_number;
    for (int i = 0; i < nr_parents; i++) {
        gene_vector= children[i].get_gene_vector();
        for (int j = 0; j < gene_vector.size(); j++) {
            // create random number between 0 and 1
            random_number = distribution(rd);
            // if random number smaller than mutation rate, mutate the gene
            if (random_number < mutation_rate) {
                gene_vector[j] += mutation_dist(rd);
            }
        }
        // set mutated gene vector
        children[i].set_gene_vector(gene_vector);
    }
}

// replace current population with parents and children
void GA::replacement() {
    population.clear();
    for (unsigned int i = 0; i < parents.size(); i++) {
        //population.push_back(parents[i]);
        population.push_back(children[i]);
    }
}

// get gene vector of specified individual
VectorXd GA::get_gene_vector(int idx) {
    return population[idx].get_gene_vector();
}
