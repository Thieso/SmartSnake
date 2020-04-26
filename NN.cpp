#include "include/NN.h"

NN::NN() {
    int nr_inputs = 1;
    int nr_outputs = 1;
    int nr_neurons = 3;
    NN(nr_inputs, nr_outputs, nr_neurons);
}

NN::NN(float nr_inputs, float nr_outputs, float nr_neurons) {
    this->bias = 1;
    this->nr_inputs = nr_inputs;
    this->nr_outputs = nr_outputs;
    this->nr_neurons = nr_neurons;
    // initialize all vectors and matrices with the correct sizes
    this->x.resize(this->nr_inputs);
    this->y.resize(this->nr_outputs);
    this->wh.resize(this->nr_neurons);
    for (int i = 0; i < nr_neurons; ++i) {
        wh[i].resize(this->nr_inputs);
    }
    this->wo.resize(this->nr_outputs);
    for (int i = 0; i < nr_neurons; ++i) {
        wo[i].resize(this->nr_neurons);
    }
    // randomize the weights
    default_random_engine generator;
    uniform_real_distribution<double> distribution(0.0, 1.0);
    for (int i = 0; i < nr_neurons; ++i) {
        for (int j = 0; j < nr_inputs; ++j) {
            wh[i][j] = distribution(generator);
        }
    }
    for (int i = 0; i < nr_outputs; ++i) {
        for (int j = 0; j < nr_neurons; ++j) {
            wh[i][j] = distribution(generator);
        }
    }
}


vector<float> NN::forward_propagation() {
    vector<float> a(nr_neurons);
    // compute from input to hidden layer
    for (int i = 0; i < nr_neurons; ++i) {
        a[i] = inner_product(wh[i].begin(), wh[i].end(), x.begin(), 0) + bias;
        a[i] = sigmoid(a[i]);
    }
    // compute from hidden layer to output
    for (int i = 0; i < nr_outputs; ++i) {
        this->y[i] = inner_product(wo[i].begin(), wo[i].end(), a.begin(), 0) + bias;
        this->y[i] = sigmoid(this->y[i]);
    }
    return this->y;
}

float NN::sigmoid(float x) {
    double y = 1 / (1 + exp(-x));
    return y;
}
