// Create a class that holds the learnable parameters
// Allows for storage of different states as the model improves

#include <iostream>
#include <vector>

class LinearRegression {
public: // Classes are private by default, make public

    double w = 0.0;     // Weight (slope)
    double b = 0.0;     // Bias (y-intercept)
    double alpha;       // Learning rate

    // Store lr value into alpha, ramains in LinearRegression object throughout iteration
    LinearRegression(double lr) : alpha(lr) {}

    // Prediction function: y_hat = wx + b
    double predict(double x) {
        return w * x + b;
    }
};

