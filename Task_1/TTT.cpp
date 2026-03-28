// g++ TTT.cpp -o"TTT.exe"
// Copy and paste above command into terminal to compile

#include <iostream>
#include <random>

// Get user input 
int manual_move(std::string input_prompt) {
    while (true) { 
        
        std::cout << input_prompt << std::endl;

        // Validate input 
        int input_value;
        if (std::cin >> input_value){ // If input is integer, pass from std::cin buffer into input_value variable
            if (input_value < 10 && input_value > 0) { // Check input range
            std::cin.ignore(99999, '\n');   //Clears input buffer
            return input_value;
            
            }
            // Invalid range input
            else{
                std::cout <<"Please input an integer between 1 and 9"<< std::endl;
                std::cin.ignore(99999, '\n');
            }
        }
        // Invalid type input
        else {
        std::cout << "Invalid Input" << std::endl;
        std::cin.clear();   // Clears error flag
        std::cin.ignore(99999, '\n');
        }
    }
}   

// Computer move
int comp_move(std::mt19937& global_num){
    std::uniform_int_distribution<> distr(1, 9);  // Get integer between 1 to 9
    return distr(global_num);
}

// Print board     
void printboard(char board[3][3]) {
    std::cout << "____________" << std::endl;
    std::cout << " " <<board[0][0] << " | " << board[0][1] << "  |" << board[0][2] << std::endl;
    std::cout << " " <<board[1][0] << " | " << board[1][1] << "  |" << board[1][2] << std::endl;
    std::cout << " " <<board[2][0] << " | " << board[2][1] << "  |" << board[2][2] << std::endl;
    std::cout << "____________" << std::endl;
}
    
// Check Win
bool isWinner(char board[3][3],char Player){    
    
    // Vertical Wins
    for (int i=0; i<3; i++) {
        if (board[i][0]==Player && board[i][1]==Player && board[i][2]==Player) {
            std::cout <<"Player"<<Player<<"wins!"<<std::endl;
            return true;
        }

        // Horizontal wins
        if (board[0][i]==Player && board[1][i]==Player && board[2][i]==Player) {
            std::cout <<"Player"<<Player<<" wins!"<<std::endl;
            return true;
        }
    }
    // Diagonal Wins
     if (board[0][0]==Player && board[1][1]==Player && board[2][2]==Player){
            std::cout <<"Player"<<Player<<" wins!"<<std::endl;
            return true;
        }
    if (board[0][2]==Player && board[1][1]==Player && board[2][0]==Player){
        std::cout <<"Player"<<Player<<" wins!"<<std::endl;
        return true;
    }
    return false;
}

// Check full board 
bool isFullboard(char board[3][3]) {
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            if (board[i][j] == '-') {
                return false; // Board has space
            
            }
        }
    }
    return true; // Full board
}


int main() {

    std::random_device rand; // Random number generated from hardware 
    std::mt19937 mt_num(rand()); // Seed generator  

    // Begin with player X, user input
    const char playerX = 'X';
    const char playerO = 'O';
    char current_player = playerX;

    // Initialise board with default symbol 
    char myboard[3][3]={
        {'-','-','-'},
        {'-','-','-'},
        {'-','-','-'}
        };
    
    printboard(myboard);
    
    while (true) {
        
        int input_val;
        
        // Computer generated value
        if (current_player == playerO){
            input_val = comp_move(mt_num);
        }

        // User input value
        else {
            input_val = manual_move("Enter move (1-9):");
        }
        
        // Unpack number for board assignment
        int row, col;
        row = 2 - (input_val - 1) / 3;
        col = (input_val - 1) % 3;


        // Check for cell occupancy
        if (myboard[row][col] != '-') {
            if (current_player == playerX){
                std::cout << "Cell  occupied, please select another cell." << std::endl;
            }
            continue;
        }
        
        // Update board with user input
        myboard[row][col] = current_player;
        printboard(myboard);

        // Check for win 
        if (isWinner(myboard,current_player)){
            if (current_player == playerX){
                std::cout<<"You win the computer!"<<"\n";
            }
            else{
                std::cout<<"You lost to amateur code. Shame"<<"\n";
            }
        break;
       }
            
        // Check full board
        if (isFullboard(myboard)){
            std::cout << "Game over!" <<"\n";
            break;
        }

        // Switch player at end of turn
        if (current_player == playerX) {
            current_player = playerO;
            }
        else {
            current_player = playerX;
        }
            
    }
    
    return 0;
}

