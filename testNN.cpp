#include <iostream>
#include <random>
#include <eigen3/Eigen/Dense>
#include "include/NN.h"

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;
using Eigen::Map;

void display_vector(VectorXd v);

int main(){
    // parameters for neural network
    int nr_inputs = 7;
    int nr_outputs = 3;
    int nr_neurons_1 = 7;
    int nr_neurons_2 = 7;
    
    // create neural network object
    NN nn(nr_inputs, nr_outputs, nr_neurons_1, nr_neurons_2);

    // random device for random inputs
    random_device rd;
    uniform_real_distribution<float> distribution(0.0, 1.0);

    // set weights
    MatrixXd wh_1(nr_neurons_1, nr_inputs + 1);
    MatrixXd wh_2(nr_neurons_2, nr_neurons_1 + 1);
    MatrixXd wo(nr_outputs, nr_neurons_2 + 1);
    wh_1.setRandom();
    wh_2.setRandom();
    wo.setRandom();
    nn.set_weights(wh_1, wh_2, wo);

    // set inputs
    VectorXd inputs(nr_inputs);
    for (int i = 0; i < inputs.size(); i++) {
        inputs(i) = distribution(rd);
    }
    nn.set_input(inputs);
    cout << "Inputs: ";
    display_vector(inputs);

    // forward propagate
    nn.forward_propagation();

    // get outputs
    VectorXd outputs(nr_outputs);
    outputs = nn.get_output();
    cout << "Outputs: ";
    display_vector(outputs);
    cout << "Sum of outputs: " << outputs.sum() << endl;

    return 0;
}

void display_vector(VectorXd v) {
    for (int i = 0; i < v.size(); i++)
        cout << v(i) << " ";
    cout << endl;
}
