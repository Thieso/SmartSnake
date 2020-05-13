#include <iostream>
#include <eigen3/Eigen/Dense>
#include "include/Individual.h"

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;
using Eigen::Map;

int main(){
    // test single individual
    int nr_inputs = 6;
    int nr_outputs = 4;
    int nr_neurons = 50;
    Individual ind(nr_inputs, nr_outputs, nr_neurons);
    int f = ind.evaluate_fitness();
    cout << "Fitness: " << f << endl;
    ind.show_game();
    VectorXd gvh = ind.get_gene_vector_hidden();
    VectorXd gvo = ind.get_gene_vector_output();
    ind.set_gene_vector_hidden(gvh);
    ind.set_gene_vector_output(gvo);
    VectorXd gvh2 = ind.get_gene_vector_hidden();
    VectorXd gvo2 = ind.get_gene_vector_output();
    VectorXd dgvh = gvh-gvh2;
    VectorXd dgvo = gvo-gvo2;
    cout << dgvh.sum() << endl;
    cout << dgvo.sum() << endl;

    // test vector of individuals
    vector<Individual> ind_v;
    for (int i = 0; i < 1000; i++){
        Individual ind(nr_inputs, nr_outputs, nr_neurons);
        ind_v.push_back(ind);
    }
    for (int i = 0; i < 1000; i++){
        ind_v[i].evaluate_fitness();
    }

    return 0;
}
