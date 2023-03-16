#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

string s[1024][1024];


void tromino(int x_board, int y_board, int x_missing, int y_missing, int board_size, int** board) {
    if (board_size == 1) {
        if (x_board == x_missing && y_board == y_missing) {
            board[x_board][y_board] = -1;  // mark the missing square with -1
        } else {
            board[x_board][y_board] = 1;  // fill the remaining square with 1
        }
    } else {
        int half_size = board_size / 2;
        int x_center = x_board + half_size;
        int y_center = y_board + half_size;
        int x_upper_left = x_board;
        int y_upper_left = y_center;
        int x_upper_right = x_center;
        int y_upper_right = y_center;
        int x_lower_left = x_board;
        int y_lower_left = y_board;
        int x_lower_right = x_center;
        int y_lower_right = y_board;

        // Place tromino in upper left quadrant
        if (x_missing < x_center && y_missing >= y_center) {
            tromino(x_upper_left, y_upper_left, x_missing, y_missing, half_size, board);
            board[x_center-1][y_center] = 2;
            tromino(x_board, y_center, x_center - 1, y_center, half_size, board);
            tromino(x_center, y_board, x_center, y_center - 1, half_size, board);
            tromino(x_center, y_center, x_center, y_center, half_size, board);
        }
        // Place tromino in upper right quadrant
        else if (x_missing >= x_center && y_missing >= y_center) {
            tromino(x_upper_right, y_upper_right, x_missing, y_missing, half_size, board);
            board[x_center][y_center] = 2;
            tromino(x_board, y_board, x_center - 1, y_center - 1, half_size, board);
            tromino(x_center, y_board, x_center, y_center - 1, half_size, board);
            tromino(x_center, y_center, x_center, y_center, half_size, board);
        }
        // Place tromino in lower left quadrant
        else if (x_missing < x_center && y_missing < y_center) {
            tromino(x_lower_left, y_lower_left, x_missing, y_missing, half_size, board);
            board[x_center][y_center-1] = 2;
            tromino(x_center, y_board, x_center, y_center - 1, half_size, board);
            tromino(x_board, y_center, x_center - 1, y_center, half_size, board);
            tromino(x_center, y_center, x_center, y_center, half_size, board);
        }
        // Place tromino in lower right quadrant
        else {
            tromino(x_lower_right, y_lower_right, x_missing, y_missing, half_size, board);
            board[x_center-1][y_center-1] = 2;
            tromino(x_board, y_board, x_center - 1, y_center - 1, half_size, board);
            tromino(x_board, y_center, x_center - 1, y_center, half_size, board);
            tromino(x_board, y_center, x_center - 1, y_center, half_size, board);}
    }
}

int main(){
    int board_size =1;
    int x_missing ;
    int y_missing ;


    while (board_size != 0) {
        cout << "Please enter size of board (need to be 2^n and 0 to quit): ";
        cin >> board_size;
        // check if board size is a power of 2
        while (ceil(log2(board_size)) != floor(log2(board_size))){
            if (ceil(log2(board_size)) != floor(log2(board_size))) {
             cout<<"\nSize of board needs to be 2^n \n";
            cout << "Please enter size of board (0 to quit): ";
            cin >> board_size;
            continue;}
        }
         if (board_size == 0) {
            break;
        }


        int x_missing, y_missing;
        cout << "Please enter coordinates of missing square (separate by a space): ";
        cin >> x_missing >> y_missing;


            // Initialize board dynamically
        int** board = new int*[board_size];
        for (int i = 0; i < board_size; i++) {
            board[i] = new int[board_size];
            for (int j = 0; j < board_size; j++) {
                board[i][j] = 0;
            }
        }

        tromino(0, 0, x_missing, y_missing, board_size, board);

    // Print the output matrix
        for (int j = board_size - 1; j >= 0; j--) {
        for (int i = 0; i < board_size; i++) {
            if (i == x_missing && j == y_missing) {
                cout << setw(3) << "MS" << " ";
            } else if ((i+1 < board_size && j+2 < board_size && board[i][j] == -1 && board[i][j+1] == -1 && board[i][j+2] == -1 && board[i+1][j+2] == -1) ||
                    (i+2 < board_size && j+1 < board_size && board[i][j] == -1 && board[i+1][j] == -1 && board[i+2][j] == -1 && board[i+2][j+1] == -1) ||
                    (i+2 < board_size && j-1 >= 0 && board[i][j] == -1 && board[i+1][j] == -1 && board[i+2][j] == -1 && board[i+2][j-1] == -1) ||
                    (i+1 < board_size && j-2 >= 0 && board[i][j] == -1 && board[i][j-1] == -1 && board[i][j-2] == -1 && board[i+1][j-2] == -1)) {
                if (i == x_missing && j == y_missing) {
                    cout << setw(3) << "MS" << " ";
                } else if (i+1 < board_size && j+2 < board_size && board[i][j] == -1 && board[i][j+1] == -1 && board[i][j+2] == -1 && board[i+1][j+2] == -1) {
                    cout << setw(3) << "UL" << " ";
                } else if (i+2 < board_size && j+1 < board_size && board[i][j] == -1 && board[i+1][j] == -1 && board[i+2][j] == -1 && board[i+2][j+1] == -1) {
                    cout << setw(3) << "UL" << " ";
                } else if (i+2 < board_size && j-1 >= 0 && board[i][j] == -1 && board[i+1][j] == -1 && board[i+2][j] == -1 && board[i+2][j-1] == -1) {
                    cout << setw(3) << "UR" << " ";
                } else if (i+1 < board_size && j-2 >= 0 && board[i][j] == -1 && board[i][j-1] == -1 && board[i][j-2] == -1 && board[i+1][j-2] == -1) {
                    cout << setw(3) << "UR" << " ";
                }
            } else {
                cout << setw(3) << "LR" << " ";
            }
        }
        cout << endl;
    }



    // Deallocate memory
        for (int i = 0; i < board_size; i++) {
            delete[] board[i];
        }
        delete[] board;



    }
}
