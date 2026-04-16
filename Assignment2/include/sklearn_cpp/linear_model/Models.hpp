// Linear, Binary, and Multi-class models inherit from base model Models
// Binary and Multi-class differ from each other in area where they differ from Linear 
// i.e. sigmoid/ soft max functions, regularised loss function
// Thus Binary and Multi-class are derived to be the same hierarchy as Linear, rather than deriving from another child Logistics class
#ifndef SKLEARN_LITE_MODELS_HPP
#define SKLEARN_LITE_MODELS_HPP

#include <iostream>
#include <vector>   // for std::vector

// Base model for the 3 regression models
namespace sklearn_lite::linear {
class Models {

    protected:
    
    std::vector<std::vector<double>> weights {};
    double lr
    int num_features

    public:
    Models(double lr, int num_features) : num_features{num_features}, lr{lr} {
        weights.resize(num_features+1, 0.0);
    }

    // Function to access weights and biases
    const std::vector<std::vector<double>>& get_weights() const{ //return by reference, const to protect object
        return weights;
    }

    // Function to update weights and biases?

   
};

} 


// Linear Regression Model, Gradient Descent
namespace sklearn_lite::linear {
class LinearRegression : public Models {


   
};

} 

// Binary Logistic Regression
namespace sklearn_lite::linear {
class BinaryLogistic : public Models {

// fit() function to train model

// predict() function for a given variable set
// Apply sigmoid function to wrap probability between 0 and 1
// Regularised Loss function
   
};

} 

// Multi-class Logistic Regression
namespace sklearn_lite::linear {
class MultiLogistic : public Models {

// fit() function to train model

// predict() function for a given variable set
// Apply softmax function to wrap probability between 0 and 1
// Regularised Loss function

   
};

} 



#endif 