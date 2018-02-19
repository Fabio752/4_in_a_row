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

int main(){
    int num_of_rows = 6;
    int num_of_col = 7;
    
    
    vector<char> grid;
    for (int i = 0; i < num_of_rows; i++)
        for (int j = 0; j < num_of_col; j++)
            grid.push_back('_');
    
    bool gameover = false;
    char winner;
    
    while(!gameover){
        print_grid(grid);

        int col_input_piece;
        cout <<"Player X, choose the number of column you want to insert your piece (1-7)" <<endl;
        cin >> col_input_piece;
        while (col_input_piece < 1 || col_input_piece > 7){
            cout <<"Please insert a valid column number (1-7)" <<endl;
            cin >> col_input_piece;
        }
        insert_choose(grid, 'x' , col_input_piece);
        gameover = win(grid);
        
        cout <<"gameover value: " <<gameover <<endl;
        if (!gameover){
            print_grid(grid);

            cout <<"Player O, choose the number of column you want to insert your piece (1-7)" <<endl;
            cin >>col_input_piece;
            while (col_input_piece < 1 || col_input_piece > 7){
                cout <<"Please insert a valid column number (1-7)" <<endl;
                cin >> col_input_piece;
            }
            insert_choose(grid, 'o', col_input_piece);
            
            gameover = win(grid);
            if (gameover)
                winner = 'o';
            
        }
        else
            winner = 'x';
    }
    
    print_grid(grid);
    cout <<"The winner is Player: " <<winner <<endl;

    return 0;
}

void print_grid(vector<char> grid){
    int num_of_row = 6;
    int num_of_col = 7;
    
    for (int i = 0; i < num_of_row; i++){
        for (int j = 0; j < num_of_col; j++)
            cout <<grid[num_of_col * i + j] <<" ";
        cout <<endl;
    }
}

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

bool win(vector<char> grid){
    int num_of_row = 6;
    int num_of_col = 7;
    bool gameover = false;
    
    for(int i = 0; i < num_of_row; i++){
        for (int j = 0; j < num_of_col; j++){
            int index = i * num_of_row + j;
            
            //checking on the col
            if (index < 20)
                if (grid[index] == grid[index + num_of_col] && grid[index] != '_' && grid[index] == grid[index + 2 * num_of_col] && grid[index] == grid[index + 3 * num_of_col])
                    
                    gameover = true;
            
            
            //checking the row
            if (j < 4)
                if (grid[index] == grid[index + 1]  && grid[index] != '_' && grid[index] == grid[index + 2] && grid[index] == grid[index + 3])
                    gameover = true;
            
            
            //check the left to right diagonal
            if ( j < 4 && index < 20)
                if (grid[index] == grid[index + num_of_col + 1]  && grid[index] != '_' && grid[index] == grid[index + 2 * num_of_col + 2] && grid[index] == grid[index + 3 * num_of_col + 3])
                    gameover = true;
            
            //check the right to left diagonal
            if ( j > 2 && index < 20)
                if (grid[index] == grid[index + num_of_col - 1]  && grid[index] != '_' && grid[index] == grid[index + 2 * num_of_col - 2] && grid[index] == grid[index + 3 * num_of_col - 3])
                    gameover = true;
        
        }
        
    }
    return gameover;
}


