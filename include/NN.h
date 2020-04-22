#include <vector>
#include <random>

using namespace std; 

class NN {
    private: 
        int nr_inputs; // number of inputs
        int nr_outputs; // number of outputs
        int nr_neurons; // number of neurons
        vector<float> x; // vector of input values
        vector<float> y; // vector of output values
        vector<vector<float>> wh; // matrix of weights for hidden layer
        vector<vector<float>> wo; // matrix of weights for output layer

    public: 
        NN();
        NN(float, float, float);
        void forward_propagation();
};
