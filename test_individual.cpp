#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <eigen3/Eigen/Dense>
#include "include/Individual.h"

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;
using Eigen::Map;

int main(){
    // test single individual
    int nr_inputs = 7;
    int nr_outputs = 3;
    int nr_neurons_1 = 7;
    int nr_neurons_2 = 7;
    Individual ind(nr_inputs, nr_outputs, nr_neurons_1, nr_neurons_2);
    NN* nn = new NN(nr_inputs, nr_outputs, nr_neurons_1, nr_neurons_2);
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(600, 600), "Snake");
    Snake* snake = new Snake();
    int f = ind.evaluate_fitness(nn, snake);
    cout << "Fitness: " << f << endl;
    ind.show_game(window, nn, snake, 0);
    VectorXd gv = ind.get_gene_vector();
    ind.set_gene_vector(gv);
    VectorXd gv2 = ind.get_gene_vector();
    VectorXd dgv = gv - gv2;
    cout << dgv.sum() << endl;

    delete nn;
    delete window;
    return 0;
}
