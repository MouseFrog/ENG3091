// Linear Regression model using gradient descent
// Inherits shared variables and functions from Models base class 
// Adapted from Assignment 1 GradientDescent class 


#ifndef SKLEARN_LITE_LINEARREGRESSION_HPP
#define SKLEARN_LITE_LINEARREGRESSION_HPP

#include <iostream>
#include <vector>
#include <cmath>      // std::sqrt, std::pow
#include "Models.hpp"

namespace sklearn_lite::linear {

class LinearRegression : public Models {

    public:

        // Constructor passes the learning rate and iteration count to the base class
        // These are stored in Models and used later during training
        // lr controls how big each gradient descent step is
        // iterations sets the maximum number of training steps
        LinearRegression(double lr, int iterations)
            : Models{lr, iterations} {}

        // Trains the model using gradient descent
        // X is the normalised feature matrix with intercept column prepended
        // y contains the actual concrete strength values, one per sample
        // The goal is to adjust the weights so the prediction error gets smaller each iteration
        void fit(const std::vector<std::vector<double>>& X,
                 const std::vector<double>& y)
        {
            int m = X.size();    // Number of samples, rows
            int n = X[0].size(); // Number of weights including intercept, cols

            // Start all weights at 0 before training
            // weights[0] acts as the bias and the rest correspond to the feature columns
            weights.resize(n, 0.0);

            // If the weights barely change between iterations, stop early
            double converge_threshold = 1e-12;

            // Repeat the gradient descent update until we either converge or hit the maximum number of iterations
            for (int e = 0; e < iterations; e++) {

                // Stores the gradient for each weight during this iteration
                // Reset to 0 at the start of every pass through the data
                std::vector<double> gradients(n, 0.0);

                // Save the current weights so we can compare after the update
                std::vector<double> old_weights = weights;

                // Go through every training sample
                for (int i = 0; i < m; i++) {

                    // Calculate the predicted strength for this sample
                    // Sum of weight * feature value across all features
                    double y_prediction = 0.0;
                    for (int j = 0; j < n; j++) {
                        y_prediction += weights[j] * X[i][j]; // weight * feature value
                    }

                    // Work out how far the prediction is from the actual value
                    double error = y_prediction - y[i];

                    // Add this sample's contribution to each gradient
                    // Gradient for each weight = error * its corresponding feature value
                    for (int j = 0; j < n; j++) {
                        gradients[j] += error * X[i][j];
                    }
                }

                // Update each weight using the average gradient across all samples
                for (int j = 0; j < n; j++) {
                    weights[j] -= lr * gradients[j] * (1.0 / m);
                }

                // Measure how much the weights changed overall this iteration
                // Sum the squared change for each weight then take square root
                double overall_change = 0.0;
                for (int j = 0; j < n; j++) {
                    double weight_change = old_weights[j] - weights[j];
                    overall_change += weight_change * weight_change; 
                }

                overall_change = std::sqrt(overall_change); // Magnitude of total change

                // If the weights have basically stabilised, stop training early
                if (overall_change < converge_threshold) {
                    std::cout << "Converged at iteration: " << e << "\n";
                    break;
                }
            }

            std::cout << "Training complete\n";
        }

        // Uses the learned weights to make predictions for new input data
        // This is the same dot product used during training, but now the weights stay fixed
        std::vector<double> predict(const std::vector<std::vector<double>>& X) const {

            // If fit() has not been called yet, there are no learned weights to use
            if (weights.empty()) {
                std::cerr << "Model not trained. Call fit() first\n";
                return {};
            }

            std::vector<double> predictions;

            // Calculate one prediction for each input row
            for (int i = 0; i < (int)X.size(); i++) {

                // Same dot product as in fit(): sum of weight * feature for all features
                double y_hat = 0.0;
                for (int j = 0; j < (int)weights.size(); j++) {
                    y_hat += weights[j] * X[i][j]; 
                }

                predictions.push_back(y_hat);
            }

            return predictions;
        }

        // Checks how well the model predicts compared to just guessing the mean
        // R2 close to 1 means the model is doing well
        // R2 close to 0 means it is not really improving on a basic average guess
        double r2_score(const std::vector<double>& y_true,
                        const std::vector<double>& y_pred) const {

            int m = y_true.size();

            // Find the mean of the actual concrete strength values
            double mean_y = 0.0;
            for (int i = 0; i < m; i++) {
                mean_y += y_true[i];
            }
            mean_y /= m; // Divide by number of samples to get mean

            // SS_res: total squared error made by our model
            double ss_res = 0.0;
            for (int i = 0; i < m; i++) {
                ss_res += std::pow(y_true[i] - y_pred[i], 2);
            }

            // SS_tot: total squared error if we always guessed the mean strength
            // This represents the dumbest possible model as a baseline
            double ss_tot = 0.0;
            for (int i = 0; i < m; i++) {
                ss_tot += std::pow(y_true[i] - mean_y, 2); 
            }

            // Compare the model against the mean baseline
            return 1.0 - (ss_res / ss_tot);
        }

}; // end LinearRegression

} // namespace sklearn_lite::linear

#endif