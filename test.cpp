
    std::vector<std::vector<double>> singleMatrix_X;

    for (int i = 0; i < multiMatrix.X.size(); i++) {
        std::vector<double> row;
        
        // Extract the Intercept (column 0) and Bedrooms (column 1)
        row.push_back(multiMatrix.X[i][0]); 
        row.push_back(multiMatrix.X[i][1]); 
        
        // Add this new 2-column row to your singleX matrix
        singleMatrix_X.push_back(row);
    }


    NormResult norm_single_X =  normaliseData(singleMatrix_X);
    GradientDescent grad_single_model(1,0.1);  // Learning rate = 0.1
    grad_single_model.train(norm_single_X.matrix,multiMatrix.Y,num_iterations);

    // Normalised weights
    std::vector<double> single_weights = grad_single_model.getWeights();   

    // Recover de-normalised results

    // real weight = normalised weight/standard deviation
    double real_single_bedroom = single_weights[1]/norm_single_X.std_devs[1];  

    // real intercept = normalised intercept - sum of (variable real weights * variable mean values)
    double real_single_intercept = single_weights[0]-(real_single_bedroom * norm_single_X.means[1]);

    std::cout <<
    "Single Intercept: "<<real_single_intercept<<"\n"<<
    "Snigle Bedroom Weight: "<<real_single_bedroom<<"\n";
