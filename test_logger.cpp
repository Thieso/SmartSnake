#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <eigen3/Eigen/Dense>
#include <cmath>
#include "include/Individual.h"
#include "include/Logger.h"

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;
using Eigen::Map;

int main(){
    // test logger
    int nr_inputs = 7;
    int nr_outputs = 3;
    int nr_neurons_1 = 9;
    int nr_neurons_2 = 15;
    Individual ind1(nr_inputs, nr_outputs, nr_neurons_1, nr_neurons_2);
    Individual ind2(nr_inputs, nr_outputs, nr_neurons_1, nr_neurons_2);
    Logger logger;

    // log gene vector of individual
    VectorXd gene_vector1 = ind1.get_gene_vector();
    logger.log_individual(gene_vector1, 0);

    // read gene vector again to compare them
    VectorXd gene_vector2;
    gene_vector2 = logger.read_individual(0, gene_vector1.size());

    // compare the gene vectors
    VectorXd d_gene_vector = gene_vector1 - gene_vector2;
    d_gene_vector = d_gene_vector.cwiseAbs();
    cout << "Difference between gene vectors: " << d_gene_vector.sum() << endl;

    return 0;
}
