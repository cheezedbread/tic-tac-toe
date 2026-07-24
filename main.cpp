#include <iostream>
#include <cstdlib>
#include <random>
// ------------- begin AI slop ------------- 
void clearScreen() {
#ifdef _WIN32
    system("cls");
#elif defined(__linux__) || defined(__APPLE__)
    system("clear");
#else
    std::cout << "Clear screen not supported on this OS" << endl;
#endif
}
//  ------------- end AI slop ------------- 

// Error codes are defined as follows:
// ---------------------------------------------------------------------------------------------------------
// | Before v1.1.0 | After v1.1.0 ||                           What Failed                                 |
// ---------------------------------------------------------------------------------------------------------
// |    400        |      -1      || Invalid input. (eg. input of "F" when expecting "A", "B" or "C";...)  |
// |    8008       |      -2      || Trying to overwrite an occupied spot.                                 |
// |    8008008    |     1024     || Impossible error code. If this error ever occurs, we are fucked.      |
// ---------------------------------------------------------------------------------------------------------
//


using namespace std; // i'm a beginner deal with it

void printMatch (int array[][3]) {
    string pp = "0";
    cout << "1    2    3" << endl;
    for (int u=0; u<3; u++) {
        for (int i=0; i<3; i++) {
            if (array[u][i] == 1) {
                pp = "X";
            }
            else if (array[u][i] == 2) {
                pp = "O";
            }
            else if (array[u][i] == 0) {
                pp = " ";
            }
            cout << "[" << pp << "] ";
    }
        cout << char('A' + u);
        cout << endl;
    }
}

string turnCheck (bool Oturn) {
    if (Oturn == false) {
        return "X";
    }
    else {
        return "O";
    }
}

int letterToNumber (string input) {
    if (input == "A" || input == "a") {
        return 0;
    }
    if (input == "B" || input == "b") {
        return 1;
    }
    if (input == "C" || input == "c") {
        return 2;
    }
    else {
        return -1;
    }
}

int changeBoard(int array[][3], int row, int column, bool Oturn) {
    if (array[row][column] == 0) {
        if (Oturn == false) {
            return 1;
        }
        else if (Oturn == true) {
            return 2;
        }
    }
    else {
        return -2;
    }
    return 1024;
}

int checkWin(int array[][3]) {
    int empty_cells = 0;
    for (int i=0; i<3; i++){ //checks all horizontal for win
        if (array[i][0]==array[i][1] && array[i][1]==array[i][2] && array[i][0] != 0) { //check all horizontal is the same AND arent zero bc zero is default
            if (array[i][0] == 1) {
                return 1; //X wins
            }
            else if (array[i][0] == 2) {
                return 2; //O wins
            }
        }
    }
    for (int i=0; i<3; i++){ //checks all vertical for win
        if (array[0][i]==array[1][i] && array[1][i]==array[2][i] && array[0][i] != 0) { //same as horizontal
            if (array[0][i] == 1) {
                return 1; //X wins
            }
            else if (array[0][i] == 2) {
                return 2; //O wins
            }
        }
    }
    if (array[0][0] == array[1][1] && array[1][1] == array[2][2] && array[0][0] != 0) { //diagonal from left to right
        if (array[0][0] == 1) {
            return 1;
        }
        else if (array[0][0] == 2) {
            return 2;
        }
    }
    if (array[2][0] == array[1][1] && array[1][1] == array[0][2] && array[2][0] !=0) { //diagonal from right to left
        if (array[2][0] == 1) {
            return 1;
        }
        else if (array[2][0] == 2) {
            return 2;
        }
    }
    for (int u=0; u<3; u++) {
        for (int i=0; i<3; i++) {
            if (array[u][i] == 0) {
                empty_cells++; //add 1 for every empty cell
            }
        }
    }
    if (empty_cells == 0) {
        return 3; //tied match because no winner yet no empty cells left
    }
    return 0;
}

int main(){
    int board[3][3]={0};
    string user_location_row = "init"; // has to be a string bc some bullshit with pointers happen using char and you cant input ABC into an integer
    int location_row = 0;// therefore the correct solution is to let the user input into a string and THEN internally convert back into an int via letterToNumber up there
    int user_location_column = 0;
    string user_initializer = "init";
    string game_turn = "init";
    bool O_turn = false;
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> dist(0, 2);
    cout << "Tic-Tac-Toe, now featuring lobotomized AI." << endl;
    cout << "Type [yes] for 2-player mode or [AI] to play with a bot." << endl;
    cin >> user_initializer;
    if (user_initializer == "yes" || user_initializer == "y" || user_initializer == "Y"){
        while (checkWin(board) == 0) {
        clearScreen();
        printMatch(board);
        game_turn = turnCheck(O_turn);
        cout << "It is " << game_turn << "'s turn" << endl;
        cout << "Column[1,2,3]:";
        cin >> user_location_column;
        user_location_column = user_location_column - 1; //arrays start at zero because some smartass decided c++ isnt hard enough
        cout << "Row[A,B,C]:";
        cin >> user_location_row;
        location_row = letterToNumber(user_location_row);
        if (location_row == -1) {
            clearScreen();
            cout << "invalid input, exiting...";
            return -1;
        }
        if (changeBoard(board, location_row, user_location_column, O_turn) == -2) {
            clearScreen();
            cout << "occupied spot, exiting..." << endl;
            return -2;
        }
        else {
            board[location_row][user_location_column] = changeBoard(board, location_row, user_location_column, O_turn);
        }
        printMatch(board);
        O_turn = !O_turn;
        }
        if (checkWin(board) == 1) {
            cout << "X wins." << endl;
        }
        else if (checkWin(board) == 2) {
            cout << "O wins." << endl;
        }
        else if (checkWin(board) == 3) {
            cout << "Tied match." << endl;
        }
    }
    else if (user_initializer == "AI" || user_initializer == "ai") {
        while (checkWin(board) == 0) {
            clearScreen();
            printMatch(board);
            game_turn = turnCheck(O_turn);
            if (game_turn == "X") {
                cout << "It is your turn." << endl;
                cout << "Column[1,2,3]:";
                cin >> user_location_column;
                user_location_column = user_location_column - 1; //arrays start at zero because some smartass decided c++ isnt hard enough
                cout << "Row[A,B,C]:";
                cin >> user_location_row;
                location_row = letterToNumber(user_location_row);
                if (location_row == -1) {
                    clearScreen();
                    cout << "invalid input, exiting...";
                    return -1;
                }
                if (changeBoard(board, location_row, user_location_column, O_turn) == -2) {
                    clearScreen();
                    cout << "occupied spot, exiting..." << endl;
                    return -2;
                }
            }
            else if (game_turn == "O") {
                while (true) {
                    user_location_column = dist(rng);
                    location_row = dist(rng);
                    if (changeBoard(board, location_row, user_location_column, O_turn) != -2) {
                        break;
                    }
                }
            }
            else {
                clearScreen();
                cout << "god is dead.";
                return 1024;
            }
            board[location_row][user_location_column] = changeBoard(board, location_row, user_location_column, O_turn);
            printMatch(board);
            O_turn = !O_turn;
        }

        if (checkWin(board) == 1) {
            cout << "You win!" << endl;
        }
        else if (checkWin(board) == 2) {
            cout << "Bot wins." << endl;
        }
        else if (checkWin(board) == 3) {
            cout << "Tied match." << endl;
        }
    }
    return 0;
}
