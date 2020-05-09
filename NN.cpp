#include "include/NN.h"

NN::NN(float nr_inputs, float nr_outputs, float nr_neurons) {
    this->bias = 0.0;
    this->nr_inputs = nr_inputs;
    this->nr_outputs = nr_outputs;
    this->nr_neurons = nr_neurons;
    // initialize all vectors and matrices with the correct sizes
    wh.assign(nr_neurons, vector<float>(nr_inputs));
    wo.assign(nr_outputs, vector<float>(nr_neurons));
}

// perform a forward propagation in the network
vector<float> NN::forward_propagation() {
    y.clear();
    vector<float> a(nr_neurons);
    // compute from input to hidden layer
    for (int i = 0; i < nr_neurons; ++i) {
        a[i] = inner_product(wh[i].begin(), wh[i].end(), x.begin(), 0) + bias;
        a[i] = sigmoid(a[i]);
    }
    // compute from hidden layer to output
    for (int i = 0; i < nr_outputs; ++i) {
        y.push_back(sigmoid(inner_product(wo[i].begin(), wo[i].end(), a.begin(), 0) + bias));
    }
    return y;
}

// sigmoid function as activation function
float NN::sigmoid(float x) {
    double y = 1 / (1 + exp(-x));
    return y;
}

// set the weights inside the network
void NN::set_weights(vector<vector<float>> wh, vector<vector<float>> wo) {
    this->wh = wh;
    this->wo = wo;
}

// set the input for the network
void NN::set_input(vector<float> input) {
    x.clear();
    for (int i = 0; i < input.size(); i++)
        x.push_back(input[i]);
}

// get the output from the network
vector<float> NN::get_output() {
    return y;
}
