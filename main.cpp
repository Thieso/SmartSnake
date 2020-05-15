#include <eigen3/Eigen/Dense>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/GA.h"
#include "include/Individual.h"

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;

int display_fitness(int, VectorXd);

int main(){
    int nr_inputs = 6;          // number of inputs of neural network
    int nr_outputs = 3;         // number of outputs of neural network
    int nr_neurons_1 = 9;         // number of neurons of neural network hidden layer 1
    int nr_neurons_2 = 15;         // number of neurons of neural network hidden layer 2
    int population_size = 100;  // number of individuals in population
    float mutation_rate = 0.15; // mutation rate for genetic algorithm
    float crossover_rate = 0.1; // crossover rate for genetic algorithm
    int nr_generations = 100;  // number of generations to simulate
    GA ga(nr_inputs, nr_outputs, nr_neurons_1, nr_neurons_2, population_size, mutation_rate, crossover_rate);
    VectorXd fitness;
    int idx = 0;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(500, 500), "Snake");
    NN* nn = new NN(nr_inputs, nr_outputs, nr_neurons_1, nr_neurons_2);

    for (int i = 0; i < nr_generations; i++) {
        fitness = ga.evaluate_fitness(nn);
        idx = display_fitness(i, fitness);
        //if (i == nr_generations - 1) {
            //while (true) {
                //ga.show_game(window, nn, idx);
            //}
        //}
        ga.selection();
        ga.crossover();
        ga.mutation();
    }
    window->close();
    delete window;
    delete nn;
    return 0;
}

// displays the best fitness value in the fitness vector and the generation
// number, returns the index of the best fitness value
int display_fitness(int gen, VectorXd fitness) {
    int best_fitness = 1;
    int idx = 0;
    for (unsigned int i = 0; i < fitness.size(); i++){
        if (fitness(i) > best_fitness) {
            best_fitness = fitness(i);
            idx = i;
        }
    }
    //cout << gen << " " << best_fitness << " " << fitness.sum() << endl;
    cout << gen << " " << best_fitness << endl;
    return idx;
}
