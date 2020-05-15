#pragma once
#include <eigen3/Eigen/Dense>
#include <vector>
#include <iostream>
#include <math.h>
#include <numeric>

using namespace std; 
using Eigen::MatrixXd;
using Eigen::VectorXd;

class NN {
    private: 
        int nr_inputs; // number of inputs
        int nr_outputs; // number of outputs
        int nr_neurons_1; // number of neurons for hidden layer 1
        int nr_neurons_2; // number of neurons for hidden layer 2
        float bias; // bias for neurons
        VectorXd x; // vector of input values
        VectorXd y; // vector of output values
        MatrixXd wh_1; // matrix of weights for hidden layer 1
        MatrixXd wh_2; // matrix of weights for hidden layer 2
        MatrixXd wo; // matrix of weights for output layer

    public: 
        NN(int, int, int, int);
        VectorXd forward_propagation();
        void set_weights(MatrixXd, MatrixXd, MatrixXd);
        void set_input(VectorXd);
        VectorXd get_output();
        VectorXd sigmoid(VectorXd);
        VectorXd tanh(VectorXd);
        VectorXd softmax(VectorXd);
};
