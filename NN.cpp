#include "include/NN.h"

NN::NN(float nr_inputs, float nr_outputs, float nr_neurons) {
    this->bias = 1.0;
    this->nr_inputs = nr_inputs;
    this->nr_outputs = nr_outputs;
    this->nr_neurons = nr_neurons;
    // initialize all vectors and matrices with the correct sizes
    x.resize(nr_inputs);
    y.resize(nr_outputs);
    wh.resize(nr_neurons, nr_inputs + 1);
    wo.resize(nr_outputs, nr_neurons + 1);
}

// perform a forward propagation in the network with biases 
VectorXd NN::forward_propagation() {
    VectorXd a(nr_neurons);
    VectorXd a_with_bias(nr_neurons + 1);
    VectorXd x_with_bias(x.size() + 1);
    // create input vector with added bias neuron
    x_with_bias.topRows(nr_inputs) = x;
    x_with_bias(x_with_bias.size() - 1) = bias;
    // compute from input to hidden layer
    a = sigmoid(wh * x_with_bias);
    // add bias neuron
    a_with_bias.topRows(nr_neurons) = a;
    a_with_bias(a_with_bias.size() - 1) = bias;
    // compute from hidden layer to output
    y = sigmoid(wo * a_with_bias);
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
    if (this->wh.size() != wh.size() || this->wo.size() != wo.size()) {
        cout << "ERROR: Matrix dimensions do not match" << endl;
    } else {
        this->wh = wh;
        this->wo = wo;
    }
}

// set the input for the network
void NN::set_input(VectorXd input) {
    if (this->wh.size() != wh.size() || this->wo.size() != wo.size()) {
        cout << "ERROR: Vector dimensions do not match" << endl;
    } else {
        x = input;
    }
}

// get the output from the network
VectorXd NN::get_output() {
    return y;
}
