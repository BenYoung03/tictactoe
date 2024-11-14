#include <iostream>
#include <string>
using namespace std;

char player, ai;

struct {
    int x;
    int y;
} aiMoveCords;

void printBoard(char board[3][3]){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

char checkWinner(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '_' && board[i][0]) {
            return board[i][0];
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != '_') {
            return board[0][i];
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '_') {
        return board[0][0];
        
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '_') {
        return board[0][2];
        
    }
    return '.';
}

bool tieCheck(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '_') {
                return false;
            }
        }
    }
    return true;
}


int minimax(char board[3][3], int depth, int alpha, int beta, bool isMaximizing){
    char winner = checkWinner(board);
    
    //subtracting depth allows the algorithm to find the shortest optimal end.
    if (winner == ai) return 10 - depth;
    if (winner == player) return depth - 10;
    if (tieCheck(board)) return 0;
    
    if(isMaximizing){
        int bestScore = -100000;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if (board[i][j] == '_'){
                    board[i][j] = ai;
                    int score = minimax(board, depth + 1, alpha, beta, false);
                    bestScore = max(bestScore, score);
                    board[i][j] = '_';
                    alpha = max(alpha, score);
                    if (beta <= alpha){
                        return bestScore;
                    } 
                }
            }
        }
        return bestScore;
    } else {
        int worstScore = 100000;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if (board[i][j] == '_'){
                    board[i][j] = player;
                    int score = minimax(board, depth + 1, alpha, beta, true);
                    worstScore = min(score, worstScore);
                    board[i][j] = '_';
                    beta = min(beta, score);
                    if (beta <= alpha){
                        return worstScore;
                    } 
                }
            }
        }
        return worstScore;
    }
}

void aiMove(char board[3][3]){
    int bestScore = -1000;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i][j] == '_'){
                board[i][j] = ai;
                int score = minimax(board, 0, -1000, 1000, false);
                board[i][j] = '_';
                if(score > bestScore){
                    bestScore = score;
                    aiMoveCords.x = i;
                    aiMoveCords.y = j;
                }
            }
        }
    }
    board[aiMoveCords.x][aiMoveCords.y] = ai;
}


int main(){

    char board[3][3] = {
        {'_', '_', '_'},
        {'_', '_', '_'},
        {'_', '_', '_'}
    };

    while(true){
        char decision;
        cout << "Would you like to play as X or O? ";
        cin >> decision;

        if (decision == 'X' || decision == 'x'){
            player = 'X';
            ai = 'O';
            break;
        } else if (decision == 'O' || decision == 'o'){
            player = 'O';
            ai = 'X';
            break;
        } else {
            cout << "Invalid choice! please input X or O" << endl;
            continue;
        }
    }
    
    while(true){
        if(player == 'O'){
            aiMove(board);

            if(checkWinner(board) == ai) {
                printBoard(board);
                cout << "Computer wins!" << endl;
                break;
            }

            if(tieCheck(board)){
                printBoard(board);
                cout << "It is a draw!" << endl;
                break;
            }
        }
        printBoard(board);
        int x, y;
        cout << endl;
        cout << "Enter the column where you want your move to be (1, 2, 3): ";
        cin >> y;
        cout << "Enter the row where you want your move to be (1, 2, 3): ";
        cin >> x;
        x--;
        y--;
        cout << endl;
        if(board[x][y] != '_'){
            cout << "Invalid move! Try Again!" << endl;
            continue;
        }
        board[x][y] = player;

        if(checkWinner(board) == player) {
            printBoard(board);
            cout << "You win!" << endl;
            break;
        }

        if(tieCheck(board)){
            printBoard(board);
            cout << "It is a draw!" << endl;
            break;
        }

        if(player == 'X'){
            aiMove(board);

            if(checkWinner(board) == ai) {
                printBoard(board);
                cout << "Computer wins!" << endl;
                break;
            }

            if(tieCheck(board)){
                printBoard(board);
                cout << "It is a draw!" << endl;
                break;
            }
        }
    }

    return 0;
}
