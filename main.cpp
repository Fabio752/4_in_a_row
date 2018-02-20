//
//  main.cpp
//  4_in_a_row
//
//  Created by fabio deo on 19/02/2018.
//  Copyright © 2018 fabio deo. All rights reserved.
//

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

void print_grid(vector<char> grid);
void insert_choose(vector<char>& grid, char choose, int column);
bool win(vector<char> grid);
bool complete_grid(vector<char> grid);
bool valid_insert(vector<char> grid, int column);

int main(){
    //initial conditions of the variables
    bool gameover = false;
    char winner;
    bool comp_grid = complete_grid(grid);
    bool valid_input;
    int num_of_rows = 6;
    int num_of_col = 7;
    
    //initial grid
    vector<char> grid;
    for (int i = 0; i < num_of_rows; i++)
        for (int j = 0; j < num_of_col; j++)
            grid.push_back('_');
    
    //gameplay
    while(!gameover && !comp_grid){
        print_grid(grid);
        
        // Player 1 turn
        int col_input_piece;
        cout << "Player X, choose the number of column you want to insert your piece (1-7)" <<endl;
        
        //ensure that the input is valid
        while (!(cin >> col_input_piece) || ((col_input_piece < 1 || col_input_piece > 7) && !valid_input)) {
            std::cin.clear(); //clear bad input flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
            cout <<"Please insert a valid column number (1-7)" <<endl;
            valid_input = valid_insert(grid, col_input_piece);
        }
        
        insert_choose(grid, 'x' , col_input_piece);
        gameover = win(grid);
        
        if (!gameover)
            comp_grid = complete_grid(grid);
        
        //Player 2 turn
        if (!gameover && !comp_grid){
            print_grid(grid);

            cout <<"Player O, choose the number of column you want to insert your piece (1-7)" <<endl;
            
            while (!(cin >> col_input_piece) || ((col_input_piece < 1 || col_input_piece > 7) && !valid_input)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
                cout <<"Please insert a valid column number (1-7)" <<endl;
                valid_input = valid_insert(grid, col_input_piece);
            }
            
            insert_choose(grid, 'o', col_input_piece);
            gameover = win(grid);
            
            if (gameover)
                winner = 'o';
            else
                comp_grid = complete_grid(grid);
        }
        else
            winner = 'x';
    }
    
    print_grid(grid);
    
    if (gameover)
        cout <<"The winner is Player: " <<winner <<endl;
    else
        cout <<"It is a draw!" <<endl;
    
    return 0;
}

//print the updated grid
void print_grid(vector<char> grid){
    int num_of_row = 6;
    int num_of_col = 7;
    
    for (int i = 0; i < num_of_row; i++){
        for (int j = 0; j < num_of_col; j++)
            cout <<grid[num_of_col * i + j] <<" ";
        cout <<endl;
    }
    
}

//insert the piece in the input column
void insert_choose(vector<char>& grid, char choose, int column){
    int num_of_col = 7;
    
    for (int i = column - 1; i < grid.size(); i = i + num_of_col){
        
        if (i + num_of_col > grid.size())
            grid[i] = choose;
        else
            if (grid[i + num_of_col] != '_'){
                grid[i] = choose;
                break;
            }
      
    }   
}

//check if a player won and return a bool
bool win(vector<char> grid){
    int num_of_row = 6;
    int num_of_col = 7;
    
    for(int i = 0; i < num_of_row; i++){
        for (int j = 0; j < num_of_col; j++){
            int index = i * num_of_row + j;
            
            //checking on the col
            if (index < 20)
                if (grid[index] == grid[index + num_of_col] && grid[index] != '_' && grid[index] == grid[index + 2 * num_of_col] && grid[index] == grid[index + 3 * num_of_col] 
                    return true;
           
            //checking the row
            if (j < 4)
                if (grid[index] == grid[index + 1]  && grid[index] != '_' && grid[index] == grid[index + 2] && grid[index] == grid[index + 3])
                    return true;
            
            //check the left to right diagonal
            if ( j < 4 && index < 20)
                if (grid[index] == grid[index + num_of_col + 1]  && grid[index] != '_' && grid[index] == grid[index + 2 * num_of_col + 2] && grid[index] == grid[index + 3 * num_of_col + 3])
                    return true;
                    
            //check the right to left diagonal
            if ( j > 2 && index < 20)
                if (grid[index] == grid[index + num_of_col - 1]  && grid[index] != '_' && grid[index] == grid[index + 2 * num_of_col - 2] && grid[index] == grid[index + 3 * num_of_col - 3])
                    return true;
        
        }
    }
                    
    return false;
}

//if the grid is complete thus the game is a draw returns true, otherwise 0
bool complete_grid(vector<char> grid){
    
    for (int i = 0; i < grid.size(); i++)
        if (grid[i] == '_')
            return false;
    return true;
    
}
  
// returns a bool set to true if the input column is full, empty otherwise
bool valid_insert(vector<char> grid, int column){
    if (grid[column - 1] == '_')
        return true;
    
    return false;
}

