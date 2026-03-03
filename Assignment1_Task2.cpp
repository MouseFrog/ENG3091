// Create a class that holds the learnable parameters

#include <iostream>
#include <vector>

class LinearRegression {
public: //everything in a class is usually private and only accessible by
        //the class. This makes the parameters global variables
    double w = 0.0;     // Weight (slope)
    double b = 0.0;     // Bias (y-intercept)
    double alpha;       // Learning rate

    LinearRegression(double lr) : alpha(lr) {}

    // Prediction function: y_hat = wx + b
    double predict(double x) {
        return w * x + b;
    }
};

