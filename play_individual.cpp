#include <eigen3/Eigen/Dense>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/GA.h"
#include "include/Logger.h"

int main(){
    // set parameters for the optimization
    int nr_inputs        = 7;    // number of inputs of neural network
    int nr_outputs       = 3;    // number of outputs of neural network
    int nr_neurons_1     = 9;    // number of neurons of neural network hidden layer 1
    int nr_neurons_2     = 15;   // number of neurons of neural network hidden layer 2
    int nr_generations   = 1000; // number of generations to simulate
    VectorXd fitness;            // vector for fitness values in a generation
    VectorXd best_fitness(nr_generations); // vector for best fitness values in each generation

    // logger object 
    Logger logger;

    // snake object
    Snake* snake = new Snake();

    // neural network for steering the snake
    NN* nn = new NN(nr_inputs, nr_outputs, nr_neurons_1, nr_neurons_2);

    // window for showing the gameplay
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(800, 800), "Snake");
    // set framerate
    window->setFramerateLimit(30);

    // Individual object
    Individual* ind = new Individual(nr_inputs, nr_outputs, nr_neurons_1, nr_neurons_2);

    // compute size of gene vector
    VectorXd gene_vector = ind->get_gene_vector();
    int nr_genes = gene_vector.size();

    // main loop for evaluation
    for (int i = 0; i < nr_generations; i+=100) {
        // get an individual
        ind->set_gene_vector(logger.read_individual(i, nr_genes));

        // show game of the snake
        ind->show_game(window, nn, snake);
    }

    // close the window
    window->close();

    // delete the pointers
    delete ind;
    delete window;
    delete nn;
    delete snake;

    return 0;
}
