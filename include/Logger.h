#pragma once
#include <eigen3/Eigen/Dense>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "Individual.h"

using namespace std; 
using Eigen::MatrixXd;
using Eigen::VectorXd;

class Logger {
    private: 
        string logging_folder;
        string fitness_file_name;

    public: 
        Logger();
        void log_individual(VectorXd, int);
        void log_fitness_vector(VectorXd, VectorXd);
        VectorXd read_individual(int, int);
};
