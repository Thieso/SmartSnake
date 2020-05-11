#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/GA.h"
#include "include/Individual.h"

using namespace std;

int display_fitness(int, vector<int>);

int main(){
    GA ga;
    vector<int> fitness;
    int idx = 0;

    for (int i = 0; i < 100; i++) {
        fitness = ga.evaluate_fitness();
        idx = display_fitness(i, fitness);
        ga.selection();
        ga.crossover();
        ga.mutation();
        ga.replacement();
        ga.show_game(idx);
    }

    return 0;
}

// displays the best fitness value in the fitness vector and the generation
// number, returns the index of the best fitness value
int display_fitness(int gen, vector<int> fitness) {
    int best_fitness = 1;
    int idx = 0;
    for (unsigned int i = 0; i < fitness.size(); i++){
        if (fitness[i] > best_fitness) {
            best_fitness = fitness[i];
            idx = i;
        }
    }
    cout << gen << ": " << best_fitness << endl;
    return idx;
}
