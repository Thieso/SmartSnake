#pragma once
#include <vector>
#include <math.h>
#include <numeric>

using namespace std; 

class NN {
    private: 
        int nr_inputs; // number of inputs
        int nr_outputs; // number of outputs
        int nr_neurons; // number of neurons
        float bias; // bias for neurons
        vector<float> x; // vector of input values
        vector<float> y; // vector of output values
        vector<vector<float>> wh; // matrix of weights for hidden layer
        vector<vector<float>> wo; // matrix of weights for output layer

    public: 
        NN(float, float, float);
        vector<float> forward_propagation();
        void set_weights(vector<vector<float>>, vector<vector<float>>);
        void set_input(vector<float>);
        vector<float> get_output();
        float sigmoid(float);
};
