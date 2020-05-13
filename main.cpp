#include <eigen3/Eigen/Dense>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/GA.h"
#include "include/Individual.h"

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;

int display_fitness(int, VectorXd);

int main(){
    GA ga;
    VectorXd fitness;
    int idx = 0;
    int nr_generations = 1000; // number of generations to simulate

    for (int i = 0; i < nr_generations; i++) {
        fitness = ga.evaluate_fitness();
        idx = display_fitness(i, fitness);
        //ga.show_game(idx);
        //ga.selection();
        //ga.crossover();
        //ga.mutation();
    }

    return 0;
}

// displays the best fitness value in the fitness vector and the generation
// number, returns the index of the best fitness value
int display_fitness(int gen, VectorXd fitness) {
    int best_fitness = 1;
    int idx = 0;
    for (unsigned int i = 0; i < fitness.size(); i++){
        if (fitness(i) > best_fitness) {
            best_fitness = fitness(i);
            idx = i;
        }
    }
    cout << gen << ": " << best_fitness << " " << fitness.sum() << endl;
    return idx;
}
