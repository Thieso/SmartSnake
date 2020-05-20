#include <eigen3/Eigen/Dense>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/GA.h"
#include "include/Individual.h"
#include "include/Logger.h"

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;

int display_fitness(int, VectorXd);

int main(){
    int nr_inputs = 7;          // number of inputs of neural network
    int nr_outputs = 3;         // number of outputs of neural network
    int nr_neurons_1 = 9;         // number of neurons of neural network hidden layer 1
    int nr_neurons_2 = 15;         // number of neurons of neural network hidden layer 2
    int population_size = 100;  // number of individuals in population
    float mutation_rate = 0.15; // mutation rate for genetic algorithm
    float crossover_rate = 0.5; // crossover rate for genetic algorithm
    int nr_generations = 2000;  // number of generations to simulate
    GA ga(nr_inputs, nr_outputs, nr_neurons_1, nr_neurons_2, population_size, mutation_rate, crossover_rate);
    VectorXd fitness;
    VectorXd best_fitness(nr_generations);
    VectorXd sum_fitness(nr_generations);
    int idx = 0;
    NN* nn = new NN(nr_inputs, nr_outputs, nr_neurons_1, nr_neurons_2);
    Snake* snake = new Snake();
    Logger logger;

    // main loop for optimization
    for (int i = 0; i < nr_generations; i++) {
        // evaluate fitness of individuals
        fitness = ga.evaluate_fitness(nn, snake);
        idx = display_fitness(i, fitness);
        best_fitness(i) = fitness.maxCoeff();
        sum_fitness(i) = fitness.sum();
        // log individual gene vector to file
        logger.log_individual(ga.get_gene_vector(idx), i);
        // do genetic algorithm iteration
        ga.selection();
        ga.crossover();
        ga.mutation();
        ga.replacement();
    }

    // log fitness vector
    logger.log_fitness_vector(best_fitness, sum_fitness);

    delete nn;
    delete snake;
    return 0;
}

// displays the best fitness value in the fitness vector and the generation
// number, returns the index of the best fitness value
int display_fitness(int gen, VectorXd fitness) {
    int best_fitness = -1000;
    int idx = 0;
    for (unsigned int i = 0; i < fitness.size(); i++){
        if (fitness(i) > best_fitness) {
            idx = i;
            best_fitness = fitness(i);
        }
    }
    cout << "Generation: " << gen << " Max Fitness: " << best_fitness << " Sum of Fitness: " << fitness.sum() <<  endl;
    return idx;
}
