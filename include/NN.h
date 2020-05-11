#pragma once
#include <eigen3/Eigen/Dense>
#include <vector>
#include <math.h>
#include <numeric>

using namespace std; 
using Eigen::MatrixXd;
using Eigen::VectorXd;

class NN {
    private: 
        int nr_inputs; // number of inputs
        int nr_outputs; // number of outputs
        int nr_neurons; // number of neurons
        float bias; // bias for neurons
        VectorXd x; // vector of input values
        VectorXd y; // vector of output values
        MatrixXd wh; // matrix of weights for hidden layer
        MatrixXd wo; // matrix of weights for output layer

    public: 
        NN(float, float, float);
        VectorXd forward_propagation();
        void set_weights(MatrixXd, MatrixXd);
        void set_input(VectorXd);
        VectorXd get_output();
        VectorXd sigmoid(VectorXd);
};
