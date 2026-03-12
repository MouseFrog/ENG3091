#include <iostream>
#include <vector>   // for std::vector
#include <fstream>  // Required for file operations
#include <random>   // For data generation
#include "MultiRegression.hpp"

int main() {

    // Create Dataset instance and define parameters, otherwise uses default
    Dataset custom;
    custom.bed_max = 10;
    custom.area_min = 15;
    custom.area_max = 1400;

    DataGenerator gen(custom); // Create instance with custom settings
    int num_features{2};
    Matrices myMatrix = gen.make_matrix(100,num_features);

    GradientDescent mlr(num_features,0.001);
    int num_iterations{10};
    mlr.train(myMatrix.X,myMatrix.Y,num_iterations);
    std::vector<double> finalWeights = mlr.getWeights();

    std::cout<<finalWeights[0]<<"\n"
    <<finalWeights[1]<<"\n"
    <<finalWeights[2]<<"\n";

    saveFile(myMatrix.X,"og file" );
    
    return 0;
}    

