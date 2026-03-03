#include <iostream>
#include <vector>
#include <numeric>

//Simple Linear Regression

int main() {
    // Data: {Square Footage} -> {Price in $1000s}
    std::vector<double> x = {1500, 2000, 1200, 2500, 1800};
    std::vector<double> y = {300, 400, 250, 500, 360};

    SimpleLinearRegression slr;
    slr.train(x, y);

    double newHouse = 2200;
    std::cout << "Predicted price for 2200 sqft: $" << slr.predict(newHouse) << "k" << std::endl;
    
    return 0;
}

//Multiple Linear Regression
class MultipleLinearRegression {
    std::vector<double> weights; 
    double learningRate;

public:
    MultipleLinearRegression(int numFeatures, double lr = 0.01) : learningRate(lr) {   
        // Create vector of size according to # of variables, fill with 0.0
        // +1 to include intercept at weights[0]
        weights.resize(numFeatures + 1, 0.0); 
    }

    void train(const std::vector<std::vector<double>>& X, const std::vector<double>& y, int epochs) {
        int m = X.size();    // Number of samples, row
        int n = X[0].size(); // Number of features, col

        for (int e = 0; e < epochs; e++) {  // # of iterations
            std::vector<double> gradients(n + 1, 0.0);  

            
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    prediction += weights[j] * X[i][j]; // Predicted y-val based on weights and x-val
                }
                
                 // Calculate error in y-val prediction
                double error = prediction - y[i];  
                //gradients[0] += error;
                for (int j = 0; j < n; j++) {
                    //gradients[j + 1] += error * X[i][j];
                    gradients[j] += error * X[i][j];
                }
            }
            // Update weights using the average gradient
            for (int j = 0; j <= n; j++) {
                weights[j] -= (learningRate * gradients[j]) / m;
            }
        }
    }
};