#include <iostream>
#include "include/Individual.h"

using namespace std;

int main(){
    Individual ind(6, 4, 6);
    int f = ind.evaluate_fitness(6, 4, 6);
    int f = ind.show_game(6, 4, 6);

    return 0;
}
