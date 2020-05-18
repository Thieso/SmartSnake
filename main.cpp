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
    float crossover_rate = 0.35; // crossover rate for genetic algorithm
    int nr_generations = 1000;  // number of generations to simulate
    GA ga(nr_inputs, nr_outputs, nr_neurons_1, nr_neurons_2, population_size, mutation_rate, crossover_rate);
    VectorXd fitness;
    int idx = 0;
    NN* nn = new NN(nr_inputs, nr_outputs, nr_neurons_1, nr_neurons_2);
    Snake* snake = new Snake();
    Logger logger;

    for (int i = 0; i < nr_generations; i++) {
        fitness = ga.evaluate_fitness(nn, snake);
        idx = display_fitness(i, fitness);
        logger.log_individual(ga.get_gene_vector(idx), i);
        ga.selection();
        ga.crossover();
        ga.mutation();
        ga.replacement();
    }
    delete nn;
    delete snake;
    return 0;
}

// displays the best fitness value in the fitness vector and the generation
// number, returns the index of the best fitness value
int display_fitness(int gen, VectorXd fitness) {
    int best_fitness = fitness.maxCoeff();
    int idx = 0;
    for (unsigned int i = 0; i < fitness.size(); i++){
        if (fitness(i) > best_fitness) {
            idx = i;
        }
    }
    //cout << gen << " " << best_fitness << " " << fitness.sum() << endl;
    cout << gen << " " << best_fitness << endl;
    return idx;
}
