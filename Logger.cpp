#include "include/Logger.h"

// constructor for Logger class
Logger::Logger() {
    logging_folder = "./Results/";
    fitness_file_name = "fitness";
}

// log the data of a given individual of a given generation
void Logger::log_individual(VectorXd gene_vector, int generation) {
    // open file for writing
    string file_name = logging_folder + "individual_" + to_string(generation);
    ofstream ind_file (file_name);

    // write gene_vector to file
    if (ind_file.is_open()) {
        for (int i = 0; i < gene_vector.size(); i++) {
            if (abs(gene_vector(i)) < 1e-15) 
                gene_vector(i) = 0;
            ind_file << setprecision(20) << (double) gene_vector(i) << endl;
        }
    }
    else 
        cout << "Unable to open file " << file_name << endl;
}

// log vector of fitness values which contains the best fitness of each
// generation
void Logger::log_fitness_vector(VectorXd best_fitness, VectorXd sum_fitness) {
    // open file for writing
    ofstream fitness_file ("./" + fitness_file_name);

    // write fitness vector to file
    if (fitness_file.is_open()) {
        for (int i = 0; i < best_fitness.size(); i++) {
            fitness_file << i << " " << (double) best_fitness(i) << " " << (double) sum_fitness(i) << endl;
        }
    }
    else 
        cout << "Unable to open file " << fitness_file_name << endl;
}

// read gene vector of individual from file for specified generation
VectorXd Logger::read_individual(int generation, int nr_genes) {
    // open file for reading
    string file_name = logging_folder + "individual_" + to_string(generation);
    ifstream ind_file(file_name);

    // read in gene vector
    VectorXd gene_vector(nr_genes);
    string number_string;
    int idx = 0;
    if (ind_file.is_open()){
        while(getline(ind_file, number_string)) {
            gene_vector(idx) = stod(number_string);
            idx++;
        }
    }
    else 
        cout << "Unable to open file " << file_name << endl;

    // return gene vector
    return gene_vector;
}
