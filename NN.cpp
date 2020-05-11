#include "include/NN.h"

NN::NN(float nr_inputs, float nr_outputs, float nr_neurons) {
    this->bias = 0.0;
    this->nr_inputs = nr_inputs;
    this->nr_outputs = nr_outputs;
    this->nr_neurons = nr_neurons;
    // initialize all vectors and matrices with the correct sizes
    x.resize(nr_inputs);
    y.resize(nr_outputs);
    wh.resize(nr_neurons, nr_inputs);
    wo.resize(nr_outputs, nr_neurons);
}

// perform a forward propagation in the network
VectorXd NN::forward_propagation() {
    VectorXd a(nr_neurons);
    // compute from input to hidden layer
    a = sigmoid(wh * x);
    // compute from hidden layer to output
    y = sigmoid(wo * a);
    return y;
}

// sigmoid function as activation function
VectorXd NN::sigmoid(VectorXd x) {
    VectorXd y = x;
    for (int i = 0; i < x.size(); i++) {
        y(i) = 1 / (1 + exp(-1 * x(i)));
    }
    return y;
}

// set the weights inside the network
void NN::set_weights(MatrixXd wh, MatrixXd wo) {
    this->wh = wh;
    this->wo = wo;
}

// set the input for the network
void NN::set_input(VectorXd input) {
    x = input;
}

// get the output from the network
VectorXd NN::get_output() {
    return y;
}
