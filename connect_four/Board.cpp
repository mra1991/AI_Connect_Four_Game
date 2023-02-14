#include "Board.h"
#include<iostream>
using namespace std;

//constructor will make sure the board is empty
Board::Board() {
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 7; j++)
			brd[i][j] = 0;
}

//safe reading access to the private member array brd
inline int Board::get_cell(int i, int j) {
	return brd[i][j];
}

//safe writing access to the private member array brd
inline void Board::set_cell(int i, int j, int value) {
	brd[i][j] = value;
}

//is move index m is a valid move?
bool Board::can_play(int m) {
	if (m < 1 || m > 7) //check if m is in valid range
		return false;
	if (get_cell(5, m - 1) == 0) //check if the column m isn't full
		return true;
	return false; //the column must have been full
}

//if column m isn't full, drops an X piece down that column
void Board::play_x(int m) {
	if (!can_play(m)) //checking if the column is full
		return;
	for (int i = 5; i > 0; i--) //starting from the top going down
		if (get_cell(i, m - 1) == 0 && get_cell(i - 1, m - 1) != 0) { //if there's a piece under this spot
			set_cell(i, m - 1, 1); //put a piece in this spot
			return;
		}
	set_cell(0, m - 1, 1); //the columns is empty. put the piece at the bottom
}

//if column m isn't full, drops an O piece down that column
void Board::play_o(int m) {
	if (!can_play(m))
		return;
	for (int i = 5; i > 0; i--) //starting from the top going down
		if (get_cell(i, m - 1) == 0 && get_cell(i - 1, m - 1) != 0) { //if there's a piece under this spot
			set_cell(i, m - 1, -1); //put a piece in this spot
			return;
		}
	set_cell(0, m - 1, -1); //the columns is empty. put the piece at the bottom
}

//removes the top piece in column m if there's any
void Board::undo_play(int m) {
	for (int i = 5; i >= 0; i--)
		if (get_cell(i, m - 1) != 0) {
			set_cell(i, m - 1, 0);
			return;
		}
}

//only called if nobody has won, if all the columns are full, that means the game has finished with a tie
bool Board::is_tie() {
	for (int i = 1; i <= 7; i++) // going through columns
		if (can_play(i)) //if the column isn't full
			return false;
	return true;
}

//returns 1 if X wins, -1 if O wins and 0 otherwise.
int Board::evaluate() {
	//checking the rows for 4 consequent X's or O's
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			if (get_cell(i, j) != 0 && get_cell(i, j) == get_cell(i, j + 1) && get_cell(i, j + 1) == get_cell(i, j + 2) && get_cell(i, j + 2) == get_cell(i, j + 3)) {
				return get_cell(i, j);
			}
		}
	}

	//checking the columns for 4 consequent X's or O's
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 7; j++) {
			if (get_cell(i, j) != 0 && get_cell(i, j) == get_cell(i + 1, j) && get_cell(i + 1, j) == get_cell(i + 2, j) && get_cell(i + 2, j) == get_cell(i + 3, j)) {
				return get_cell(i, j);
			}
		}
	}

	//checking the diagonals for 4 consequent X's or O's
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			if (get_cell(i, j) != 0 && get_cell(i, j) == get_cell(i + 1, j + 1) && get_cell(i + 1, j + 1) == get_cell(i + 2, j + 2) && get_cell(i + 2, j + 2) == get_cell(i + 3, j + 3)) {
				return get_cell(i, j);
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 6; j > 2; j--) {
			if (get_cell(i, j) != 0 && get_cell(i, j) == get_cell(i + 1, j - 1) && get_cell(i + 1, j - 1) == get_cell(i + 2, j - 2) && get_cell(i + 2, j - 2) == get_cell(i + 3, j - 3)) {
				return get_cell(i, j);
			}
		}
	}

	return 0;
}

//prints the board in its current state in the std output
void Board::ilustrate() {
	cout << endl;
	for (int i = 5; i >= 0; i--) {
		for (int j = 0; j < 7; j++)
			if (get_cell(i, j) == 1)
				cout << "  " << 'X';
			else if (get_cell(i, j) == -1)
				cout << "  " << 'O';
			else
				cout << "  " << '|';
		cout << endl;
	}
	cout << "-----------------------" << endl;
	for (int i = 0; i < 7; i++)
		cout << "  " << i + 1;
	cout << endl << endl;
}

