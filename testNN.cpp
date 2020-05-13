#include <iostream>
#include <eigen3/Eigen/Dense>
#include "include/NN.h"

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;
using Eigen::Map;

void display_vector(VectorXd v);

int main(){
    // test single individual
    int nr_inputs = 6;
    int nr_outputs = 4;
    int nr_neurons = 5;
    NN nn(nr_inputs, nr_outputs, nr_neurons);

    // set weights
    MatrixXd wh(nr_neurons, nr_inputs + 1);
    MatrixXd wo(nr_outputs, nr_neurons + 1);
    wh.setRandom();
    wo.setRandom();
    nn.set_weights(wh, wo);

    // set inputs
    VectorXd inputs(nr_inputs);
    inputs.setRandom();
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

    return 0;
}

void display_vector(VectorXd v) {
    for (int i = 0; i < v.size(); i++)
        cout << v(i) << " ";
    cout << endl;
}
