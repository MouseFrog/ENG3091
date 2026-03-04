#include <iostream>
#include <vector>
#include <fstream>
#include <random>


// Class that stores the parameters of the regression line
// After training, w represents the price increase per bedroom
// and b represents the base price when bedrooms = 0
class SimpleLinearRegression {
public:

    double w = 0.0;   // slope of the line
    double b = 0.0;   // y-intercept

    // Train the model using the dataset of bedrooms and prices
    // The goal is to compute the line that best fits the data
    void train(const std::vector<double>& bedroom_values,
               const std::vector<double>& price_values)
    {
        int num_points = bedroom_values.size();

        // Variables used to accumulate the sums needed for the regression calculation
        // They are updated during the loop so that we end up with the totals across the dataset
        double sum_bedrooms = 0.0;
        double sum_prices = 0.0;
        double sum_bedrooms_times_prices = 0.0;
        double sum_bedrooms_squared = 0.0;

         // Loop through the dataset and update the running sums for each value
        for (int i = 0; i < num_points; i++) {

            double bedrooms = bedroom_values[i];
            double price = price_values[i];

            sum_bedrooms += bedrooms;
            sum_prices += price;

            // Tracks how bedrooms and prices vary together
            sum_bedrooms_times_prices += bedrooms * price;

            // Tracks how spread out the bedroom values are
            sum_bedrooms_squared += bedrooms * bedrooms;
        }

        // Use the totals computed in the loop to determine the slope of the regression line
        w = (num_points * sum_bedrooms_times_prices - sum_bedrooms * sum_prices)
            /
            (num_points * sum_bedrooms_squared - sum_bedrooms * sum_bedrooms);

        b = (sum_prices - w * sum_bedrooms) / num_points;
    }


// Predicts price from the regression model
    double predict(double bedrooms) {
        return w * bedrooms + b;
    }
};


int main() {

    // Create the random generator used for producing bedroom values and noise
    std::random_device rd;
    std::mt19937 gen(rd());

    // Random bedroom values between 1 and 5
    std::uniform_int_distribution<int> bedroom_dist(1, 5);

    // Small noise applied to bedroom
    std::uniform_real_distribution<double> bedroom_noise(-0.1, 0.1);

    // Noise added to price 
    std::uniform_real_distribution<double> price_noise(-4000.0, 4000.0);


    // True price parameters
    double true_price_per_bedroom = 50000.0;
    double true_base_price = 50000.0;

    int num_houses = 100;


    // Store the generated bedroom and price values
    std::vector<double> bedroom_values;
    std::vector<double> price_values;

    // Open CSV file to store the generated dataset
    std::ofstream myFile("prices.csv");

    // If the file cannot be opened, print an error and stop the program
    if (!myFile.is_open()) {
        std::cout << "Error: could not open prices.csv for writing." << std::endl;
        return 1;
    }

    // Column headers for the CSV file
    myFile << "Bedrooms,Price\n";


    // Generate the dataset used for training the regression model
    // Each iteration creates one house entry
    for (int i = 0; i < num_houses; i++) {

        int base_bedrooms = bedroom_dist(gen);

        // Add small noise to the bedroom value
        double bedrooms = base_bedrooms + bedroom_noise(gen);

        // Compute the price using the true model with added noise
        double price =
            (true_price_per_bedroom * base_bedrooms)
            + true_base_price
            + price_noise(gen);


        // Store values so the regression model can train on them
        bedroom_values.push_back(bedrooms);
        price_values.push_back(price);

        // Also write the same data to the CSV file
        myFile << bedrooms << "," << price << "\n";
    }

    // Close the dataset file once writing is finished
    myFile.close();

    std::cout << "Data written to prices.csv" << std::endl;


    // Create the regression model and train it using the generated dataset
    SimpleLinearRegression model;
    model.train(bedroom_values, price_values);


    // Print the estimated parameters and compare them with the true values
    std::cout << "\n--- Normal Equation Results ---" << std::endl;

    std::cout << "Estimated price per bedroom (w): "
              << model.w
              << " | True: "
              << true_price_per_bedroom
              << std::endl;

    std::cout << "Estimated base price (b): "
              << model.b
              << " | True: "
              << true_base_price
              << std::endl;

    return 0;
}