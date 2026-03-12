#include "MultiRegression.hpp"

// This file consists standalone functions
// saveFile() and normaliseData()

// Iterate through matrix and save into .csv file
// Matrix is read only to preserve original
void saveFile(const std::vector<std::vector<double>>& data_in, std::string file_name){  
// Open file to store data
    std::ofstream myFile(file_name +".csv");

    // Check if file opened correctly
    if (myFile.is_open()) { 
        
        // Iterate through row and column 
        for (int i=0; i<data_in.size(); i++) {
            for (int j=0; j<data_in[i].size(); j++){
                myFile << data_in[i][j];

                // Inserts comma only between values --> if value is not in last column, print ","
                if (j < (data_in[i].size()-1) ){
                    myFile << ",";
                }
            }
            // Value in last column, begin new row
            myFile << "\n";
        }
        // Close file
        myFile.close();
        std::cout << "File successfully saved" << std::endl; // Success prompt
    }
    
    else {
    std::cerr << "Unable to open file!" << std::endl; // Raise error if unable to open file
    } 
} 

// Z-VALUE NORMALISATION
// Mean = 0.0
// Standard Deviation = 1.0
NormResult normaliseData(const std::vector<std::vector<double>>& var_matrix){

    int m = var_matrix.size();    // rows
    int n = var_matrix[0].size(); // cols

    NormResult result;
    result.matrix.resize(m,std::vector<double>(n)); // Matrix to hold normalised values

    // Reserve first set of data point for intercept
    // Default values for Z-Value Normalisation
    for(int i = 0; i < m ; i++){
        result.matrix[i][0]=1.0;    
    }
    result.means.push_back(0.0); 
    result.std_devs.push_back(1.0);
    
    // Loop through each variable j (col)
    for (int j = 1; j < n; j++){  

        double value_sum{0};
        for(int i = 0; i < m ; i++){
            value_sum += var_matrix[i][j];
        }
        double mean = value_sum/m;  // Mean value of variable j
        result.means.push_back(mean);

        double error_sum{0};
        for (int i = 0; i < m; i++) {
            error_sum += std::pow((var_matrix[i][j]-mean), 2);  // (x_val - mean)^2

        }
        double std_dev = std::sqrt(error_sum/m);    // Standard Deviation
        result.std_devs.push_back(std_dev);

        if (std_dev == 0){
            std::cout<<"Standard Deviation Cannot be 0"<<std::endl;
        }

        //x_normalised = (x - mean)/std_dev
        else {
            for (int i = 0; i < m; i++){
            result.matrix[i][j] = (var_matrix[i][j]-mean)/std_dev;
            }
        }
        
    }
    return result;
}