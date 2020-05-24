#include <eigen3/Eigen/Dense>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <iostream>
#include "include/GA.h"
#include "include/Logger.h"

int main(int argc, char* argv[]){
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <generation number of individual to show>" << endl;
        return 1;
    }

    // get generation number from command line arguments
    int generation_number = stoi(argv[1]);

    // set parameters for the optimization
    int nr_inputs        = 9;    // number of inputs of neural network
    int nr_outputs       = 3;    // number of outputs of neural network
    int nr_neurons_1     = 11;   // number of neurons of neural network hidden layer 1
    int nr_neurons_2     = 15;   // number of neurons of neural network hidden layer 2
    VectorXd fitness;            // vector for fitness values in a generation

    // logger object 
    Logger logger;

    // snake object
    Snake* snake = new Snake();

    // neural network for steering the snake
    NN* nn = new NN(nr_inputs, nr_outputs, nr_neurons_1, nr_neurons_2);

    // window for showing the gameplay
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(600, 600), "Snake");
    // set framerate
    window->setFramerateLimit(30);

    // Individual object
    Individual* ind = new Individual(nr_inputs, nr_outputs, nr_neurons_1, nr_neurons_2);

    // compute size of gene vector
    VectorXd gene_vector = ind->get_gene_vector();
    int nr_genes = gene_vector.size();

    // set gene vector
    ind->set_gene_vector(logger.read_individual(generation_number, nr_genes));

    // compute fitness value
    int nr_evaluation = 100;
    VectorXd v_fitness(nr_evaluation);
    for (int i = 0; i < nr_evaluation; i++) {
        v_fitness(i) = ind->evaluate_fitness(nn, snake);
    }
    // display max mean and min fitness
    cout << "Max Fitness: " << v_fitness.maxCoeff() << endl;
    cout << "Min Fitness: " << v_fitness.minCoeff() << endl;
    cout << "Mean Fitness: " << v_fitness.mean() << endl;

    // wait for some seconds to start the game
    for (int i = 10; i >= 0; i--) {
        cout << "Starting game in " << i << endl;
        usleep(1000000);
    }

    // show game of the snake
    ind->show_game(window, nn, snake, generation_number+1);

    cout << "Game finished. Close game window" << endl;
    sf::Event event;
    while(window->isOpen()) {
        while (window->pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window->close();
        }
    }

    // delete the pointers
    delete ind;
    delete window;
    delete nn;
    delete snake;

    return 0;
}
