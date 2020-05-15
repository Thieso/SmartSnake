#include "include/NN.h"

NN::NN(int nr_inputs, int nr_outputs, int nr_neurons_1, int nr_neurons_2) {
    this->bias = 1.0;
    this->nr_inputs = nr_inputs;
    this->nr_outputs = nr_outputs;
    this->nr_neurons_1 = nr_neurons_1;
    this->nr_neurons_2 = nr_neurons_2;
    // initialize all vectors and matrices with the correct sizes
    x.resize(nr_inputs);
    y.resize(nr_outputs);
    wh_1.resize(nr_neurons_1, nr_inputs + 1);
    wh_2.resize(nr_neurons_2, nr_neurons_1 + 1);
    wo.resize(nr_outputs, nr_neurons_2 + 1);
}

// perform a forward propagation in the network with biases 
VectorXd NN::forward_propagation() {
    VectorXd a_1(nr_neurons_1);
    VectorXd a_2(nr_neurons_2);
    VectorXd a_1_with_bias(nr_neurons_1 + 1);
    VectorXd a_2_with_bias(nr_neurons_2 + 1);
    VectorXd x_with_bias(x.size() + 1);
    // create input vector with added bias neuron
    x_with_bias.topRows(nr_inputs) = x;
    x_with_bias(x_with_bias.size() - 1) = bias;
    // compute from input to hidden layer 1
    a_1 = tanh(wh_1 * x_with_bias);
    // add bias neuron
    a_1_with_bias.topRows(nr_neurons_1) = a_1;
    a_1_with_bias(a_1_with_bias.size() - 1) = bias;
    // compute from hidden layer 1 to hidden layer 2
    a_2 = tanh(wh_2 * a_1_with_bias);
    // add bias neuron
    a_2_with_bias.topRows(nr_neurons_2) = a_2;
    a_2_with_bias(a_2_with_bias.size() - 1) = bias;
    // compute from hidden layer 2 to output
    y = softmax(wo * a_2_with_bias);
    return y;
}

// sigmoid function 
VectorXd NN::sigmoid(VectorXd x) {
    VectorXd y = x;
    for (int i = 0; i < x.size(); i++) {
        y(i) = 1 / (1 + exp(-1 * x(i)));
    }
    return y;
}

// tanh function 
VectorXd NN::tanh(VectorXd x) {
    VectorXd y = x;
    for (int i = 0; i < x.size(); i++) {
        y(i) = 2 * (1 / (1 + exp(-1 * 2 * x(i)))) - 1;
    }
    return y;
}

// softmax function 
VectorXd NN::softmax(VectorXd x) {
    VectorXd y(x.size());
    float denominator = 0;
    // max value in x
    float m = x.maxCoeff();
    // compute denominator (constant for the vector)
    for (int i = 0; i < x.size(); i++) {
        denominator += exp(x(i) - m);
    }
    // compute results
    for (int i = 0; i < x.size(); i++) {
        y(i) = exp(x(i) - m - log(denominator));
    }
    return y;
}


// set the weights inside the network
void NN::set_weights(MatrixXd wh_1, MatrixXd wh_2, MatrixXd wo) {
    if (this->wh_1.size() != wh_1.size() || this->wo.size() != wo.size() || this->wh_2.size() != wh_2.size()) {
        cout << "ERROR: Matrix dimensions do not match" << endl;
    } else {
        this->wh_1 = wh_1;
        this->wh_2 = wh_2;
        this->wo = wo;
    }
}

// set the input for the network
void NN::set_input(VectorXd input) {
    if (this->x.size() != x.size()) {
        cout << "ERROR: Vector dimensions do not match" << endl;
    } else {
        x = input;
    }
}

// get the output from the network
VectorXd NN::get_output() {
    return y;
}
