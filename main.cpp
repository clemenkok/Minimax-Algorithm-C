// An Implementation of the Minimax Algorithm in
// Tic-Tac-Toe

// Importing libraries
#include <iostream>
#include <limits>
#include <stdlib.h>
#include <string>

// Array for the board
char board[3][3] = {{'_', '_', '_'}, {'_', '_', '_'}, {'_', '_', '_'}};

// Variable Declaration
int choice;
int row, column;
int openSpots;
char turn = 'X';
bool draw = false;
std::string winner = "null";
std::string realWinner = "null";

// Board Layout
void display_board() {
	std::cout << "PLAYER - X AI - O" << std::endl;
	std::cout << "       0     1     2  " << std::endl;
	std::cout << "     _________________" << std::endl;
	std::cout << "    |     |     |     |" << std::endl;
	std::cout << "0   |"
			  << "  " << board[0][0] << "  |  " << board[0][1] << "  |  "
			  << board[0][2] << "  "
			  << "|   0" << std::endl;
	std::cout << "    |_____|_____|_____|" << std::endl;
	std::cout << "    |     |     |     |" << std::endl;
	std::cout << "1   |"
			  << "  " << board[1][0] << "  |  " << board[1][1] << "  |  "
			  << board[1][2] << "  "
			  << "|   1" << std::endl;
	std::cout << "    |_____|_____|_____|" << std::endl;
	std::cout << "    |     |     |     |" << std::endl;
	std::cout << "2   |"
			  << "  " << board[2][0] << "  |  " << board[2][1] << "  |  "
			  << board[2][2] << "  "
			  << "|   2" << std::endl;
	std::cout << "    |     |     |     |" << std::endl;
	std::cout << "    |_____|_____|_____|" << std::endl;
	std::cout << "                       " << std::endl;
	std::cout << "       0     1     2  " << std::endl;
	std::cout << "                       " << std::endl;
}

// Checker for row / column equivalence
bool equals3(char a, char b, char c) {
	if (a == b && b == c && a != '_') {
		return true;
	} else {
		return false;
	}
}

// Function to check winner or draw
std::string checkWinner() {
	for (int i = 0; i < 3; i++) {
		// Horizontal
		if (equals3(board[i][0], board[i][1], board[i][2])) {
			return winner = board[i][0];
		}
		// Vertical
		else if (equals3(board[0][i], board[1][i], board[2][i])) {
			return winner = board[i][0];
		}
		// Diagonal
		else if (equals3(board[0][0], board[1][1], board[2][2])) {
			return winner = board[0][0];
		} else if (equals3(board[2][0], board[1][1], board[0][2])) {
			return winner = board[2][0];
		}
	}
	// Check for Draw
	int openSpots = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == '_') {
				openSpots++;
			}
		}
	}
	if (winner == "null" && openSpots == 0) {
		return "tie";
	} else {
		return winner;
	}
}

// MiniMax Magic
int minimax(char board[3][3], int depth, bool isMaximizing) {
	std::string result = checkWinner();
	if (result != "null") {
		if (result == "X") {
			return 10;
		};
		if (result == "O") {
			return -10;
		};
		if (result == "tie") {
			return 0;
		};
	}
	if (isMaximizing) {
		int bestScore = -std::numeric_limits<int>::max();
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				// Is the spot available?
				if (board[i][j] == '_') {
					board[i][j] = 'O';
					int score = minimax(board, depth + 1, false);
					board[i][j] = '_';
					bestScore = std::max(score, bestScore);
				}
			}
		}
		return bestScore;
	} else {
		int bestScore = std::numeric_limits<int>::max();
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				// Is the spot available?
				if (board[i][j] == '_') {
					board[i][j] = 'X';
					int score = minimax(board, depth + 1, true);
					board[i][j] = '_';
					bestScore = std::min(score, bestScore);
				}
			}
		}
		return bestScore;
	}
}

// AI Move
void bestMove() {
	int bestScore = -std::numeric_limits<int>::max();
	char best_i;
	char best_j;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == '_') {
				board[i][j] = 'O';
				int score = minimax(board, 0, false);
				board[i][j] = '_';
				if (score > bestScore) {
					bestScore = score;
					best_i = i;
					best_j = j;
				}
			}
		}
	}
	board[best_i][best_j] = 'O';
}

// Function to control player turns
void player_turn() {
	if (turn == 'X') {
		display_board();
		std::cout << "Your turn. Input a row: ";
		std::cin >> row;
		std::cout << "Your turn. Input a column: ";
		std::cin >> column;
		if (board[row][column] != 'X' && board[row][column] != 'O') {
			board[row][column] = 'X';
			turn = 'O';
		} else if (board[row][column] == 'X' || board[row][column] == 'O') {
			std::cout << "Invalid Operation" << std::endl;
			player_turn();
		}
	} else if (turn == 'O') {
		std::cout << "AI turn." << std::endl;
		bestMove();
		turn = 'X';
	}
}

// Function to check winner or draw
std::string checkRealWinner() {
	for (int i = 0; i < 3; i++) {
		// Horizontal
		if (equals3(board[i][0], board[i][1], board[i][2])) {
			return realWinner = board[i][0];
		}
		// Vertical
		else if (equals3(board[0][i], board[1][i], board[2][i])) {
			return realWinner = board[i][0];
		}
		// Diagonal
		else if (equals3(board[0][0], board[1][1], board[2][2])) {
			return realWinner = board[0][0];
		} else if (equals3(board[2][0], board[1][1], board[0][2])) {
			return realWinner = board[2][0];
		}
	}
	// Check for Draw
	int openSpots = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == '_') {
				openSpots = openSpots + 1;
			}
		}
	}

	if (realWinner == "null" && openSpots == 0) {
		return realWinner = "tie";
	} else {
		return realWinner;
	}
}

// Driver Program
int main() {
	std::cout << "Artificial Intelligence: A C++ Implementation of the "
				 "Minimax Algorithm in Tic-Tac-Toe"
			  << std::endl;
	while (realWinner == "null") {
		player_turn();
		checkRealWinner();
	};
	display_board();
	if (realWinner == "tie") {
		std::cout << "Game Over! The game was a " << realWinner << "."
				  << std::endl;
	} else {
		std::cout << "Game Over! Winner is " << realWinner << "." << std::endl;
	}
}
